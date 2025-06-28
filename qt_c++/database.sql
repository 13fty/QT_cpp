-- 用户表
CREATE TABLE users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    student_id VARCHAR(20) UNIQUE NOT NULL,  -- 学号
    id_card VARCHAR(18) UNIQUE NOT NULL,     -- 身份证号
    password VARCHAR(255) NOT NULL,          -- 密码
    name VARCHAR(50) NOT NULL,               -- 姓名
    gender VARCHAR(10) NOT NULL,             -- 性别
    major VARCHAR(100) NOT NULL,             -- 专业
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- 宿舍表
CREATE TABLE dormitories (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name VARCHAR(50) NOT NULL,               -- 宿舍名称
    building VARCHAR(50) NOT NULL,           -- 楼栋
    room_number VARCHAR(20) NOT NULL,        -- 房间号
    capacity INTEGER NOT NULL,               -- 容量（4/6/8人）
    current_count INTEGER DEFAULT 0,         -- 当前人数
    gender VARCHAR(10) NOT NULL,             -- 性别要求
    schedule_type VARCHAR(10) NOT NULL,      -- 作息类型（早/晚）
    accept_different_major BOOLEAN DEFAULT 0, -- 是否接受不同专业
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    UNIQUE(building, room_number)
);

-- 床位表
CREATE TABLE beds (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    dormitory_id INTEGER NOT NULL,           -- 所属宿舍ID
    bed_number INTEGER NOT NULL,             -- 床位号
    is_upper BOOLEAN NOT NULL,               -- 是否上铺
    is_occupied BOOLEAN DEFAULT 0,           -- 是否已占用
    FOREIGN KEY (dormitory_id) REFERENCES dormitories(id),
    UNIQUE(dormitory_id, bed_number)
);

-- 学生偏好表
CREATE TABLE student_preferences (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER NOT NULL,                -- 用户ID
    prefer_upper BOOLEAN,                    -- 偏好上铺
    prefer_capacity INTEGER,                 -- 偏好宿舍容量
    accept_different_major BOOLEAN DEFAULT 0, -- 是否接受不同专业
    hobbies TEXT,                            -- 爱好（JSON格式存储）
    FOREIGN KEY (user_id) REFERENCES users(id)
);

-- 分配记录表
CREATE TABLE assignments (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER NOT NULL,                -- 用户ID
    dormitory_id INTEGER NOT NULL,           -- 宿舍ID
    bed_id INTEGER NOT NULL,                 -- 床位ID
    assigned_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES users(id),
    FOREIGN KEY (dormitory_id) REFERENCES dormitories(id),
    FOREIGN KEY (bed_id) REFERENCES beds(id)
);

-- 消息表
CREATE TABLE messages (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    sender_id INTEGER NOT NULL,           -- 发送者用户ID
    receiver_id INTEGER NOT NULL,         -- 接收者用户ID
    content TEXT NOT NULL,                -- 消息内容
    send_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP, -- 发送时间
    is_read BOOLEAN DEFAULT 0             -- 是否已读
    FOREIGN KEY (sender_id) REFERENCES users(id),
    FOREIGN KEY (receiver_id) REFERENCES users(id)
); 