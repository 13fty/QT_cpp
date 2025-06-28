-- 智能宿舍分配算法
-- 这个脚本包含分配逻辑，可以在应用程序中实现

-- 1. 获取学生偏好信息的视图
CREATE VIEW student_preference_view AS
SELECT 
    u.id as user_id,
    u.name,
    u.gender,
    u.major,
    sp.prefer_upper,
    sp.prefer_capacity,
    sp.accept_different_major,
    sp.schedule_type,
    sp.is_early_bird,
    sp.is_night_owl,
    sp.is_quiet,
    sp.is_social,
    sp.prefer_same_major,
    sp.prefer_same_gender,
    sp.hobbies,
    sp.special_needs
FROM users u
LEFT JOIN student_preferences sp ON u.id = sp.user_id
WHERE u.id NOT IN (SELECT user_id FROM assignments);

-- 2. 获取可用宿舍的视图
CREATE VIEW available_dormitories_view AS
SELECT 
    d.id,
    d.name,
    d.building,
    d.room_number,
    d.capacity,
    d.current_count,
    d.gender,
    d.schedule_type,
    d.accept_different_major,
    (d.capacity - d.current_count) as available_beds
FROM dormitories d
WHERE d.current_count < d.capacity;

-- 3. 获取可用床位的视图
CREATE VIEW available_beds_view AS
SELECT 
    b.id as bed_id,
    b.dormitory_id,
    b.bed_number,
    b.is_upper,
    d.name as dormitory_name,
    d.capacity,
    d.current_count,
    d.gender,
    d.schedule_type
FROM beds b
JOIN dormitories d ON b.dormitory_id = d.id
WHERE b.is_occupied = 0;

-- 4. 分配算法示例查询（可以在应用程序中实现）

-- 示例1：为特定学生找到最佳匹配的宿舍
-- 参数：@user_id, @prefer_capacity, @schedule_type, @gender
/*
SELECT 
    d.id,
    d.name,
    d.capacity,
    d.current_count,
    d.gender,
    d.schedule_type,
    -- 计算匹配度分数
    CASE 
        WHEN d.capacity = ? THEN 10  -- 容量匹配
        ELSE 5
    END +
    CASE 
        WHEN d.schedule_type = ? OR d.schedule_type = '' THEN 8  -- 作息匹配
        ELSE 3
    END +
    CASE 
        WHEN d.gender = ? OR d.gender = '' THEN 6  -- 性别匹配
        ELSE 2
    END +
    CASE 
        WHEN d.current_count = 0 THEN 4  -- 空宿舍优先
        ELSE 0
    END as match_score
FROM dormitories d
WHERE d.current_count < d.capacity
ORDER BY match_score DESC, d.current_count ASC
LIMIT 1;
*/

-- 示例2：批量分配算法（按优先级排序）
/*
-- 第一步：按容量分组学生
-- 第二步：按作息时间分组
-- 第三步：按性别分组
-- 第四步：分配宿舍
*/

-- 5. 分配结果统计视图
CREATE VIEW assignment_stats_view AS
SELECT 
    d.building,
    d.capacity,
    COUNT(a.id) as assigned_count,
    d.capacity * COUNT(DISTINCT d.id) as total_capacity,
    ROUND(COUNT(a.id) * 100.0 / (d.capacity * COUNT(DISTINCT d.id)), 2) as occupancy_rate
FROM dormitories d
LEFT JOIN assignments a ON d.id = a.dormitory_id
GROUP BY d.building, d.capacity;

-- 6. 未分配学生统计
CREATE VIEW unassigned_students_view AS
SELECT 
    u.id,
    u.name,
    u.gender,
    u.major,
    sp.prefer_capacity,
    sp.schedule_type
FROM users u
LEFT JOIN student_preferences sp ON u.id = sp.user_id
WHERE u.id NOT IN (SELECT user_id FROM assignments);

-- 7. 宿舍分配建议查询
-- 这个查询可以帮助管理员了解分配情况
SELECT 
    '未分配学生' as category,
    COUNT(*) as count
FROM unassigned_students_view
UNION ALL
SELECT 
    '已分配学生' as category,
    COUNT(*) as count
FROM assignments
UNION ALL
SELECT 
    '可用床位' as category,
    COUNT(*) as count
FROM available_beds_view; 