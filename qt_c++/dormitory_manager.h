#ifndef DORMITORY_MANAGER_H
#define DORMITORY_MANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>

struct Dormitory {
    int id;
    QString name;           // 宿舍名称
    QString building;
    QString roomNumber;     // 改为字符串类型
    int capacity;
    int currentCount;
    QString gender;
    QString scheduleType;   // 作息类型
    bool acceptDifferentMajor; // 是否接受不同专业
};

// 学生偏好结构体
struct StudentPreference {
    int userId;
    bool preferUpper;
    int preferCapacity;
    bool acceptDifferentMajor;
    QString scheduleType;
    bool isEarlyBird;
    bool isNightOwl;
    bool isQuiet;
    bool isSocial;
    QString hobbies;
    QString specialNeeds;
    bool preferSameMajor;
    bool preferSameGender;
};

// 分配结果结构体
struct AssignmentResult {
    int userId;
    int dormitoryId;
    int bedId;
    QString dormitoryName;
    int bedNumber;
    bool isUpper;
    int matchScore;
};

class DormitoryManager : public QObject
{
    Q_OBJECT

public:
    explicit DormitoryManager(QSqlDatabase &database, QObject *parent = nullptr);
    ~DormitoryManager();

    // 宿舍分配相关
    bool assignDormitory(int userId);
    bool addDormitory(const QString &name, const QString &building, const QString &roomNumber, 
                     int capacity, const QString &gender, const QString &scheduleType, bool acceptDifferentMajor);
    bool updateDormitory(int dormId, const QString &name, const QString &building, const QString &roomNumber,
                        int capacity, const QString &gender, const QString &scheduleType, bool acceptDifferentMajor);
    bool deleteDormitory(int dormId);

    // 查询相关
    QList<Dormitory> getDormitories();
    QList<QMap<QString, QVariant>> getDormitoryAssignments(int dormId);
    QMap<QString, QVariant> getStudentDormitory(int userId);

    // 床位管理
    bool addBed(int dormId, int bedNumber, bool isUpper);
    bool updateBedStatus(int bedId, bool isOccupied);
    QList<QMap<QString, QVariant>> getAvailableBeds(int dormId);

    // 用户偏好管理（增强版）
    bool saveUserPreferences(int userId, const StudentPreference &preference);
    StudentPreference getUserPreferences(int userId);
    QList<StudentPreference> getAllUnassignedPreferences();

    // 智能分配相关
    AssignmentResult findBestMatch(int userId);
    QList<AssignmentResult> batchAssignDormitories();
    bool executeAssignment(const AssignmentResult &result);
    int calculateMatchScore(int dormId, int userId);

    // 统计和报告
    QMap<QString, QVariant> getAssignmentStats();
    QList<QMap<QString, QVariant>> getUnassignedStudents();
    QList<QMap<QString, QVariant>> getAvailableDormitories();

    // 消息相关接口
    bool sendMessage(int senderId, int receiverId, const QString &content);
    QList<QMap<QString, QVariant>> getMessages(int userId1, int userId2);

private:
    QSqlDatabase db;
    
    // 辅助函数
    bool validateDormitoryData(const QString &name, const QString &building, const QString &roomNumber,
                             int capacity, const QString &gender, const QString &scheduleType);
    bool checkDormitoryExists(const QString &building, const QString &roomNumber);
    bool checkBedExists(int dormId, int bedNumber);
    void logError(const QString &message);
    
    // 智能分配辅助函数
    bool updateDormitoryAttributes(int dormId, const QString &gender, const QString &scheduleType);
    QList<int> getCompatibleStudents(int dormId);
    bool validateAssignment(const AssignmentResult &result);
};

#endif // DORMITORY_MANAGER_H 