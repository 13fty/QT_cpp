-- 删除现有的宿舍数据（包括相关的床位和分配记录）
DELETE FROM assignments WHERE dormitory_id IN (SELECT id FROM dormitories);
DELETE FROM beds WHERE dormitory_id IN (SELECT id FROM dormitories);
DELETE FROM dormitories;

-- 重置自增ID
DELETE FROM sqlite_sequence WHERE name='dormitories';
DELETE FROM sqlite_sequence WHERE name='beds';
DELETE FROM sqlite_sequence WHERE name='assignments';

-- 重新设计：只设定宿舍基础信息，不预设性别和作息时间
-- 60间宿舍，4人寝、6人寝、8人寝各20间

-- 4人寝 (20间) - 1号楼
INSERT INTO dormitories (name, building, room_number, capacity, current_count, gender, schedule_type, accept_different_major) VALUES
('1号楼101', '1', '101', 4, 0, '', '', 1),
('1号楼102', '1', '102', 4, 0, '', '', 1),
('1号楼103', '1', '103', 4, 0, '', '', 1),
('1号楼104', '1', '104', 4, 0, '', '', 1),
('1号楼105', '1', '105', 4, 0, '', '', 1),
('1号楼106', '1', '106', 4, 0, '', '', 1),
('1号楼107', '1', '107', 4, 0, '', '', 1),
('1号楼108', '1', '108', 4, 0, '', '', 1),
('1号楼201', '1', '201', 4, 0, '', '', 1),
('1号楼202', '1', '202', 4, 0, '', '', 1),
('1号楼203', '1', '203', 4, 0, '', '', 1),
('1号楼204', '1', '204', 4, 0, '', '', 1),
('1号楼205', '1', '205', 4, 0, '', '', 1),
('1号楼206', '1', '206', 4, 0, '', '', 1),
('1号楼207', '1', '207', 4, 0, '', '', 1),
('1号楼208', '1', '208', 4, 0, '', '', 1),
('1号楼301', '1', '301', 4, 0, '', '', 1),
('1号楼302', '1', '302', 4, 0, '', '', 1),
('1号楼303', '1', '303', 4, 0, '', '', 1),
('1号楼304', '1', '304', 4, 0, '', '', 1),
('1号楼305', '1', '305', 4, 0, '', '', 1);

-- 6人寝 (20间) - 2号楼
INSERT INTO dormitories (name, building, room_number, capacity, current_count, gender, schedule_type, accept_different_major) VALUES
('2号楼101', '2', '101', 6, 0, '', '', 1),
('2号楼102', '2', '102', 6, 0, '', '', 1),
('2号楼103', '2', '103', 6, 0, '', '', 1),
('2号楼104', '2', '104', 6, 0, '', '', 1),
('2号楼105', '2', '105', 6, 0, '', '', 1),
('2号楼106', '2', '106', 6, 0, '', '', 1),
('2号楼107', '2', '107', 6, 0, '', '', 1),
('2号楼108', '2', '108', 6, 0, '', '', 1),
('2号楼201', '2', '201', 6, 0, '', '', 1),
('2号楼202', '2', '202', 6, 0, '', '', 1),
('2号楼203', '2', '203', 6, 0, '', '', 1),
('2号楼204', '2', '204', 6, 0, '', '', 1),
('2号楼205', '2', '205', 6, 0, '', '', 1),
('2号楼206', '2', '206', 6, 0, '', '', 1),
('2号楼207', '2', '207', 6, 0, '', '', 1),
('2号楼208', '2', '208', 6, 0, '', '', 1),
('2号楼301', '2', '301', 6, 0, '', '', 1),
('2号楼302', '2', '302', 6, 0, '', '', 1),
('2号楼303', '2', '303', 6, 0, '', '', 1),
('2号楼304', '2', '304', 6, 0, '', '', 1),
('2号楼305', '2', '305', 6, 0, '', '', 1);

-- 8人寝 (20间) - 3号楼
INSERT INTO dormitories (name, building, room_number, capacity, current_count, gender, schedule_type, accept_different_major) VALUES
('3号楼101', '3', '101', 8, 0, '', '', 1),
('3号楼102', '3', '102', 8, 0, '', '', 1),
('3号楼103', '3', '103', 8, 0, '', '', 1),
('3号楼104', '3', '104', 8, 0, '', '', 1),
('3号楼105', '3', '105', 8, 0, '', '', 1),
('3号楼106', '3', '106', 8, 0, '', '', 1),
('3号楼107', '3', '107', 8, 0, '', '', 1),
('3号楼108', '3', '108', 8, 0, '', '', 1),
('3号楼201', '3', '201', 8, 0, '', '', 1),
('3号楼202', '3', '202', 8, 0, '', '', 1),
('3号楼203', '3', '203', 8, 0, '', '', 1),
('3号楼204', '3', '204', 8, 0, '', '', 1),
('3号楼205', '3', '205', 8, 0, '', '', 1),
('3号楼206', '3', '206', 8, 0, '', '', 1),
('3号楼207', '3', '207', 8, 0, '', '', 1),
('3号楼208', '3', '208', 8, 0, '', '', 1),
('3号楼301', '3', '301', 8, 0, '', '', 1),
('3号楼302', '3', '302', 8, 0, '', '', 1),
('3号楼303', '3', '303', 8, 0, '', '', 1),
('3号楼304', '3', '304', 8, 0, '', '', 1),
('3号楼305', '3', '305', 8, 0, '', '', 1);

-- 为所有宿舍添加床位
-- 4人寝床位
INSERT INTO beds (dormitory_id, bed_number, is_upper, is_occupied)
SELECT d.id, 1, 0, 0 FROM dormitories d WHERE d.capacity = 4
UNION ALL
SELECT d.id, 2, 1, 0 FROM dormitories d WHERE d.capacity = 4
UNION ALL
SELECT d.id, 3, 0, 0 FROM dormitories d WHERE d.capacity = 4
UNION ALL
SELECT d.id, 4, 1, 0 FROM dormitories d WHERE d.capacity = 4;

-- 6人寝床位
INSERT INTO beds (dormitory_id, bed_number, is_upper, is_occupied)
SELECT d.id, 1, 0, 0 FROM dormitories d WHERE d.capacity = 6
UNION ALL
SELECT d.id, 2, 1, 0 FROM dormitories d WHERE d.capacity = 6
UNION ALL
SELECT d.id, 3, 0, 0 FROM dormitories d WHERE d.capacity = 6
UNION ALL
SELECT d.id, 4, 1, 0 FROM dormitories d WHERE d.capacity = 6
UNION ALL
SELECT d.id, 5, 0, 0 FROM dormitories d WHERE d.capacity = 6
UNION ALL
SELECT d.id, 6, 1, 0 FROM dormitories d WHERE d.capacity = 6;

-- 8人寝床位
INSERT INTO beds (dormitory_id, bed_number, is_upper, is_occupied)
SELECT d.id, 1, 0, 0 FROM dormitories d WHERE d.capacity = 8
UNION ALL
SELECT d.id, 2, 1, 0 FROM dormitories d WHERE d.capacity = 8
UNION ALL
SELECT d.id, 3, 0, 0 FROM dormitories d WHERE d.capacity = 8
UNION ALL
SELECT d.id, 4, 1, 0 FROM dormitories d WHERE d.capacity = 8
UNION ALL
SELECT d.id, 5, 0, 0 FROM dormitories d WHERE d.capacity = 8
UNION ALL
SELECT d.id, 6, 1, 0 FROM dormitories d WHERE d.capacity = 8
UNION ALL
SELECT d.id, 7, 0, 0 FROM dormitories d WHERE d.capacity = 8
UNION ALL
SELECT d.id, 8, 1, 0 FROM dormitories d WHERE d.capacity = 8; 