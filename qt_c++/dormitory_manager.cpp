#include "dormitory_manager.h"

DormitoryManager::DormitoryManager(QSqlDatabase &database, QObject *parent)
    : QObject(parent), db(database)
{
}

DormitoryManager::~DormitoryManager()
{
}

bool DormitoryManager::assignDormitory(int userId)
{
    if (!db.isOpen()) {
        logError("Database not open");
        return false;
    }

    // 开始事务
    db.transaction();

    try {
        // 获取用户信息
        QSqlQuery query;
        query.prepare("SELECT gender FROM users WHERE id = ?");
        query.addBindValue(userId);
        
        if (!query.exec() || !query.next()) {
            throw std::runtime_error("获取用户信息失败");
        }
        
        QString userGender = query.value(0).toString();
        
        // 查找合适的宿舍
        query.prepare("SELECT id FROM dormitories "
                     "WHERE (gender = ? OR gender IS NULL OR gender = '') AND current_count < capacity "
                     "ORDER BY current_count ASC LIMIT 1");
        query.addBindValue(userGender);
        
        if (!query.exec() || !query.next()) {
            throw std::runtime_error("没有找到合适的宿舍");
        }
        
        int dormId = query.value(0).toInt();
        
        // 查找可用床位
        query.prepare("SELECT id FROM beds "
                     "WHERE dormitory_id = ? AND is_occupied = 0 "
                     "ORDER BY bed_number ASC LIMIT 1");
        query.addBindValue(dormId);
        
        if (!query.exec() || !query.next()) {
            throw std::runtime_error("没有找到可用床位");
        }
        
        int bedId = query.value(0).toInt();
        
        // 更新床位状态
        query.prepare("UPDATE beds SET is_occupied = 1 WHERE id = ?");
        query.addBindValue(bedId);
        if (!query.exec()) {
            throw std::runtime_error("更新床位状态失败");
        }
        
        // 更新宿舍人数
        query.prepare("UPDATE dormitories SET current_count = current_count + 1 WHERE id = ?");
        query.addBindValue(dormId);
        
        if (!query.exec()) {
            throw std::runtime_error("更新宿舍人数失败");
        }
        
        // 如果宿舍性别为空，设置宿舍性别
        query.prepare("UPDATE dormitories SET gender = ? WHERE id = ? AND (gender IS NULL OR gender = '')");
        query.addBindValue(userGender);
        query.addBindValue(dormId);
        query.exec(); // 不检查错误，因为可能已经设置了性别
        
        // 记录分配结果
        query.prepare("INSERT INTO assignments (user_id, dormitory_id, bed_id, assigned_date) "
                     "VALUES (?, ?, ?, CURRENT_TIMESTAMP)");
        query.addBindValue(userId);
        query.addBindValue(dormId);
        query.addBindValue(bedId);
        
        if (!query.exec()) {
            throw std::runtime_error("记录分配结果失败");
        }
        
        // 提交事务
        if (!db.commit()) {
            throw std::runtime_error("提交事务失败");
        }
        
        return true;
    }
    catch (const std::exception& e) {
        db.rollback();
        logError(QString("分配宿舍失败: %1").arg(e.what()));
        return false;
    }
}

bool DormitoryManager::addDormitory(const QString &name, const QString &building, const QString &roomNumber, 
                                   int capacity, const QString &gender, const QString &scheduleType, bool acceptDifferentMajor)
{
    if (!validateDormitoryData(name, building, roomNumber, capacity, gender, scheduleType)) {
        logError("宿舍数据验证失败");
        return false;
    }

    if (checkDormitoryExists(building, roomNumber)) {
        logError("宿舍已存在");
        return false;
    }

    // 开始事务
    db.transaction();

    try {
        // 1. 添加宿舍
        QSqlQuery query;
        query.prepare("INSERT INTO dormitories (name, building, room_number, capacity, gender, current_count, schedule_type, accept_different_major) VALUES (?, ?, ?, ?, ?, 0, ?, ?)");
        query.addBindValue(name);
        query.addBindValue(building);
        query.addBindValue(roomNumber);
        query.addBindValue(capacity);
        query.addBindValue(gender);
        query.addBindValue(scheduleType);
        query.addBindValue(acceptDifferentMajor);

        if (!query.exec()) {
            QString err = query.lastError().text();
            logError("添加宿舍失败: " + err);
            throw std::runtime_error(err.toStdString());
        }

        int dormId = query.lastInsertId().toInt();
        logError(QString("成功添加宿舍，ID: %1").arg(dormId));

        // 2. 创建床位
        for (int i = 1; i <= capacity; i++) {
            query.prepare("INSERT INTO beds (dormitory_id, bed_number, is_upper, is_occupied) VALUES (?, ?, ?, ?)");
            query.addBindValue(dormId);
            query.addBindValue(i);
            query.addBindValue(false);  // 默认下铺
            query.addBindValue(false);  // 默认未占用

            if (!query.exec()) {
                QString err = query.lastError().text();
                logError("添加床位失败: " + err);
                throw std::runtime_error(err.toStdString());
            }
        }

        // 提交事务
        if (!db.commit()) {
            throw std::runtime_error("提交事务失败");
        }

        return true;
    }
    catch (const std::exception& e) {
        db.rollback();
        logError(QString("添加宿舍失败: %1").arg(e.what()));
        return false;
    }
}

bool DormitoryManager::updateDormitory(int dormId, const QString &name, const QString &building, const QString &roomNumber, 
                                      int capacity, const QString &gender, const QString &scheduleType, bool acceptDifferentMajor)
{
    if (!validateDormitoryData(name, building, roomNumber, capacity, gender, scheduleType)) {
        return false;
    }

    QSqlQuery query;
    query.prepare("UPDATE dormitories SET name = ?, building = ?, room_number = ?, capacity = ?, gender = ?, schedule_type = ?, accept_different_major = ? WHERE id = ?");
    query.addBindValue(name);
    query.addBindValue(building);
    query.addBindValue(roomNumber);
    query.addBindValue(capacity);
    query.addBindValue(gender);
    query.addBindValue(scheduleType);
    query.addBindValue(acceptDifferentMajor);
    query.addBindValue(dormId);

    if (!query.exec()) {
        logError("更新宿舍失败: " + query.lastError().text());
        return false;
    }

    return true;
}

bool DormitoryManager::deleteDormitory(int dormId)
{
    // 开始事务
    db.transaction();

    try {
        QSqlQuery query;

        // 1. 删除分配记录
        query.prepare("DELETE FROM assignments WHERE dormitory_id = ?");
        query.addBindValue(dormId);
        if (!query.exec()) {
            throw std::runtime_error("删除分配记录失败: " + query.lastError().text().toStdString());
        }

        // 2. 删除床位记录
        query.prepare("DELETE FROM beds WHERE dormitory_id = ?");
        query.addBindValue(dormId);
        if (!query.exec()) {
            throw std::runtime_error("删除床位记录失败: " + query.lastError().text().toStdString());
        }

        // 3. 删除宿舍记录
        query.prepare("DELETE FROM dormitories WHERE id = ?");
        query.addBindValue(dormId);
        if (!query.exec()) {
            throw std::runtime_error("删除宿舍记录失败: " + query.lastError().text().toStdString());
        }

        // 提交事务
        if (!db.commit()) {
            throw std::runtime_error("提交事务失败");
        }

        return true;
    }
    catch (const std::exception& e) {
        db.rollback();
        logError(QString("删除宿舍失败: %1").arg(e.what()));
        return false;
    }
}

QList<Dormitory> DormitoryManager::getDormitories()
{
    QList<Dormitory> dormitories;
    QSqlQuery query("SELECT * FROM dormitories ORDER BY building, room_number");
    
    if (!query.exec()) {
        logError("获取宿舍列表失败: " + query.lastError().text());
        return dormitories;
    }
    
    qDebug() << "开始获取宿舍列表";
    
    while (query.next()) {
        Dormitory dorm;
        dorm.id = query.value("id").toInt();
        dorm.name = query.value("name").toString();
        dorm.building = query.value("building").toString();
        dorm.roomNumber = query.value("room_number").toString();
        dorm.capacity = query.value("capacity").toInt();
        dorm.gender = query.value("gender").toString();
        dorm.currentCount = query.value("current_count").toInt();
        dorm.scheduleType = query.value("schedule_type").toString();
        dorm.acceptDifferentMajor = query.value("accept_different_major").toBool();
        
        dormitories.append(dorm);
        qDebug() << "读取到宿舍:" << dorm.building << dorm.roomNumber;
    }
    
    qDebug() << "总共读取到" << dormitories.size() << "个宿舍";
    return dormitories;
}

QList<QMap<QString, QVariant>> DormitoryManager::getDormitoryAssignments(int dormId)
{
    QList<QMap<QString, QVariant>> result;
    
    QSqlQuery query;
    query.prepare("SELECT u.*, a.*, b.bed_number, b.is_upper "
                 "FROM assignments a "
                 "JOIN users u ON a.user_id = u.id "
                 "JOIN beds b ON a.bed_id = b.id "
                 "WHERE a.dormitory_id = ?");
    query.addBindValue(dormId);

    if (!query.exec()) {
        logError("Failed to get dormitory assignments: " + query.lastError().text());
        return result;
    }

    while (query.next()) {
        QMap<QString, QVariant> assignment;
        assignment["user_id"] = query.value("user_id");
        assignment["name"] = query.value("name");
        assignment["student_id"] = query.value("student_id");
        assignment["major"] = query.value("major");
        assignment["bed_number"] = query.value("bed_number");
        assignment["is_upper"] = query.value("is_upper");
        assignment["assigned_date"] = query.value("assigned_date");
        result.append(assignment);
    }

    return result;
}

QMap<QString, QVariant> DormitoryManager::getStudentDormitory(int userId)
{
    QMap<QString, QVariant> result;
    
    QSqlQuery query;
    query.prepare("SELECT d.id as dormitory_id, d.name as dormitory_name, d.building, d.room_number, "
                 "b.bed_number, b.is_upper, a.assigned_date "
                 "FROM assignments a "
                 "JOIN dormitories d ON a.dormitory_id = d.id "
                 "JOIN beds b ON a.bed_id = b.id "
                 "WHERE a.user_id = ?");
    query.addBindValue(userId);

    qDebug() << "getStudentDormitory: userId =" << userId;
    
    if (!query.exec()) {
        logError("Failed to get student dormitory: " + query.lastError().text());
        return result;
    }
    
    if (!query.next()) {
        qDebug() << "getStudentDormitory: No assignment found for user" << userId;
        return result;
    }

    qDebug() << "getStudentDormitory: Found assignment for user" << userId;

    result["dormitory_id"] = query.value("dormitory_id");
    result["dormitory_name"] = query.value("dormitory_name");
    result["building"] = query.value("building");
    result["room_number"] = query.value("room_number");
    result["bed_number"] = query.value("bed_number");
    result["is_upper"] = query.value("is_upper");
    result["assigned_date"] = query.value("assigned_date");

    return result;
}

bool DormitoryManager::addBed(int dormId, int bedNumber, bool isUpper)
{
    if (checkBedExists(dormId, bedNumber)) {
        logError("Bed already exists");
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO beds (dormitory_id, bed_number, is_upper, is_occupied) "
                 "VALUES (?, ?, ?, ?)");
    
    query.addBindValue(dormId);
    query.addBindValue(bedNumber);
    query.addBindValue(isUpper);
    query.addBindValue(false);  // is_occupied

    if (!query.exec()) {
        logError("Failed to add bed: " + query.lastError().text());
        return false;
    }

    return true;
}

bool DormitoryManager::updateBedStatus(int bedId, bool isOccupied)
{
    QSqlQuery query;
    query.prepare("UPDATE beds SET is_occupied = ? WHERE id = ?");
    query.addBindValue(isOccupied);
    query.addBindValue(bedId);

    if (!query.exec()) {
        logError("Failed to update bed status: " + query.lastError().text());
        return false;
    }

    return true;
}

QList<QMap<QString, QVariant>> DormitoryManager::getAvailableBeds(int dormId)
{
    QList<QMap<QString, QVariant>> result;
    
    QSqlQuery query;
    query.prepare("SELECT b.* FROM beds b "
                 "WHERE b.dormitory_id = ? AND b.is_occupied = 0");
    query.addBindValue(dormId);

    if (!query.exec()) {
        logError("Failed to get available beds: " + query.lastError().text());
        return result;
    }

    while (query.next()) {
        QMap<QString, QVariant> bed;
        bed["id"] = query.value("id");
        bed["bed_number"] = query.value("bed_number");
        bed["is_upper"] = query.value("is_upper");
        result.append(bed);
    }

    return result;
}

bool DormitoryManager::validateDormitoryData(const QString &name, const QString &building, const QString &roomNumber, 
                                           int capacity, const QString &gender, const QString &scheduleType)
{
    if (name.isEmpty()) {
        logError("宿舍名称不能为空");
        return false;
    }

    if (building.isEmpty()) {
        logError("楼栋不能为空");
        return false;
    }

    if (roomNumber.isEmpty()) {
        logError("房间号不能为空");
        return false;
    }

    if (capacity <= 0 || capacity > 8) {
        logError("容量必须在1-8之间");
        return false;
    }

    if (gender != "男" && gender != "女") {
        logError("性别必须是'男'或'女'");
        return false;
    }

    if (scheduleType.isEmpty()) {
        logError("宿舍类型不能为空");
        return false;
    }

    return true;
}

bool DormitoryManager::checkDormitoryExists(const QString &building, const QString &roomNumber)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM dormitories WHERE building = ? AND room_number = ?");
    query.addBindValue(building);
    query.addBindValue(roomNumber);
    if (!query.exec() || !query.next()) {
        logError("检查宿舍是否存在失败: " + query.lastError().text());
        return false;
    }
    return query.value(0).toInt() > 0;
}

bool DormitoryManager::checkBedExists(int dormId, int bedNumber)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM beds WHERE dormitory_id = ? AND bed_number = ?");
    query.addBindValue(dormId);
    query.addBindValue(bedNumber);

    if (!query.exec() || !query.next()) {
        return false;
    }

    return query.value(0).toInt() > 0;
}

bool DormitoryManager::saveUserPreferences(int userId, const StudentPreference &preference)
{
    QSqlQuery query(db);
    query.prepare("INSERT OR REPLACE INTO student_preferences "
                 "(user_id, prefer_upper, prefer_capacity, accept_different_major, schedule_type, "
                 "is_early_bird, is_night_owl, is_quiet, is_social, hobbies, special_needs, "
                 "prefer_same_major, prefer_same_gender, updated_at) "
                 "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, CURRENT_TIMESTAMP)");
    
    query.addBindValue(userId);
    query.addBindValue(preference.preferUpper);
    query.addBindValue(preference.preferCapacity);
    query.addBindValue(preference.acceptDifferentMajor);
    query.addBindValue(preference.scheduleType);
    query.addBindValue(preference.isEarlyBird);
    query.addBindValue(preference.isNightOwl);
    query.addBindValue(preference.isQuiet);
    query.addBindValue(preference.isSocial);
    query.addBindValue(preference.hobbies);
    query.addBindValue(preference.specialNeeds);
    query.addBindValue(preference.preferSameMajor);
    query.addBindValue(preference.preferSameGender);
    
    return query.exec();
}

StudentPreference DormitoryManager::getUserPreferences(int userId)
{
    StudentPreference preference;
    preference.userId = userId;
    
    QSqlQuery query(db);
    query.prepare("SELECT * FROM student_preferences WHERE user_id = ?");
    query.addBindValue(userId);
    
    if (query.exec() && query.next()) {
        preference.preferUpper = query.value("prefer_upper").toBool();
        preference.preferCapacity = query.value("prefer_capacity").toInt();
        preference.acceptDifferentMajor = query.value("accept_different_major").toBool();
        preference.scheduleType = query.value("schedule_type").toString();
        preference.isEarlyBird = query.value("is_early_bird").toBool();
        preference.isNightOwl = query.value("is_night_owl").toBool();
        preference.isQuiet = query.value("is_quiet").toBool();
        preference.isSocial = query.value("is_social").toBool();
        preference.hobbies = query.value("hobbies").toString();
        preference.specialNeeds = query.value("special_needs").toString();
        preference.preferSameMajor = query.value("prefer_same_major").toBool();
        preference.preferSameGender = query.value("prefer_same_gender").toBool();
    }
    
    return preference;
}

QList<StudentPreference> DormitoryManager::getAllUnassignedPreferences()
{
    QList<StudentPreference> preferences;
    
    QSqlQuery query(db);
    query.prepare("SELECT sp.* FROM student_preferences sp "
                 "WHERE sp.user_id NOT IN (SELECT user_id FROM assignments)");
    
    if (query.exec()) {
        while (query.next()) {
            StudentPreference preference;
            preference.userId = query.value("user_id").toInt();
            preference.preferUpper = query.value("prefer_upper").toBool();
            preference.preferCapacity = query.value("prefer_capacity").toInt();
            preference.acceptDifferentMajor = query.value("accept_different_major").toBool();
            preference.scheduleType = query.value("schedule_type").toString();
            preference.isEarlyBird = query.value("is_early_bird").toBool();
            preference.isNightOwl = query.value("is_night_owl").toBool();
            preference.isQuiet = query.value("is_quiet").toBool();
            preference.isSocial = query.value("is_social").toBool();
            preference.hobbies = query.value("hobbies").toString();
            preference.specialNeeds = query.value("special_needs").toString();
            preference.preferSameMajor = query.value("prefer_same_major").toBool();
            preference.preferSameGender = query.value("prefer_same_gender").toBool();
            
            preferences.append(preference);
        }
    }
    
    return preferences;
}

void DormitoryManager::logError(const QString &message)
{
    qDebug() << "DormitoryManager Error:" << message;
}

// 消息相关接口实现
bool DormitoryManager::sendMessage(int senderId, int receiverId, const QString &content) {
    QSqlQuery query(db);
    query.prepare("INSERT INTO messages (sender_id, receiver_id, content, sent_at) VALUES (?, ?, ?, CURRENT_TIMESTAMP)");
    query.addBindValue(senderId);
    query.addBindValue(receiverId);
    query.addBindValue(content);
    return query.exec();
}

QList<QMap<QString, QVariant>> DormitoryManager::getMessages(int userId1, int userId2) {
    QList<QMap<QString, QVariant>> messages;
    QSqlQuery query(db);
    qDebug() << "getMessages SQL params:" << userId1 << userId2;
    query.prepare("SELECT * FROM messages WHERE (sender_id = ? AND receiver_id = ?) OR (sender_id = ? AND receiver_id = ?) ORDER BY sent_at ASC");
    query.addBindValue(userId1);
    query.addBindValue(userId2);
    query.addBindValue(userId2);
    query.addBindValue(userId1);
    bool ok = query.exec();
    if (!ok) qDebug() << "getMessages SQL error:" << query.lastError().text();
    int count = 0;
    while (query.next()) {
        QMap<QString, QVariant> msg;
        msg["id"] = query.value("id");
        msg["sender_id"] = query.value("sender_id");
        msg["receiver_id"] = query.value("receiver_id");
        msg["content"] = query.value("content");
        msg["send_time"] = query.value("sent_at");
        msg["is_read"] = query.value("is_read");
        messages.append(msg);
        count++;
    }
    qDebug() << "getMessages result size:" << count;
    return messages;
}

// 智能分配相关方法实现
AssignmentResult DormitoryManager::findBestMatch(int userId)
{
    AssignmentResult result;
    result.userId = userId;
    result.matchScore = 0;

    // 新增：判断该学生是否已分配宿舍
    QSqlQuery checkQuery(db);
    checkQuery.prepare("SELECT COUNT(*) FROM assignments WHERE user_id = ?");
    checkQuery.addBindValue(userId);
    if (checkQuery.exec() && checkQuery.next() && checkQuery.value(0).toInt() > 0) {
        // 已分配，直接返回
        return result;
    }
    
    // 获取学生偏好
    StudentPreference preference = getUserPreferences(userId);
    if (preference.userId == 0) {
        logError("未找到学生偏好信息");
        return result;
    }
    
    // 获取学生信息
    QSqlQuery userQuery(db);
    userQuery.prepare("SELECT gender, major FROM users WHERE id = ?");
    userQuery.addBindValue(userId);
    if (!userQuery.exec() || !userQuery.next()) {
        logError("未找到学生信息");
        return result;
    }
    
    QString userGender = userQuery.value("gender").toString();
    QString userMajor = userQuery.value("major").toString();
    
    // 查找最佳匹配的宿舍
    QSqlQuery dormQuery(db);
    dormQuery.prepare("SELECT d.*, b.id as bed_id, b.bed_number, b.is_upper "
                     "FROM dormitories d "
                     "JOIN beds b ON d.id = b.dormitory_id "
                     "WHERE b.is_occupied = 0 "
                     "ORDER BY d.current_count ASC, d.id ASC");
    
    if (!dormQuery.exec()) {
        logError("查询可用宿舍失败");
        return result;
    }
    
    int bestScore = 0;
    while (dormQuery.next()) {
        int dormId = dormQuery.value("id").toInt();
        int score = calculateMatchScore(dormId, userId);
        
        if (score > bestScore) {
            bestScore = score;
            result.dormitoryId = dormId;
            result.bedId = dormQuery.value("bed_id").toInt();
            result.dormitoryName = dormQuery.value("name").toString();
            result.bedNumber = dormQuery.value("bed_number").toInt();
            result.isUpper = dormQuery.value("is_upper").toBool();
            result.matchScore = score;
        }
    }
    
    return result;
}

int DormitoryManager::calculateMatchScore(int dormId, int userId)
{
    int score = 0;
    
    // 获取宿舍信息
    QSqlQuery dormQuery(db);
    dormQuery.prepare("SELECT * FROM dormitories WHERE id = ?");
    dormQuery.addBindValue(dormId);
    if (!dormQuery.exec() || !dormQuery.next()) {
        return 0;
    }
    
    int dormCapacity = dormQuery.value("capacity").toInt();
    QString dormGender = dormQuery.value("gender").toString();
    QString dormSchedule = dormQuery.value("schedule_type").toString();
    int currentCount = dormQuery.value("current_count").toInt();
    
    // 获取学生偏好
    StudentPreference preference = getUserPreferences(userId);
    if (preference.userId == 0) {
        return 0;
    }
    
    // 获取学生信息
    QSqlQuery userQuery(db);
    userQuery.prepare("SELECT gender, major FROM users WHERE id = ?");
    userQuery.addBindValue(userId);
    if (!userQuery.exec() || !userQuery.next()) {
        return 0;
    }
    
    QString userGender = userQuery.value("gender").toString();
    QString userMajor = userQuery.value("major").toString();
    
    // 计算匹配分数
    
    // 1. 容量匹配 (权重: 极高)
    if (dormCapacity == preference.preferCapacity) {
        score += 100;
    } else {
        score += 1;
    }
    
    // 2. 作息匹配 (权重: 8分)
    if (dormSchedule == preference.scheduleType || dormSchedule.isEmpty()) {
        score += 8;
    } else {
        score += 3;
    }
    
    // 3. 性别匹配 (权重: 6分)
    if (dormGender == userGender || dormGender.isEmpty()) {
        score += 6;
    } else {
        score += 2;
    }
    
    // 4. 宿舍状态 (权重: 4分)
    if (currentCount == 0) {
        score += 4; // 空宿舍优先
    }
    
    // 5. 专业匹配 (权重: 3分)
    if (preference.preferSameMajor) {
        QSqlQuery majorQuery(db);
        majorQuery.prepare("SELECT COUNT(*) FROM assignments a "
                          "JOIN users u ON a.user_id = u.id "
                          "WHERE a.dormitory_id = ? AND u.major = ?");
        majorQuery.addBindValue(dormId);
        majorQuery.addBindValue(userMajor);
        if (majorQuery.exec() && majorQuery.next() && majorQuery.value(0).toInt() > 0) {
            score += 3;
        }
    }
    
    return score;
}

QList<AssignmentResult> DormitoryManager::batchAssignDormitories()
{
    QList<AssignmentResult> results;
    // 1. 获取所有未分配学生
    QList<StudentPreference> unassigned = getAllUnassignedPreferences();
    if (unassigned.isEmpty()) return results;

    // 2. 获取所有可用床位（宿舍+床位信息）
    struct BedInfo {
        int dormitoryId;
        QString dormitoryName;
        int bedId;
        int bedNumber;
        bool isUpper;
    };
    QList<BedInfo> availableBeds;
    QSqlQuery bedQuery(db);
    bedQuery.prepare("SELECT d.id as dormitory_id, d.name as dormitory_name, b.id as bed_id, b.bed_number, b.is_upper FROM dormitories d JOIN beds b ON d.id = b.dormitory_id WHERE b.is_occupied = 0");
    if (bedQuery.exec()) {
        while (bedQuery.next()) {
            BedInfo info;
            info.dormitoryId = bedQuery.value("dormitory_id").toInt();
            info.dormitoryName = bedQuery.value("dormitory_name").toString();
            info.bedId = bedQuery.value("bed_id").toInt();
            info.bedNumber = bedQuery.value("bed_number").toInt();
            info.isUpper = bedQuery.value("is_upper").toBool();
            availableBeds.append(info);
        }
    }
    if (availableBeds.isEmpty()) return results;

    // 3. 贪心分配：每次分配分数最高的学生-床位对
    while (!unassigned.isEmpty() && !availableBeds.isEmpty()) {
        int bestScore = -1;
        int bestStudentIdx = -1;
        int bestBedIdx = -1;
        AssignmentResult bestResult;
        // 枚举所有学生-床位对
        for (int i = 0; i < unassigned.size(); ++i) {
            int userId = unassigned[i].userId;
            for (int j = 0; j < availableBeds.size(); ++j) {
                int score = calculateMatchScore(availableBeds[j].dormitoryId, userId);
                if (score > bestScore) {
                    bestScore = score;
                    bestStudentIdx = i;
                    bestBedIdx = j;
                    bestResult.userId = userId;
                    bestResult.dormitoryId = availableBeds[j].dormitoryId;
                    bestResult.bedId = availableBeds[j].bedId;
                    bestResult.dormitoryName = availableBeds[j].dormitoryName;
                    bestResult.bedNumber = availableBeds[j].bedNumber;
                    bestResult.isUpper = availableBeds[j].isUpper;
                    bestResult.matchScore = score;
                }
            }
        }
        // 没有可分配项
        if (bestScore <= 0) break;
        // 执行分配
        if (executeAssignment(bestResult)) {
            results.append(bestResult);
            // 移除已分配学生和床位
            unassigned.removeAt(bestStudentIdx);
            availableBeds.removeAt(bestBedIdx);
        } else {
            // 分配失败，移除该学生，避免死循环
            unassigned.removeAt(bestStudentIdx);
        }
    }
    return results;
}

bool DormitoryManager::executeAssignment(const AssignmentResult &result)
{
    if (!validateAssignment(result)) {
        return false;
    }
    
    // 开始事务
    db.transaction();
    
    try {
        // 1. 更新床位状态
        QSqlQuery bedQuery(db);
        bedQuery.prepare("UPDATE beds SET is_occupied = 1 WHERE id = ?");
        bedQuery.addBindValue(result.bedId);
        if (!bedQuery.exec()) {
            throw std::runtime_error("更新床位状态失败");
        }
        
        // 2. 更新宿舍人数
        QSqlQuery dormQuery(db);
        dormQuery.prepare("UPDATE dormitories SET current_count = current_count + 1 WHERE id = ?");
        dormQuery.addBindValue(result.dormitoryId);
        if (!dormQuery.exec()) {
            throw std::runtime_error("更新宿舍人数失败");
        }
        
        // 3. 记录分配
        QSqlQuery assignQuery(db);
        assignQuery.prepare("INSERT INTO assignments (user_id, dormitory_id, bed_id, assigned_date) "
                           "VALUES (?, ?, ?, CURRENT_TIMESTAMP)");
        assignQuery.addBindValue(result.userId);
        assignQuery.addBindValue(result.dormitoryId);
        assignQuery.addBindValue(result.bedId);
        if (!assignQuery.exec()) {
            throw std::runtime_error("记录分配失败");
        }
        
        // 4. 更新宿舍属性（如果宿舍还没有设置性别和作息）
        StudentPreference preference = getUserPreferences(result.userId);
        if (!preference.scheduleType.isEmpty()) {
            updateDormitoryAttributes(result.dormitoryId, "", preference.scheduleType);
        }
        
        // 提交事务
        if (!db.commit()) {
            throw std::runtime_error("提交事务失败");
        }
        
        return true;
    }
    catch (const std::exception& e) {
        db.rollback();
        logError(QString("执行分配失败: %1").arg(e.what()));
        return false;
    }
}

QMap<QString, QVariant> DormitoryManager::getAssignmentStats()
{
    QMap<QString, QVariant> stats;
    
    QSqlQuery query(db);
    query.prepare("SELECT "
                  "COUNT(DISTINCT d.id) as total_dormitories, "
                  "SUM(d.capacity) as total_capacity, "
                  "SUM(d.current_count) as total_assigned, "
                  "COUNT(DISTINCT a.user_id) as assigned_students "
                  "FROM dormitories d "
                  "LEFT JOIN assignments a ON d.id = a.dormitory_id");
    
    if (query.exec() && query.next()) {
        stats["total_dormitories"] = query.value("total_dormitories");
        stats["total_capacity"] = query.value("total_capacity");
        stats["total_assigned"] = query.value("total_assigned");
        stats["assigned_students"] = query.value("assigned_students");
        
        int totalCapacity = query.value("total_capacity").toInt();
        int totalAssigned = query.value("total_assigned").toInt();
        if (totalCapacity > 0) {
            stats["occupancy_rate"] = (totalAssigned * 100.0) / totalCapacity;
        }
    }
    
    return stats;
}

QList<QMap<QString, QVariant>> DormitoryManager::getUnassignedStudents()
{
    QList<QMap<QString, QVariant>> students;
    
    QSqlQuery query(db);
    query.prepare("SELECT u.id, u.name, u.gender, u.major, u.student_id, "
                  "sp.prefer_capacity, sp.schedule_type "
                  "FROM users u "
                  "LEFT JOIN student_preferences sp ON u.id = sp.user_id "
                  "WHERE u.id NOT IN (SELECT user_id FROM assignments)");
    
    if (query.exec()) {
        while (query.next()) {
            QMap<QString, QVariant> student;
            student["id"] = query.value("id");
            student["name"] = query.value("name");
            student["gender"] = query.value("gender");
            student["major"] = query.value("major");
            student["student_id"] = query.value("student_id");
            student["prefer_capacity"] = query.value("prefer_capacity");
            student["schedule_type"] = query.value("schedule_type");
            students.append(student);
        }
    }
    
    return students;
}

QList<QMap<QString, QVariant>> DormitoryManager::getAvailableDormitories()
{
    QList<QMap<QString, QVariant>> dormitories;
    
    QSqlQuery query(db);
    query.prepare("SELECT d.*, (d.capacity - d.current_count) as available_beds "
                  "FROM dormitories d "
                  "WHERE d.current_count < d.capacity "
                  "ORDER BY d.building, d.room_number");
    
    if (query.exec()) {
        while (query.next()) {
            QMap<QString, QVariant> dorm;
            dorm["id"] = query.value("id");
            dorm["name"] = query.value("name");
            dorm["building"] = query.value("building");
            dorm["room_number"] = query.value("room_number");
            dorm["capacity"] = query.value("capacity");
            dorm["current_count"] = query.value("current_count");
            dorm["available_beds"] = query.value("available_beds");
            dorm["gender"] = query.value("gender");
            dorm["schedule_type"] = query.value("schedule_type");
            dormitories.append(dorm);
        }
    }
    
    return dormitories;
}

bool DormitoryManager::updateDormitoryAttributes(int dormId, const QString &gender, const QString &scheduleType)
{
    QSqlQuery query(db);
    query.prepare("UPDATE dormitories SET gender = ?, schedule_type = ? WHERE id = ?");
    query.addBindValue(gender);
    query.addBindValue(scheduleType);
    query.addBindValue(dormId);
    
    return query.exec();
}

QList<int> DormitoryManager::getCompatibleStudents(int dormId)
{
    QList<int> compatibleStudents;
    
    // 获取宿舍信息
    QSqlQuery dormQuery(db);
    dormQuery.prepare("SELECT * FROM dormitories WHERE id = ?");
    dormQuery.addBindValue(dormId);
    if (!dormQuery.exec() || !dormQuery.next()) {
        return compatibleStudents;
    }
    
    QString dormGender = dormQuery.value("gender").toString();
    QString dormSchedule = dormQuery.value("schedule_type").toString();
    
    // 查找兼容的学生
    QSqlQuery studentQuery(db);
    studentQuery.prepare("SELECT u.id FROM users u "
                        "JOIN student_preferences sp ON u.id = sp.user_id "
                        "WHERE u.id NOT IN (SELECT user_id FROM assignments) "
                        "AND (sp.schedule_type = ? OR ? = '') "
                        "AND (u.gender = ? OR ? = '')");
    studentQuery.addBindValue(dormSchedule);
    studentQuery.addBindValue(dormSchedule);
    studentQuery.addBindValue(dormGender);
    studentQuery.addBindValue(dormGender);
    
    if (studentQuery.exec()) {
        while (studentQuery.next()) {
            compatibleStudents.append(studentQuery.value("id").toInt());
        }
    }
    
    return compatibleStudents;
}

bool DormitoryManager::validateAssignment(const AssignmentResult &result)
{
    // 检查学生是否已分配
    QSqlQuery assignQuery(db);
    assignQuery.prepare("SELECT COUNT(*) FROM assignments WHERE user_id = ?");
    assignQuery.addBindValue(result.userId);
    if (assignQuery.exec() && assignQuery.next() && assignQuery.value(0).toInt() > 0) {
        logError("学生已分配宿舍");
        return false;
    }
    
    // 检查床位是否可用
    QSqlQuery bedQuery(db);
    bedQuery.prepare("SELECT COUNT(*) FROM beds WHERE id = ? AND is_occupied = 0");
    bedQuery.addBindValue(result.bedId);
    if (bedQuery.exec() && bedQuery.next() && bedQuery.value(0).toInt() == 0) {
        logError("床位不可用");
        return false;
    }
    
    return true;
}