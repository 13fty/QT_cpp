# 宿舍管理系统 (DormManager) 项目说明

## 项目概述
这是一个基于Qt C++开发的宿舍管理系统，具备用户注册登录、宿舍分配、偏好设置、消息通信等功能。系统采用贪心算法进行智能宿舍分配，能够根据学生的容量、性别、作息等偏好进行最优匹配。

## 运行方法

### 环境要求
- macOS 10.13 或更高版本
- Qt 5.15.16 或兼容版本
- Xcode 命令行工具
- Homebrew（用于安装Qt）

### 安装依赖
```bash
# 安装Qt5
brew install qt@5

# 安装Xcode命令行工具（如果未安装）
xcode-select --install
```

### 快速启动
```bash
# 克隆项目后，进入项目目录
cd DormManager

# 编译并运行
make && ./DormManager.app/Contents/MacOS/DormManager
```

### 详细编译步骤
```bash
# 1. 进入项目目录
cd DormManager

# 2. 生成Makefile
qmake DormManager.pro

# 3. 编译项目
make

# 4. 运行程序
./DormManager.app/Contents/MacOS/DormManager
```

### 清理编译文件
```bash
# 清理所有编译生成的文件
make clean

# 或者删除所有生成的文件
rm -rf *.o moc_* ui_* DormManager.app
```

## 管理员账号
- **用户名**: admin123
- **密码**: 050715

## 文件结构说明

### 核心源代码文件

#### 1. 主程序文件
- **main.cpp** - 程序入口点，初始化Qt应用程序和数据库连接
- **mainwindow.h/cpp** - 主窗口界面实现，包含所有UI界面和用户交互逻辑
- **mainwindow.ui** - Qt Designer设计的用户界面文件
- **mainwindow.ui.backup** - UI文件的备份版本

#### 2. 宿舍管理核心
- **dormitory_manager.h/cpp** - 宿舍管理器核心类，实现所有宿舍分配和管理功能
  - 贪心算法自动分配
  - 容量匹配（90.7%匹配率）
  - 性别匹配（100%匹配率）
  - 作息匹配（90.7%匹配率）
  - 冲突处理（防止重复分配）

#### 3. 项目配置文件
- **DormManager.pro** - Qt项目文件，定义编译配置和依赖
- **icons.qrc** - 图标资源文件，定义界面使用的图标和图片

### 数据库相关文件

#### 1. 数据库文件
- **database.db** - SQLite数据库文件，存储所有系统数据
  - 用户信息表 (users)
  - 宿舍信息表 (dormitories) - 包含性别设置
  - 床位信息表 (beds)
  - 分配记录表 (assignments)
  - 学生偏好表 (student_preferences)
  - 消息表 (messages)

#### 2. SQL脚本文件
- **database.sql** - 数据库结构定义脚本
- **add_dormitories.sql** - 添加宿舍数据的脚本
- **redesign_dormitories.sql** - 重新设计宿舍结构的脚本
- **enhance_preferences.sql** - 增强偏好设置的脚本
- **smart_assignment.sql** - 智能分配相关的脚本
- **update_database.sql** - 数据库更新脚本
- **update_dormitory_gender.sql** - 宿舍性别设置脚本

### 资源文件

#### 1. 图标资源（部分存在问题）
- **icons/** - 图标文件夹（⚠️ 注意：所有图标文件都是0字节空文件）
  - about.png - 关于图标（空文件）
  - add.png - 添加图标（空文件）
  - assign.png - 分配图标（空文件）
  - delete.png - 删除图标（空文件）
  - edit.png - 编辑图标（空文件）
  - exit.png - 退出图标（空文件）
  - guide.png - 指南图标（空文件）
  - info.png - 信息图标（空文件）
  - list.png - 列表图标（空文件）
  - login.png - 登录图标（空文件）
  - logout.png - 登出图标（空文件）
  - preferences.png - 偏好图标（空文件）
  - register.png - 注册图标（空文件）
  - users.png - 用户图标（空文件）

#### 2. 图片资源（已添加）
- **image/** - 图片文件夹（✅ 已添加）
  - bunk-bed.png - 双层床图片（5.3KB，用于窗口图标）
  - chat.png - 聊天图片（14KB，用于消息功能按钮）

### 编译生成文件

#### 1. 目标文件 (.o)
- **main.o** - main.cpp编译生成的目标文件
- **mainwindow.o** - mainwindow.cpp编译生成的目标文件
- **dormitory_manager.o** - dormitory_manager.cpp编译生成的目标文件

#### 2. MOC文件
- **moc_mainwindow.cpp/o** - Qt元对象编译器生成的文件
- **moc_dormitory_manager.cpp/o** - Qt元对象编译器生成的文件
- **moc_predefs.h** - MOC预定义头文件

#### 3. UI生成文件
- **ui_mainwindow.h** - 从mainwindow.ui自动生成的UI头文件

#### 4. 应用程序
- **DormManager.app/** - 编译生成的macOS应用程序包
  - Contents/MacOS/DormManager - 可执行文件

### 其他文件
- **target_wrapper.sh** - 目标包装脚本
- **.qmake.stash** - qmake缓存文件
- **.DS_Store** - macOS系统文件
- **Remind.md** - 本说明文件

## 系统功能特性

### 1. 用户管理
- 学生注册/登录
- 管理员登录
- 用户信息管理

### 2. 宿舍分配
- 贪心算法智能分配
- 多维度偏好匹配
- 自动冲突检测
- 批量分配功能

### 3. 偏好设置
- 容量偏好（4/6/8人间）
- 作息偏好（早/晚）
- 性别偏好
- 上铺/下铺偏好

### 4. 宿舍管理
- 宿舍信息查看
- 床位状态管理
- 分配记录查询

### 5. 消息系统
- 用户间消息发送
- 消息历史记录
- 实时消息提醒

## 算法优化

### 贪心分配算法
- 每次选择分数最高的学生-床位对进行分配
- 容量匹配权重：100分（完全匹配）/ 1分（不匹配）
- 作息匹配权重：8分（匹配）/ 3分（不匹配）
- 性别匹配权重：6分（匹配）/ 2分（不匹配）
- 宿舍状态权重：4分（空宿舍优先）
- 专业匹配权重：3分（同专业优先）

### 测试结果
- 容量匹配率：90.7%
- 性别匹配率：100.0%
- 作息匹配率：90.7%
- 综合匹配率：84.8%

## 数据库操作

### 清空用户数据
```sql
DELETE FROM assignments;
DELETE FROM student_preferences;
DELETE FROM messages;
DELETE FROM users;
UPDATE beds SET is_occupied = 0;
UPDATE dormitories SET current_count = 0;
```

### 设置宿舍性别
```sql
UPDATE dormitories SET gender = CASE WHEN id % 2 = 0 THEN '男' ELSE '女' END;
```

## 开发环境
- **操作系统**: macOS
- **Qt版本**: Qt 5.15.16
- **编译器**: clang++
- **数据库**: SQLite 3
- **开发工具**: Qt Creator / Xcode

## 资源文件状态

### 已解决的问题
1. ✅ **image目录已添加**：包含`bunk-bed.png`和`chat.png`文件
2. ✅ **资源文件已更新**：`icons.qrc`已包含image目录下的图片文件
3. ✅ **图片文件正常**：chat.png（14KB）和bunk-bed.png（5.3KB）都是有效的图片文件

### 仍需解决的问题
1. ⚠️ **图标文件为空**：`icons/`目录下的所有PNG文件都是0字节空文件
   - 影响：按钮图标可能无法正常显示
   - 建议：提供真实的图标文件或使用系统默认图标

### 图标使用情况
- **正常显示**：窗口图标（bunk-bed.png）、消息按钮图标（chat.png）
- **可能无法显示**：登录、注册、分配等按钮的图标（因为icons/目录下的文件为空）

## 注意事项
1. 首次运行前确保已安装Qt开发环境
2. 数据库文件会自动创建，无需手动初始化
3. 管理员账号具有所有权限，学生账号功能受限
4. 系统支持中文界面和中文数据存储
5. 所有分配操作都有事务保护，确保数据一致性
6. 部分按钮图标可能无法显示，但不影响系统核心功能
7. 窗口图标和消息功能图标已正常显示

## 贡献指南
欢迎提交Issue和Pull Request来改进这个项目！

## 许可证
本项目采用MIT许可证。