-- 创建新的宿舍表结构
CREATE TABLE IF NOT EXISTS dormitories_new (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    building TEXT NOT NULL,
    room_number INTEGER NOT NULL,
    capacity INTEGER NOT NULL,
    gender TEXT NOT NULL,
    current_count INTEGER DEFAULT 0,
    UNIQUE(building, room_number)
);

-- 复制现有数据到新表
INSERT INTO dormitories_new (id, building, room_number, capacity, gender, current_count)
SELECT id, building, room_number, capacity, gender, 
       (SELECT COUNT(*) FROM assignments WHERE dormitory_id = dormitories.id) as current_count
FROM dormitories;

-- 删除旧表
DROP TABLE IF EXISTS dormitories;

-- 重命名新表
ALTER TABLE dormitories_new RENAME TO dormitories;

-- 创建消息表（如不存在）
CREATE TABLE IF NOT EXISTS messages (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    sender_id INTEGER NOT NULL,
    receiver_id INTEGER NOT NULL,
    content TEXT NOT NULL,
    send_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    is_read BOOLEAN DEFAULT 0
); 