-- 更新宿舍性别，根据入住学生的性别设置
UPDATE dormitories 
SET gender = (
    SELECT u.gender 
    FROM assignments a 
    JOIN users u ON a.user_id = u.id 
    WHERE a.dormitory_id = dormitories.id 
    LIMIT 1
)
WHERE gender = '未设置';

-- 显示更新结果
SELECT d.id, d.name, d.building, d.room_number, d.gender, d.current_count,
       u.name as student_name, u.gender as student_gender
FROM dormitories d
LEFT JOIN assignments a ON d.id = a.dormitory_id
LEFT JOIN users u ON a.user_id = u.id
WHERE d.current_count > 0
ORDER BY d.id; 