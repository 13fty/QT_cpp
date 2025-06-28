-- 增强学生偏好表，添加更多偏好选项
-- 先删除现有表（如果存在）
DROP TABLE IF EXISTS student_preferences;

-- 重新创建增强的学生偏好表
CREATE TABLE student_preferences (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER NOT NULL,
    
    -- 基础偏好
    prefer_upper BOOLEAN,                    -- 偏好上铺
    prefer_capacity INTEGER,                 -- 偏好宿舍容量 (4/6/8)
    accept_different_major BOOLEAN DEFAULT 1, -- 是否接受不同专业
    
    -- 作息偏好
    schedule_type VARCHAR(10),               -- 作息类型 (早/晚/无要求)
    
    -- 生活习惯偏好
    is_early_bird BOOLEAN,                   -- 是否早起
    is_night_owl BOOLEAN,                    -- 是否夜猫子
    is_quiet BOOLEAN,                        -- 是否喜欢安静
    is_social BOOLEAN,                       -- 是否社交活跃
    
    -- 兴趣爱好
    hobbies TEXT,                            -- 爱好（JSON格式存储）
    
    -- 特殊需求
    special_needs TEXT,                      -- 特殊需求（如身体原因等）
    
    -- 室友偏好
    prefer_same_major BOOLEAN DEFAULT 0,     -- 偏好同专业
    prefer_same_gender BOOLEAN DEFAULT 1,    -- 偏好同性
    
    -- 时间戳
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    
    FOREIGN KEY (user_id) REFERENCES users(id)
);

-- 创建索引提高查询性能
CREATE INDEX idx_preferences_user_id ON student_preferences(user_id);
CREATE INDEX idx_preferences_capacity ON student_preferences(prefer_capacity);
CREATE INDEX idx_preferences_schedule ON student_preferences(schedule_type); 