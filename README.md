宿舍管理系统 (DormManager)
Qt Platform License

一个基于Qt C++开发的智能宿舍管理系统，采用贪心算法进行最优宿舍分配。

✨ 功能特性
🏠 智能宿舍分配 - 基于贪心算法的多维度匹配
👥 用户管理 - 学生注册登录，管理员权限控制
⚙️ 偏好设置 - 容量、性别、作息等多维度偏好
💬 消息系统 - 用户间实时消息通信
📊 数据统计 - 宿舍分配情况统计和分析
🔒 数据安全 - SQLite数据库，事务保护
🚀 快速开始
环境要求
macOS 10.13 或更高版本
Qt 5.15.16 或兼容版本
Xcode 命令行工具
安装依赖
# 安装Qt5
brew install qt@5

# 安装Xcode命令行工具（如果未安装）
xcode-select --install
编译运行
# 克隆项目
git clone https://github.com/13fty/DormManager.git
cd DormManager

# 编译并运行
make && ./DormManager.app/Contents/MacOS/DormManager
管理员账号
用户名: admin123
密码: 050715
📁 项目结构
DormManager/
├── src/                    # 源代码
│   ├── main.cpp           # 程序入口
│   ├── mainwindow.h/cpp   # 主窗口
│   └── dormitory_manager.h/cpp  # 宿舍管理核心
├── resources/             # 资源文件
│   ├── icons/            # 图标文件
│   ├── image/            # 图片文件
│   └── icons.qrc         # 资源文件配置
├── database/             # 数据库相关
│   ├── database.db       # SQLite数据库
│   └── *.sql            # SQL脚本文件
├── docs/                 # 文档
│   └── Remind.md        # 详细说明文档
└── DormManager.pro      # Qt项目文件
🧠 算法说明
贪心分配算法
系统采用贪心算法进行宿舍分配，每次选择分数最高的学生-床位对进行分配：

容量匹配权重: 100分（完全匹配）/ 1分（不匹配）
作息匹配权重: 8分（匹配）/ 3分（不匹配）
性别匹配权重: 6分（匹配）/ 2分（不匹配）
宿舍状态权重: 4分（空宿舍优先）
专业匹配权重: 3分（同专业优先）
测试结果
容量匹配率: 90.7%
性别匹配率: 100.0%
作息匹配率: 90.7%
综合匹配率: 84.8%
🛠️ 开发
详细编译步骤
# 1. 生成Makefile
qmake DormManager.pro

# 2. 编译项目
make

# 3. 运行程序
./DormManager.app/Contents/MacOS/DormManager
清理编译文件
# 清理所有编译生成的文件
make clean

# 或者删除所有生成的文件
rm -rf *.o moc_* ui_* DormManager.app
📊 数据库操作
清空用户数据
DELETE FROM assignments;
DELETE FROM student_preferences;
DELETE FROM messages;
DELETE FROM users;
UPDATE beds SET is_occupied = 0;
UPDATE dormitories SET current_count = 0;
设置宿舍性别
UPDATE dormitories SET gender = CASE WHEN id % 2 = 0 THEN '男' ELSE '女' END;
🤝 贡献
欢迎提交Issue和Pull Request来改进这个项目！

Fork 这个项目
创建你的特性分支 (git checkout -b feature/AmazingFeature)
提交你的更改 (git commit -m 'Add some AmazingFeature')
推送到分支 (git push origin feature/AmazingFeature)
打开一个 Pull Request
📄 许可证
本项目采用 MIT 许可证 - 查看 LICENSE 文件了解详情。

📞 联系方式
如有问题或建议，请通过以下方式联系：

提交 Issue
发送邮件至: hqq916674@gmail.com
🙏 致谢
感谢所有为这个项目做出贡献的开发者！

⭐ 如果这个项目对你有帮助，请给它一个星标！
