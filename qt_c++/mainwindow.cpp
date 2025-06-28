#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QInputDialog>
#include <QApplication>
#include <QDebug>
#include <QSysInfo>
#include <QIcon>
#include <QFont>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QGuiApplication>
#include <QScreen>
#include <QRect>
#include <QEasingCurve>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    // 设置窗口图标和标题
    setWindowIcon(QIcon(":/icons/image/bunk-bed.png"));
    setWindowTitle("宿舍分配系统- 智能宿舍管理平台");
    
    // 设置窗口最小尺寸
    setMinimumSize(900, 700);
    
    // 初始化数据库
    if (!initDatabase()) {
        QMessageBox::critical(this, "错误", "数据库初始化失败！");
        return;
    }
    dormManager = new DormitoryManager(db, this);
    messageCheckTimer = new QTimer(this);
    connect(messageCheckTimer, &QTimer::timeout, this, &MainWindow::checkNewMessages);
    // 信号槽连接
    connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::on_loginButton_clicked);
    connect(ui->registerButton, &QPushButton::clicked, this, &MainWindow::on_registerButton_clicked);
    connect(ui->submitRegisterButton, &QPushButton::clicked, this, &MainWindow::on_submitRegisterButton_clicked);
    connect(ui->backToLoginButton, &QPushButton::clicked, this, &MainWindow::on_backToLoginButton_clicked);
    connect(ui->logoutButton, &QPushButton::clicked, this, &MainWindow::on_logoutButton_clicked);
    connect(ui->addDormitoryButton, &QPushButton::clicked, this, &MainWindow::on_addDormitoryButton_clicked);
    connect(ui->editDormitoryButton, &QPushButton::clicked, this, &MainWindow::on_editDormitoryButton_clicked);
    connect(ui->deleteDormitoryButton, &QPushButton::clicked, this, &MainWindow::on_deleteDormitoryButton_clicked);
    connect(ui->sendMessageButton, &QPushButton::clicked, this, &MainWindow::on_sendMessageButton_clicked);
    connect(ui->studentMessageCenterButton, &QPushButton::clicked, this, &MainWindow::on_viewMessagesButton_clicked);
    connect(ui->messageCenterButton, &QPushButton::clicked, this, &MainWindow::on_viewMessagesButton_clicked);
    connect(ui->studentLogoutButton, &QPushButton::clicked, this, &MainWindow::on_logoutButton_clicked);
    connect(ui->backToHomeButton, &QPushButton::clicked, this, [this]() {
        if (isAdminUser) {
            ui->stackedWidget->setCurrentWidget(ui->dormitoryManagementPage);
            refreshDormitoryList();
        } else {
            ui->stackedWidget->setCurrentWidget(ui->homePage);
            refreshDormitoryList();
        }
    });
    connect(ui->backToHomeButton1, &QPushButton::clicked, this, [this]() {
        if (isAdminUser) {
            ui->stackedWidget->setCurrentWidget(ui->dormitoryManagementPage);
            refreshDormitoryList();
        } else {
            ui->stackedWidget->setCurrentWidget(ui->homePage);
            refreshDormitoryList();
        }
    });
    // 消息中心用户表格选中变化
    if (ui->userTable)
        connect(ui->userTable, &QTableWidget::itemSelectionChanged, this, &MainWindow::refreshMessages);
    // 初始化消息检查定时器
    messageCheckTimer = new QTimer(this);
    connect(messageCheckTimer, &QTimer::timeout, this, &MainWindow::checkNewMessages);
    
    // 初始化消息提醒相关变量
    lastMessageCheck = QDateTime::currentDateTime();
    unreadMessageCount = 0;
    
    setupMessageUI();
    ui->stackedWidget->setCurrentWidget(ui->loginPage);
    // 设置全局样式表
    QString styleSheet = R"(
/* 全局样式 */
QMainWindow {
    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
        stop:0 #f8f9fa, stop:1 #e9ecef);
    font-family: 'PingFang SC', 'Microsoft YaHei', 'Helvetica Neue', Arial, sans-serif;
    color: #495057;
}

/* 菜单栏样式 */
QMenuBar {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 rgba(73, 80, 87, 0.95), stop:1 rgba(52, 58, 64, 0.95));
    color: #f8f9fa;
    font-size: 14px;
    font-weight: 500;
    border: none;
    padding: 4px 0px;
    min-height: 32px;
    backdrop-filter: blur(10px);
}

QMenuBar::item {
    background-color: transparent;
    color: #f8f9fa;
    padding: 8px 16px;
    margin: 2px 1px;
    border-radius: 6px;
    font-weight: 500;
    transition: all 0.2s ease;
}

QMenuBar::item:selected {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #6c757d, stop:1 #495057);
    color: #ffffff;
    border: 1px solid #495057;
    transform: translateY(-1px);
    box-shadow: 0 4px 12px rgba(108, 117, 125, 0.3);
}

QMenuBar::item:pressed {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #495057, stop:1 #343a40);
    color: #ffffff;
    transform: translateY(0px);
}

/* 下拉菜单样式 */
QMenu {
    background: rgba(255, 255, 255, 0.95);
    border: 1px solid rgba(222, 226, 230, 0.3);
    border-radius: 12px;
    padding: 8px 0px;
    font-size: 14px;
    color: #495057;
    box-shadow: 0 12px 32px rgba(0, 0, 0, 0.1);
    backdrop-filter: blur(15px);
}

QMenu::item {
    background-color: transparent;
    color: #495057;
    padding: 12px 24px;
    margin: 2px 8px;
    border-radius: 8px;
    font-weight: 400;
    min-width: 140px;
    transition: all 0.15s ease;
}

QMenu::item:selected {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #6c757d, stop:1 #495057);
    color: #ffffff;
    transform: translateX(2px);
    box-shadow: 0 4px 12px rgba(108, 117, 125, 0.3);
}

QMenu::item:pressed {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #495057, stop:1 #343a40);
    color: #ffffff;
    transform: translateX(2px) translateY(1px);
}

QMenu::separator {
    height: 1px;
    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
        stop:0 transparent, stop:0.5 #dee2e6, stop:1 transparent);
    margin: 6px 16px;
}

/* 堆叠窗口样式 */
QStackedWidget {
    background: transparent;
}

/* 页面容器样式 */
QWidget {
    background: transparent;
}

/* 标签样式 */
QLabel {
    color: #495057;
    font-size: 15px;
    font-weight: 500;
    background: transparent;
    border: none;
}

/* 标题标签样式 */
QLabel#loginTitle, QLabel#registerTitle {
    font-size: 28px;
    font-weight: 700;
    color: #495057;
    text-align: center;
    padding: 20px;
    background: rgba(255, 255, 255, 0.8);
    border-radius: 16px;
    margin: 10px;
    backdrop-filter: blur(10px);
    border: 1px solid rgba(222, 226, 230, 0.5);
}

/* 输入框样式 */
QLineEdit {
    background: rgba(255, 255, 255, 0.9);
    border: 2px solid rgba(222, 226, 230, 0.5);
    border-radius: 12px;
    font-size: 15px;
    padding: 12px 16px;
    color: #495057;
    font-weight: 500;
    backdrop-filter: blur(10px);
    transition: all 0.3s ease;
}

QLineEdit:focus {
    border: 2px solid #6c757d;
    background: rgba(255, 255, 255, 0.95);
    box-shadow: 0 0 0 4px rgba(108, 117, 125, 0.1);
    transform: translateY(-2px);
}

QLineEdit:hover {
    border: 2px solid rgba(108, 117, 125, 0.5);
    background: rgba(255, 255, 255, 0.95);
    transform: translateY(-1px);
}

QLineEdit::placeholder {
    color: #adb5bd;
    font-weight: 400;
}

/* 按钮样式 */
QPushButton {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #adb5bd, stop:1 #6c757d);
    color: #ffffff;
    border: none;
    border-radius: 12px;
    padding: 12px 24px;
    font-size: 15px;
    font-weight: 600;
    text-transform: uppercase;
    letter-spacing: 0.5px;
    transition: all 0.3s ease;
    box-shadow: 0 4px 12px rgba(173, 181, 189, 0.3);
}

QPushButton:hover {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #ced4da, stop:1 #adb5bd);
    transform: translateY(-2px);
    box-shadow: 0 8px 20px rgba(173, 181, 189, 0.4);
}

QPushButton:pressed {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #6c757d, stop:1 #495057);
    transform: translateY(0px);
    box-shadow: 0 2px 8px rgba(173, 181, 189, 0.3);
}

/* 次要按钮样式 */
QPushButton#registerButton, QPushButton#backToLoginButton {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #adb5bd, stop:1 #6c757d);
    box-shadow: 0 4px 12px rgba(173, 181, 189, 0.3);
}

QPushButton#registerButton:hover, QPushButton#backToLoginButton:hover {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #ced4da, stop:1 #adb5bd);
    box-shadow: 0 8px 20px rgba(173, 181, 189, 0.4);
}

/* 登录按钮绿色样式 */
QPushButton#loginButton {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #28a745, stop:1 #1e7e34);
    box-shadow: 0 4px 12px rgba(40, 167, 69, 0.3);
}

QPushButton#loginButton:hover {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #34ce57, stop:1 #28a745);
    box-shadow: 0 8px 20px rgba(40, 167, 69, 0.4);
}

QPushButton#loginButton:pressed {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #1e7e34, stop:1 #155724);
    box-shadow: 0 2px 8px rgba(40, 167, 69, 0.3);
}

/* 管理员主页按钮样式 */
QPushButton#addDormitoryButton {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #28a745, stop:1 #1e7e34);
    box-shadow: 0 4px 12px rgba(40, 167, 69, 0.3);
}

QPushButton#addDormitoryButton:hover {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #34ce57, stop:1 #28a745);
    box-shadow: 0 8px 20px rgba(40, 167, 69, 0.4);
}

QPushButton#editDormitoryButton {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #007bff, stop:1 #0056b3);
    box-shadow: 0 4px 12px rgba(0, 123, 255, 0.3);
}

QPushButton#editDormitoryButton:hover {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #17a2b8, stop:1 #007bff);
    box-shadow: 0 8px 20px rgba(0, 123, 255, 0.4);
}

QPushButton#deleteDormitoryButton {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #dc3545, stop:1 #c82333);
    box-shadow: 0 4px 12px rgba(220, 53, 69, 0.3);
}

QPushButton#deleteDormitoryButton:hover {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #e4606d, stop:1 #dc3545);
    box-shadow: 0 8px 20px rgba(220, 53, 69, 0.4);
}

QPushButton#assignDormitoryButton {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #ffc107, stop:1 #e0a800);
    color: #212529;
    box-shadow: 0 4px 12px rgba(255, 193, 7, 0.3);
}

QPushButton#assignDormitoryButton:hover {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #ffca2c, stop:1 #ffc107);
    box-shadow: 0 8px 20px rgba(255, 193, 7, 0.4);
}

QPushButton#messageCenterButton {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #6f42c1, stop:1 #5a2d91);
    box-shadow: 0 4px 12px rgba(111, 66, 193, 0.3);
}

QPushButton#messageCenterButton:hover {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #8250df, stop:1 #6f42c1);
    box-shadow: 0 8px 20px rgba(111, 66, 193, 0.4);
}

/* 学生消息中心按钮绿色样式 */
QPushButton#studentMessageCenterButton {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #28a745, stop:1 #1e7e34);
    box-shadow: 0 4px 12px rgba(40, 167, 69, 0.3);
}

QPushButton#studentMessageCenterButton:hover {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #34ce57, stop:1 #28a745);
    box-shadow: 0 8px 20px rgba(40, 167, 69, 0.4);
}

/* 管理员界面按钮样式 */
QPushButton#logoutButton {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #fd7e14, stop:1 #e55a00);
    box-shadow: 0 4px 12px rgba(253, 126, 20, 0.3);
}

QPushButton#logoutButton:hover {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #ff8a1f, stop:1 #fd7e14);
    box-shadow: 0 8px 20px rgba(253, 126, 20, 0.4);
}

QPushButton#backToHomeButton, QPushButton#backToHomeButton1 {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #20c997, stop:1 #17a2b8);
    box-shadow: 0 4px 12px rgba(32, 201, 151, 0.3);
}

QPushButton#backToHomeButton:hover, QPushButton#backToHomeButton1:hover {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #2dd4bf, stop:1 #20c997);
    box-shadow: 0 8px 20px rgba(32, 201, 151, 0.4);
}

/* 危险按钮样式 */
QPushButton#studentLogoutButton {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #dc3545, stop:1 #c82333);
    box-shadow: 0 4px 12px rgba(220, 53, 69, 0.3);
}

QPushButton#studentLogoutButton:hover {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #e4606d, stop:1 #dc3545);
    box-shadow: 0 8px 20px rgba(220, 53, 69, 0.4);
}

/* 成功按钮样式 */
QPushButton#submitRegisterButton, QPushButton#submitPreferencesButton {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #28a745, stop:1 #1e7e34);
    box-shadow: 0 4px 12px rgba(40, 167, 69, 0.3);
}

QPushButton#submitRegisterButton:hover, QPushButton#submitPreferencesButton:hover {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #34ce57, stop:1 #28a745);
    box-shadow: 0 8px 20px rgba(40, 167, 69, 0.4);
}

/* 表格样式 */
QTableWidget {
    background: rgba(255, 255, 255, 0.9);
    border: 1px solid rgba(222, 226, 230, 0.3);
    border-radius: 12px;
    gridline-color: rgba(222, 226, 230, 0.3);
    selection-background-color: rgba(108, 117, 125, 0.2);
    selection-color: #495057;
    alternate-background-color: rgba(248, 249, 250, 0.5);
    backdrop-filter: blur(10px);
}

QTableWidget::item {
    padding: 8px;
    border-radius: 6px;
    margin: 2px;
}

QTableWidget::item:selected {
    background: rgba(108, 117, 125, 0.3);
    color: #495057;
    border-radius: 6px;
}

QHeaderView::section {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 rgba(73, 80, 87, 0.8), stop:1 rgba(52, 58, 64, 0.8));
    color: #ffffff;
    font-weight: 600;
    border: none;
    border-bottom: 1px solid rgba(255, 255, 255, 0.2);
    padding: 12px 8px;
    border-radius: 0px;
}

QHeaderView::section:hover {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 rgba(108, 117, 125, 0.8), stop:1 rgba(73, 80, 87, 0.8));
}

/* 分组框样式 */
QGroupBox {
    background: rgba(255, 255, 255, 0.9);
    border: 2px solid rgba(222, 226, 230, 0.3);
    border-radius: 16px;
    margin-top: 20px;
    font-weight: 600;
    color: #495057;
    padding-top: 20px;
    backdrop-filter: blur(10px);
    box-shadow: 0 8px 24px rgba(0, 0, 0, 0.05);
}

QGroupBox::title {
    subcontrol-origin: margin;
    left: 16px;
    padding: 0 12px;
    color: #6c757d;
    font-size: 16px;
    font-weight: 700;
    background: rgba(255, 255, 255, 0.9);
    border-radius: 8px;
    backdrop-filter: blur(10px);
}

/* 列表样式 */
QListWidget {
    background: rgba(255, 255, 255, 0.9);
    border: 1px solid rgba(222, 226, 230, 0.3);
    border-radius: 12px;
    padding: 8px;
    backdrop-filter: blur(10px);
}

QListWidget::item {
    background: transparent;
    border: none;
    padding: 4px;
    margin: 2px;
    border-radius: 8px;
}

QListWidget::item:selected {
    background: rgba(108, 117, 125, 0.2);
    border-radius: 8px;
}

/* 滚动条样式 */
QScrollBar:vertical {
    background: rgba(255, 255, 255, 0.3);
    width: 12px;
    border-radius: 6px;
    margin: 0px;
}

QScrollBar::handle:vertical {
    background: rgba(108, 117, 125, 0.6);
    border-radius: 6px;
    min-height: 20px;
    margin: 2px;
}

QScrollBar::handle:vertical:hover {
    background: rgba(108, 117, 125, 0.8);
}

QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
    height: 0px;
}

QScrollBar:horizontal {
    background: rgba(255, 255, 255, 0.3);
    height: 12px;
    border-radius: 6px;
    margin: 0px;
}

QScrollBar::handle:horizontal {
    background: rgba(108, 117, 125, 0.6);
    border-radius: 6px;
    min-width: 20px;
    margin: 2px;
}

QScrollBar::handle:horizontal:hover {
    background: rgba(108, 117, 125, 0.8);
}

QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {
    width: 0px;
}

/* 单选按钮样式 */
QRadioButton {
    color: #495057;
    font-size: 14px;
    font-weight: 500;
    spacing: 8px;
}

QRadioButton::indicator {
    width: 18px;
    height: 18px;
    border-radius: 9px;
    border: 2px solid #adb5bd;
    background: rgba(255, 255, 255, 0.9);
}

QRadioButton::indicator:checked {
    border: 2px solid #6c757d;
    background: #6c757d;
}

QRadioButton::indicator:checked::after {
    content: "";
    width: 6px;
    height: 6px;
    border-radius: 3px;
    background: #ffffff;
    margin: 4px;
}

/* 复选框样式 */
QCheckBox {
    color: #495057;
    font-size: 14px;
    font-weight: 500;
    spacing: 8px;
}

QCheckBox::indicator {
    width: 18px;
    height: 18px;
    border-radius: 4px;
    border: 2px solid #adb5bd;
    background: rgba(255, 255, 255, 0.9);
}

QCheckBox::indicator:checked {
    border: 2px solid #6c757d;
    background: #6c757d;
}

QCheckBox::indicator:checked::after {
    content: "✓";
    color: #ffffff;
    font-weight: bold;
    font-size: 12px;
    margin: 1px;
}

/* 消息框样式 */
QMessageBox {
    background: rgba(255, 255, 255, 0.95);
    border: 1px solid rgba(222, 226, 230, 0.3);
    border-radius: 16px;
    backdrop-filter: blur(15px);
}

QMessageBox QLabel {
    color: #495057;
    font-size: 14px;
    font-weight: 500;
}

QMessageBox QPushButton {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #6c757d, stop:1 #495057);
    color: #ffffff;
    border: none;
    border-radius: 8px;
    padding: 8px 16px;
    font-size: 13px;
    font-weight: 600;
    min-width: 80px;
}

QMessageBox QPushButton:hover {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #868e96, stop:1 #6c757d);
}

/* 输入对话框样式 */
QInputDialog {
    background: rgba(255, 255, 255, 0.95);
    border: 1px solid rgba(222, 226, 230, 0.3);
    border-radius: 16px;
    backdrop-filter: blur(15px);
}

QInputDialog QLabel {
    color: #495057;
    font-size: 14px;
    font-weight: 500;
}

QInputDialog QLineEdit {
    background: rgba(255, 255, 255, 0.9);
    border: 2px solid rgba(222, 226, 230, 0.3);
    border-radius: 8px;
    padding: 8px 12px;
    font-size: 14px;
}

QInputDialog QLineEdit:focus {
    border: 2px solid #6c757d;
    background: rgba(255, 255, 255, 0.95);
}

QInputDialog QPushButton {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #6c757d, stop:1 #495057);
    color: #ffffff;
    border: none;
    border-radius: 8px;
    padding: 8px 16px;
    font-size: 13px;
    font-weight: 600;
    min-width: 80px;
}

QInputDialog QPushButton:hover {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #868e96, stop:1 #6c757d);
}

/* 特殊页面样式 */
QWidget#loginPage, QWidget#registerPage {
    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
        stop:0 rgba(248, 249, 250, 0.9), stop:1 rgba(233, 236, 239, 0.9));
}

QWidget#homePage, QWidget#dormitoryManagementPage, QWidget#messagePage, QWidget#preferencesPage {
    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
        stop:0 rgba(248, 249, 250, 0.7), stop:1 rgba(233, 236, 239, 0.7));
}

/* 欢迎标签样式 */
QLabel#welcomeLabel {
    font-size: 24px;
    font-weight: 700;
    color: #495057;
    text-align: center;
    padding: 20px;
    background: rgba(255, 255, 255, 0.8);
    border-radius: 16px;
    margin: 10px;
    backdrop-filter: blur(10px);
    border: 1px solid rgba(222, 226, 230, 0.5);
}

/* 分配信息标签样式 */
QLabel#assignmentInfoLabel {
    font-size: 16px;
    font-weight: 600;
    color: #495057;
    text-align: center;
    padding: 16px;
    background: rgba(255, 255, 255, 0.8);
    border-radius: 12px;
    margin: 8px;
    backdrop-filter: blur(10px);
    border: 1px solid rgba(222, 226, 230, 0.3);
}

/* 消息输入框样式 */
QLineEdit#messageInput {
    background: rgba(255, 255, 255, 0.9);
    border: 2px solid rgba(222, 226, 230, 0.3);
    border-radius: 20px;
    padding: 12px 20px;
    font-size: 14px;
    margin: 8px;
}

QLineEdit#messageInput:focus {
    border: 2px solid #6c757d;
    background: rgba(255, 255, 255, 0.95);
    box-shadow: 0 0 0 4px rgba(108, 117, 125, 0.1);
}

/* 发送按钮样式 */
QPushButton#sendMessageButton {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #28a745, stop:1 #1e7e34);
    border-radius: 20px;
    padding: 12px 20px;
    font-size: 14px;
    font-weight: 600;
    box-shadow: 0 4px 12px rgba(40, 167, 69, 0.3);
}

QPushButton#sendMessageButton:hover {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #34ce57, stop:1 #28a745);
    box-shadow: 0 8px 20px rgba(40, 167, 69, 0.4);
}

/* 动画效果 */
* {
    transition: all 0.3s cubic-bezier(0.4, 0, 0.2, 1);
}

/* 响应式设计 */
@media (max-width: 800px) {
    QMainWindow {
        min-width: 600px;
    }
    
    QLabel#loginTitle, QLabel#registerTitle {
        font-size: 24px;
        padding: 16px;
    }
    
    QPushButton {
        padding: 10px 20px;
        font-size: 14px;
    }
    
    QLineEdit, QComboBox {
        padding: 10px 14px;
        font-size: 14px;
    }
}
)";
    qApp->setStyleSheet(styleSheet);
    ui->sendMessageButton->setText("发送");
    // 设置用户表格表头，只显示姓名和学号（ID列会被隐藏）
    ui->userTable->setHorizontalHeaderLabels(QStringList() << "ID" << "姓名" << "学号");
    
    // 测试性别选择控件
    qDebug() << "Gender combo box test:";
    qDebug() << "  Item count:" << ui->regGenderInput->count();
    qDebug() << "  Item 0:" << ui->regGenderInput->itemText(0);
    qDebug() << "  Item 1:" << ui->regGenderInput->itemText(1);
    qDebug() << "  Current index:" << ui->regGenderInput->currentIndex();
    qDebug() << "  Current text:" << ui->regGenderInput->currentText();
    qDebug() << "  Is enabled:" << ui->regGenderInput->isEnabled();
    qDebug() << "  Is visible:" << ui->regGenderInput->isVisible();

    connect(ui->assignDormitoryButton, &QPushButton::clicked, this, &MainWindow::on_assignDormitoryButton_clicked);
    connect(ui->submitPreferencesButton, &QPushButton::clicked, this, &MainWindow::on_submitPreferencesButton_clicked);
    connect(ui->startAssignmentButton, &QPushButton::clicked, this, &MainWindow::on_startAssignmentButton_clicked);
    connect(ui->cancelPreferencesButton, &QPushButton::clicked, this, &MainWindow::on_cancelPreferencesButton_clicked);
    
    // 创建菜单项
    setupMenuBar();
    
    // 添加页面切换动画效果
    setupPageTransitions();
    
    // 设置窗口居中显示
    centerWindow();
    
    // 添加启动动画
    QTimer::singleShot(100, this, &MainWindow::showStartupAnimation);
}

MainWindow::~MainWindow()
{
    if (db.isOpen()) db.close();
    delete ui;
}

bool MainWindow::initDatabase()
{
    if (db.isOpen()) db.close();
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.db");
    if (!db.open()) return false;
    // 创建表（略，见原有实现）
    return true;
}

bool MainWindow::isAdmin(const QString &studentId, const QString &password)
{
    return (studentId == "admin123" && password == "050715");
}

QString MainWindow::hashPassword(const QString &password)
{
    return QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());
}

void MainWindow::on_loginButton_clicked()
{
    QString studentId = ui->studentIdInput->text();
    QString password = ui->passwordInput->text();
    
    if (studentId.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "提示", "请输入学号和密码");
        return;
    }
    
    // 先检查是否为管理员账号
    if (isAdmin(studentId, password)) {
        isAdminUser = true;
        currentUserId = -1; // 管理员没有用户ID
        animatePageSwitch(ui->loginPage, ui->dormitoryManagementPage);
        refreshDormitoryList();
        // 启动消息检查定时器
        messageCheckTimer->start(3000); // 每3秒检查一次新消息
        return;
    }
    
    // 不是管理员，查询学生账号
    QSqlQuery query;
    query.prepare("SELECT id, password FROM users WHERE student_id = ?");
    query.addBindValue(studentId);
    
    if (query.exec() && query.next()) {
        QString storedPassword = query.value(1).toString();
        if (storedPassword == hashPassword(password)) {
            currentUserId = query.value(0).toInt();
            isAdminUser = false;
            
            animatePageSwitch(ui->loginPage, ui->homePage);
            refreshDormitoryList();
            // 启动消息检查定时器
            messageCheckTimer->start(3000); // 每3秒检查一次新消息
            // 查询当前用户信息
            QSqlQuery query;
            query.prepare("SELECT name, major, student_id FROM users WHERE id = ?");
            query.addBindValue(currentUserId);
            if (query.exec() && query.next()) {
                QString name = query.value(0).toString();
                QString major = query.value(1).toString();
                QString studentId = query.value(2).toString();
                ui->welcomeLabel->setText(QString("欢迎，%1").arg(name));
                QString info = QString("学号：%1\n姓名：%2\n专业：%3").arg(studentId, name, major);
                ui->userInfoGroup->setTitle("个人信息");
                
                // 确保用户信息组有布局
                QLayout *layout = ui->userInfoGroup->layout();
                if (!layout) {
                    layout = new QVBoxLayout(ui->userInfoGroup);
                    ui->userInfoGroup->setLayout(layout);
                }
                
                // 清空旧内容并添加新内容
                QLayoutItem *child;
                while ((child = layout->takeAt(0)) != nullptr) {
                    if (child->widget()) delete child->widget();
                    delete child;
                }
                QLabel *infoLabel = new QLabel(info, ui->userInfoGroup);
                infoLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
                layout->addWidget(infoLabel);
            }
            
            // 更新宿舍分配显示
            updateAssignmentDisplay();
        } else {
            QMessageBox::warning(this, "登录失败", "密码错误");
        }
    } else {
        QMessageBox::warning(this, "登录失败", "用户不存在");
    }
}

void MainWindow::on_registerButton_clicked()
{
    animatePageSwitch(ui->loginPage, ui->registerPage);
}

QString MainWindow::generateStudentId()
{
    QString year = QDateTime::currentDateTime().toString("yyyy");
    QSqlQuery query;
    
    // 查找当前年份的最大学号
    query.prepare("SELECT MAX(CAST(SUBSTR(student_id, 5, 3) AS INTEGER)) FROM users WHERE student_id LIKE ?");
    query.addBindValue(year + "%");
    
    int maxSequence = 0;
    if (query.exec() && query.next()) {
        maxSequence = query.value(0).toInt();
    }
    
    // 生成新的序列号
    QString sequence = QString::number(maxSequence + 1).rightJustified(3, '0');
    
    // 获取性别标识
    QString gender = ui->regGenderInput->currentText();
    int lastDigit = (gender == "男") ? 1 : 0;
    
    QString studentId = year + sequence + QString::number(lastDigit);
    
    qDebug() << "Generated student ID:" << studentId;
    return studentId;
}

void MainWindow::on_submitRegisterButton_clicked()
{
    QString idCard = ui->regIdCardInput->text();
    QString name = ui->regNameInput->text();
    QString gender = ui->regGenderInput->currentText();
    QString major = ui->regMajorInput->currentText();
    QString password = ui->regPasswordInput->text();
    
    // 调试信息
    qDebug() << "Registration form data:";
    qDebug() << "  ID Card:" << idCard;
    qDebug() << "  Name:" << name;
    qDebug() << "  Gender:" << gender << "(index:" << ui->regGenderInput->currentIndex() << ")";
    qDebug() << "  Major:" << major << "(index:" << ui->regMajorInput->currentIndex() << ")";
    qDebug() << "  Password length:" << password.length();
    
    // 输入验证
    if (idCard.isEmpty() || name.isEmpty() || gender.isEmpty() || major.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "注册失败", "请填写所有必填信息");
        return;
    }
    
    // 身份证号验证
    if (idCard.length() != 18) {
        QMessageBox::warning(this, "注册失败", "身份证号必须是18位");
        return;
    }
    
    // 密码长度验证
    if (password.length() < 6) {
        QMessageBox::warning(this, "注册失败", "密码长度不能少于6位");
        return;
    }
    
    QString studentId = generateStudentId();
    qDebug() << "Registering user with student ID:" << studentId;
    
    QSqlQuery query;
    query.prepare("INSERT INTO users (student_id, id_card, name, gender, major, password) VALUES (?, ?, ?, ?, ?, ?)");
    query.addBindValue(studentId);
    query.addBindValue(idCard);
    query.addBindValue(name);
    query.addBindValue(gender);
    query.addBindValue(major);
    query.addBindValue(hashPassword(password));
    
    if (query.exec()) {
        QMessageBox::information(this, "注册成功", 
            QString("注册成功！\n学号：%1\n请使用学号和密码登录").arg(studentId));
        
        // 清空输入框
        ui->regIdCardInput->clear();
        ui->regNameInput->clear();
        ui->regGenderInput->setCurrentIndex(0);  // 重置为"男"
        ui->regMajorInput->setCurrentIndex(0);   // 重置为第一个专业
        ui->regPasswordInput->clear();
        
        qDebug() << "Form cleared, gender reset to:" << ui->regGenderInput->currentText();
        
        ui->stackedWidget->setCurrentWidget(ui->loginPage);
    } else {
        QString errorMsg = query.lastError().text();
        qDebug() << "Registration failed:" << errorMsg;
        
        if (errorMsg.contains("UNIQUE constraint failed")) {
            if (errorMsg.contains("student_id")) {
                QMessageBox::warning(this, "注册失败", "学号已存在，请重试");
            } else if (errorMsg.contains("id_card")) {
                QMessageBox::warning(this, "注册失败", "身份证号已存在");
            } else {
                QMessageBox::warning(this, "注册失败", "用户信息已存在");
            }
        } else {
            QMessageBox::warning(this, "注册失败", "信息填写有误，请检查后重试");
        }
    }
}

void MainWindow::on_backToLoginButton_clicked()
{
    animatePageSwitch(ui->registerPage, ui->loginPage);
}

void MainWindow::on_logoutButton_clicked()
{
    currentUserId = -1;
    isAdminUser = false;
    ui->stackedWidget->setCurrentWidget(ui->loginPage);
    messageCheckTimer->stop();
}

void MainWindow::on_addDormitoryButton_clicked()
{
    if (!isAdminUser) return;
    QString name = ui->dormitoryNameInput->text();
    QString building = ui->buildingInput->text();
    QString roomNumber = ui->roomNumberInput->text();
    int capacity = ui->capacityInput->currentText().remove("人").toInt();
    QString gender = ui->dormitoryGenderInput->currentText();
    QString scheduleType = ui->scheduleTypeInput->currentText();
    bool acceptDifferentMajor = ui->acceptDifferentMajorCheckBox->isChecked();
    
    if (!name.isEmpty() && !building.isEmpty() && !roomNumber.isEmpty() && 
        dormManager->addDormitory(name, building, roomNumber, capacity, gender, scheduleType, acceptDifferentMajor)) {
        refreshDormitoryList();
        ui->dormitoryNameInput->clear();
        ui->buildingInput->clear();
        ui->roomNumberInput->clear();
        ui->capacityInput->setCurrentIndex(0);
        ui->dormitoryGenderInput->setCurrentIndex(0);
        ui->scheduleTypeInput->setCurrentIndex(0);
        ui->acceptDifferentMajorCheckBox->setChecked(false);
    }
}

void MainWindow::on_editDormitoryButton_clicked()
{
    auto items = ui->dormitoryTable->selectedItems();
    if (items.isEmpty()) return;
    int row = items.first()->row();
    int dormId = ui->dormitoryTable->item(row, 0)->text().toInt();
    QString name = ui->dormitoryNameInput->text();
    QString building = ui->buildingInput->text();
    QString roomNumber = ui->roomNumberInput->text();
    int capacity = ui->capacityInput->currentText().remove("人").toInt();
    QString gender = ui->dormitoryGenderInput->currentText();
    QString scheduleType = ui->scheduleTypeInput->currentText();
    bool acceptDifferentMajor = ui->acceptDifferentMajorCheckBox->isChecked();
    
    if (!name.isEmpty() && !building.isEmpty() && !roomNumber.isEmpty() && 
        dormManager->updateDormitory(dormId, name, building, roomNumber, capacity, gender, scheduleType, acceptDifferentMajor)) {
        refreshDormitoryList();
        ui->dormitoryNameInput->clear();
        ui->buildingInput->clear();
        ui->roomNumberInput->clear();
        ui->capacityInput->setCurrentIndex(0);
        ui->dormitoryGenderInput->setCurrentIndex(0);
        ui->scheduleTypeInput->setCurrentIndex(0);
        ui->acceptDifferentMajorCheckBox->setChecked(false);
    }
}

void MainWindow::on_deleteDormitoryButton_clicked()
{
    if (!isAdminUser) return;
    int row = ui->dormitoryTable->currentRow();
    if (row < 0) return;
    int dormId = ui->dormitoryTable->item(row, 0)->text().toInt();
    if (dormManager->deleteDormitory(dormId)) {
        refreshDormitoryList();
    }
}

void MainWindow::on_sendMessageButton_clicked()
{
    QString content = ui->messageInput->text();
    if (content.isEmpty()) return;
    
    int senderId, receiverId;
    if (isAdminUser) {
        senderId = -1; // 管理员ID
        receiverId = getSelectedUserId();
        if (receiverId == -1) {
            QMessageBox::warning(this, "提示", "请先选择一个学生！");
            return;
        }
    } else {
        senderId = currentUserId;
        receiverId = -1; // 管理员ID
    }
    
    if (dormManager->sendMessage(senderId, receiverId, content)) {
        ui->messageInput->clear();
        refreshMessages();
        // 自动滚动到最新消息
        ui->messageList->scrollToBottom();
        QMessageBox::information(this, "提示", "消息发送成功！");
    } else {
        QMessageBox::warning(this, "发送失败", "消息发送失败");
    }
}

void MainWindow::on_viewMessagesButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->messagePage);
    if (isAdminUser) {
        ui->userTable->setVisible(true);
        loadStudentListForAdmin();
    } else {
        ui->userTable->setVisible(false);
        // 学生直接和管理员聊天，不需要选择
    }
    refreshMessages();
    // 重置未读消息计数
    unreadMessageCount = 0;
}

void MainWindow::on_replyMessageButton_clicked()
{
    on_sendMessageButton_clicked();
}

void MainWindow::refreshMessages()
{
    int otherId;
    if (isAdminUser) {
        otherId = getSelectedUserId();
        if (otherId == -1) {
            // 管理员没有选择学生，清空消息列表
            ui->messageList->clear();
            return;
        }
    } else {
        // 学生固定和管理员聊天
        otherId = -1; // 管理员ID为-1
    }
    
    qDebug() << "refreshMessages: currentUserId=" << currentUserId << ", isAdminUser=" << isAdminUser << ", otherId=" << otherId;
    auto messages = dormManager->getMessages(currentUserId, otherId);
    qDebug() << "messages.size()=" << messages.size();
    
    // 清空消息列表
    ui->messageList->clear();
    
    for (const auto &msg : messages) {
        QString senderName = getUserName(msg["sender_id"].toInt());
        QString content = msg["content"].toString();
        QString time = msg["send_time"].toDateTime().toString("MM-dd hh:mm");
        bool isFromMe = (msg["sender_id"].toInt() == currentUserId);
        
        // 添加消息到聊天界面
        addMessageToChat(senderName, content, time, isFromMe);
        
        // 标记未读消息为已读
        if (msg["receiver_id"].toInt() == currentUserId && !msg["is_read"].toBool()) {
            markMessageAsRead(msg["id"].toInt());
        }
    }
    
    // 自动滚动到最新消息
    ui->messageList->scrollToBottom();
}

void MainWindow::checkNewMessages()
{
    if (currentUserId == -1 && !isAdminUser) return;
    
    // 检查是否有新消息
    QSqlQuery query;
    if (isAdminUser) {
        query.prepare("SELECT COUNT(*) FROM messages WHERE receiver_id = -1 AND is_read = 0");
    } else {
        query.prepare("SELECT COUNT(*) FROM messages WHERE receiver_id = ? AND is_read = 0");
        query.addBindValue(currentUserId);
    }
    
    if (query.exec() && query.next()) {
        int newUnreadCount = query.value(0).toInt();
        
        // 如果未读消息数量增加，且当前不在消息页面，显示提醒
        if (newUnreadCount > unreadMessageCount && 
            ui->stackedWidget->currentWidget() != ui->messagePage) {
            updateMessageNotification();
        }
        
        unreadMessageCount = newUnreadCount;
        
        // 如果在消息页面，自动刷新
        if (ui->stackedWidget->currentWidget() == ui->messagePage) {
            refreshMessages();
        }
    }
}

void MainWindow::setupMessageUI()
{
    // 设置消息列表样式
    ui->messageList->setStyleSheet(
        "QListWidget {"
        "    background-color: #f0f0f0;"
        "    border: none;"
        "    padding: 10px;"
        "}"
        "QListWidget::item {"
        "    background-color: transparent;"
        "    border: none;"
        "    padding: 5px;"
        "}"
    );
    
    // 设置输入框样式
    ui->messageInput->setStyleSheet(
        "QLineEdit {"
        "    border: 1px solid #ddd;"
        "    border-radius: 15px;"
        "    padding: 8px 15px;"
        "    background-color: white;"
        "    font-size: 14px;"
        "}"
    );
    
    // 设置发送按钮样式和图标
    ui->sendMessageButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #007AFF;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 15px;"
        "    padding: 8px 15px;"
        "    font-size: 14px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background-color: #0056CC;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #004499;"
        "}"
    );
    
    // 为消息相关按钮添加图标
    ui->sendMessageButton->setIcon(QIcon(":/icons/image/chat.png"));
    ui->sendMessageButton->setIconSize(QSize(16, 16));
    
    // 为消息中心按钮添加图标
    if (ui->studentMessageCenterButton) {
        ui->studentMessageCenterButton->setIcon(QIcon(":/icons/image/chat.png"));
        ui->studentMessageCenterButton->setIconSize(QSize(16, 16));
    }
    
    if (ui->messageCenterButton) {
        ui->messageCenterButton->setIcon(QIcon(":/icons/image/chat.png"));
        ui->messageCenterButton->setIconSize(QSize(16, 16));
    }
    
    // 为其他功能按钮添加图标
    ui->loginButton->setIcon(QIcon(":/icons/login.png"));
    ui->loginButton->setIconSize(QSize(16, 16));
    
    ui->registerButton->setIcon(QIcon(":/icons/register.png"));
    ui->registerButton->setIconSize(QSize(16, 16));
    
    ui->submitRegisterButton->setIcon(QIcon(":/icons/register.png"));
    ui->submitRegisterButton->setIconSize(QSize(16, 16));
    
    ui->backToLoginButton->setIcon(QIcon(":/icons/login.png"));
    ui->backToLoginButton->setIconSize(QSize(16, 16));
    
    ui->logoutButton->setIcon(QIcon(":/icons/logout.png"));
    ui->logoutButton->setIconSize(QSize(16, 16));
    
    ui->studentLogoutButton->setIcon(QIcon(":/icons/logout.png"));
    ui->studentLogoutButton->setIconSize(QSize(16, 16));
    
    ui->addDormitoryButton->setIcon(QIcon(":/icons/add.png"));
    ui->addDormitoryButton->setIconSize(QSize(16, 16));
    
    ui->editDormitoryButton->setIcon(QIcon(":/icons/edit.png"));
    ui->editDormitoryButton->setIconSize(QSize(16, 16));
    
    ui->deleteDormitoryButton->setIcon(QIcon(":/icons/delete.png"));
    ui->deleteDormitoryButton->setIconSize(QSize(16, 16));
    
    ui->assignDormitoryButton->setIcon(QIcon(":/icons/assign.png"));
    ui->assignDormitoryButton->setIconSize(QSize(16, 16));
    
    ui->submitPreferencesButton->setIcon(QIcon(":/icons/preferences.png"));
    ui->submitPreferencesButton->setIconSize(QSize(16, 16));
    
    ui->startAssignmentButton->setIcon(QIcon(":/icons/assign.png"));
    ui->startAssignmentButton->setIconSize(QSize(16, 16));
    
    ui->cancelPreferencesButton->setIcon(QIcon(":/icons/exit.png"));
    ui->cancelPreferencesButton->setIconSize(QSize(16, 16));
}

void MainWindow::markMessageAsRead(int messageId)
{
    QSqlQuery query;
    query.prepare("UPDATE messages SET is_read = 1 WHERE id = ?");
    query.addBindValue(messageId);
    query.exec();
}

QString MainWindow::getUserName(int userId)
{
    if (userId == -1) return "管理员";
    QSqlQuery query;
    query.prepare("SELECT name FROM users WHERE id = ?");
    query.addBindValue(userId);
    if (query.exec() && query.next()) return query.value(0).toString();
    return "未知用户";
}

void MainWindow::updateMessageNotification()
{
    // 如果当前不在消息页面，显示消息提醒
    if (ui->stackedWidget->currentWidget() != ui->messagePage) {
        QString title = isAdminUser ? "管理员" : "学生";
        QString message = QString("%1，您有 %2 条新消息，请查看消息中心！")
                         .arg(title).arg(unreadMessageCount);
        QMessageBox::information(this, "新消息提醒", message);
    }
}

int MainWindow::getSelectedUserId()
{
    if (!ui->userTable) return -1;
    auto selection = ui->userTable->selectionModel()->selectedRows();
    if (selection.isEmpty()) return -1;
    return ui->userTable->item(selection.first().row(), 0)->text().toInt();
}

void MainWindow::refreshDormitoryList()
{
    ui->dormitoryTable->setRowCount(0);
    QList<Dormitory> dormitories = dormManager->getDormitories();
    for (const Dormitory& dorm : dormitories) {
        int row = ui->dormitoryTable->rowCount();
        ui->dormitoryTable->insertRow(row);
        ui->dormitoryTable->setItem(row, 0, new QTableWidgetItem(QString::number(dorm.id)));
        ui->dormitoryTable->setItem(row, 1, new QTableWidgetItem(dorm.name));
        ui->dormitoryTable->setItem(row, 2, new QTableWidgetItem(dorm.building));
        ui->dormitoryTable->setItem(row, 3, new QTableWidgetItem(dorm.roomNumber));
        ui->dormitoryTable->setItem(row, 4, new QTableWidgetItem(QString::number(dorm.capacity)));
        ui->dormitoryTable->setItem(row, 5, new QTableWidgetItem(dorm.gender));
        ui->dormitoryTable->setItem(row, 6, new QTableWidgetItem(QString::number(dorm.currentCount)));
        ui->dormitoryTable->setItem(row, 7, new QTableWidgetItem(dorm.scheduleType));
        ui->dormitoryTable->setItem(row, 8, new QTableWidgetItem(dorm.acceptDifferentMajor ? "是" : "否"));
    }
    ui->dormitoryTable->hideColumn(0);
}

void MainWindow::loadStudentListForAdmin()
{
    ui->userTable->setRowCount(0);
    ui->userTable->setColumnCount(3);
    ui->userTable->setHorizontalHeaderLabels(QStringList() << "ID" << "姓名" << "学号");
    QSqlQuery query("SELECT id, name, student_id FROM users");
    int row = 0;
    while (query.next()) {
        ui->userTable->insertRow(row);
        ui->userTable->setItem(row, 0, new QTableWidgetItem(QString::number(query.value(0).toInt())));
        ui->userTable->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
        ui->userTable->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
        row++;
    }
    if (row > 0) {
        ui->userTable->selectRow(0);
    }
    // 隐藏ID列，只显示姓名和学号
    ui->userTable->hideColumn(0);
}

void MainWindow::createMessageWidget(const QString &senderName, const QString &content, 
                                   const QString &time, bool isFromMe)
{
    QWidget *messageWidget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(messageWidget);
    
    // 头像（简单的圆形标签）
    QLabel *avatar = new QLabel();
    avatar->setFixedSize(40, 40);
    avatar->setStyleSheet(
        QString("QLabel {"
                "    background-color: %1;"
                "    border-radius: 20px;"
                "    color: white;"
                "    font-weight: bold;"
                "    font-size: 16px;"
                "    qproperty-alignment: AlignCenter;"
                "}").arg(isFromMe ? "#007AFF" : "#8E8E93")
    );
    avatar->setText(senderName.left(1).toUpper());
    
    // 消息内容容器
    QVBoxLayout *contentLayout = new QVBoxLayout();
    
    // 消息气泡
    QLabel *messageLabel = new QLabel(content);
    messageLabel->setWordWrap(true);
    messageLabel->setTextFormat(Qt::PlainText);
    messageLabel->setMaximumWidth(300);
    messageLabel->setStyleSheet(
        QString("QLabel {"
                "    background-color: %1;"
                "    color: %2;"
                "    border-radius: 15px;"
                "    padding: 10px 15px;"
                "    font-size: 14px;"
                "    line-height: 1.4;"
                "}").arg(isFromMe ? "#007AFF" : "white").arg(isFromMe ? "white" : "black")
    );
    
    // 时间标签
    QLabel *timeLabel = new QLabel(time);
    timeLabel->setStyleSheet(
        "QLabel {"
        "    color: #8E8E93;"
        "    font-size: 12px;"
        "    padding: 2px 0px;"
        "}"
    );
    timeLabel->setAlignment(isFromMe ? Qt::AlignRight : Qt::AlignLeft);
    
    contentLayout->addWidget(messageLabel);
    contentLayout->addWidget(timeLabel);
    
    // 布局设置
    if (isFromMe) {
        // 发送的消息在右侧
        layout->addStretch();
        layout->addLayout(contentLayout);
        layout->addWidget(avatar);
    } else {
        // 接收的消息在左侧
        layout->addWidget(avatar);
        layout->addLayout(contentLayout);
        layout->addStretch();
    }
    
    // 创建列表项
    QListWidgetItem *item = new QListWidgetItem(ui->messageList);
    item->setSizeHint(messageWidget->sizeHint());
    ui->messageList->setItemWidget(item, messageWidget);
}

void MainWindow::addMessageToChat(const QString &senderName, const QString &content, 
                                const QString &time, bool isFromMe)
{
    createMessageWidget(senderName, content, time, isFromMe);
    
    // 滚动到底部
    ui->messageList->scrollToBottom();
}

void MainWindow::on_assignDormitoryButton_clicked()
{
    if (isAdminUser) {
        QMessageBox::information(this, "提示", "管理员无需分配宿舍");
        return;
    }
    
    // 检查是否已经分配了宿舍
    QMap<QString, QVariant> assignment = dormManager->getStudentDormitory(currentUserId);
    if (!assignment.isEmpty()) {
        QMessageBox::information(this, "提示", "您已经分配了宿舍，无需重复分配");
        return;
    }
    
    // 跳转到偏好设置页面
    ui->stackedWidget->setCurrentWidget(ui->preferencesPage);
    
    // 加载用户已有的偏好设置
    loadUserPreferences();
}

void MainWindow::on_submitPreferencesButton_clicked()
{
    // 保存用户偏好设置
    if (saveUserPreferences()) {
        QMessageBox::information(this, "成功", "偏好设置已保存！");
    } else {
        QMessageBox::warning(this, "失败", "保存偏好设置失败，请重试");
    }
}

void MainWindow::on_startAssignmentButton_clicked()
{
    // 先保存偏好设置
    if (!saveUserPreferences()) {
        QMessageBox::warning(this, "失败", "保存偏好设置失败，请重试");
        return;
    }
    
    // 执行宿舍分配
    if (performDormitoryAssignment()) {
        QMessageBox::information(this, "分配成功", "宿舍分配完成！");
        // 返回个人主页并更新显示
        ui->stackedWidget->setCurrentWidget(ui->homePage);
        updateAssignmentDisplay();
    } else {
        QMessageBox::warning(this, "分配失败", "宿舍分配失败，请稍后重试或联系管理员");
    }
}

void MainWindow::on_cancelPreferencesButton_clicked()
{
    // 返回个人主页
    ui->stackedWidget->setCurrentWidget(ui->homePage);
}

// 宿舍分配相关方法实现
void MainWindow::loadUserPreferences()
{
    StudentPreference pref = dormManager->getUserPreferences(currentUserId);
    
    // 设置床位偏好
    if (pref.preferUpper) {
        ui->preferUpperInput->setCurrentText("上铺");
    } else {
        ui->preferUpperInput->setCurrentText("下铺");
    }
    
    // 设置容量偏好
    switch (pref.preferCapacity) {
        case 4: ui->preferCapacityInput->setCurrentText("4人"); break;
        case 6: ui->preferCapacityInput->setCurrentText("6人"); break;
        case 8: ui->preferCapacityInput->setCurrentText("8人"); break;
        default: ui->preferCapacityInput->setCurrentText("4人"); break;
    }
    
    // 设置作息偏好
    if (pref.isEarlyBird) {
        ui->earlyBirdRadio->setChecked(true);
    } else if (pref.isNightOwl) {
        ui->nightOwlRadio->setChecked(true);
    } else {
        ui->normalRadio->setChecked(true);
    }
    
    // 设置专业偏好
    ui->acceptDifferentMajorInput->setChecked(pref.acceptDifferentMajor);
}

bool MainWindow::saveUserPreferences()
{
    StudentPreference pref;
    pref.userId = currentUserId;
    
    // 床位偏好
    pref.preferUpper = (ui->preferUpperInput->currentText() == "上铺");
    
    // 容量偏好
    QString capacityText = ui->preferCapacityInput->currentText();
    if (capacityText == "4人") pref.preferCapacity = 4;
    else if (capacityText == "6人") pref.preferCapacity = 6;
    else if (capacityText == "8人") pref.preferCapacity = 8;
    else pref.preferCapacity = 4;
    
    // 作息偏好
    if (ui->earlyBirdRadio->isChecked()) {
        pref.isEarlyBird = true;
        pref.isNightOwl = false;
        pref.scheduleType = "早睡早起";
    } else if (ui->nightOwlRadio->isChecked()) {
        pref.isEarlyBird = false;
        pref.isNightOwl = true;
        pref.scheduleType = "夜猫子";
    } else {
        pref.isEarlyBird = false;
        pref.isNightOwl = false;
        pref.scheduleType = "正常作息";
    }
    
    // 专业偏好
    pref.acceptDifferentMajor = ui->acceptDifferentMajorInput->isChecked();
    
    // 兴趣爱好（简化处理）
    QStringList hobbies;
    if (ui->readingCheck->isChecked()) hobbies << "阅读";
    if (ui->gamingCheck->isChecked()) hobbies << "游戏";
    if (ui->sportsCheck->isChecked()) hobbies << "运动";
    if (ui->musicCheck->isChecked()) hobbies << "音乐";
    if (ui->artCheck->isChecked()) hobbies << "艺术";
    if (ui->programmingCheck->isChecked()) hobbies << "编程";
    if (ui->photographyCheck->isChecked()) hobbies << "摄影";
    if (ui->cookingCheck->isChecked()) hobbies << "烹饪";
    if (ui->travelCheck->isChecked()) hobbies << "旅行";
    if (ui->otherCheck->isChecked()) hobbies << "其他";
    
    pref.hobbies = hobbies.join(",");
    
    return dormManager->saveUserPreferences(currentUserId, pref);
}

bool MainWindow::performDormitoryAssignment()
{
    // 使用智能分配算法
    AssignmentResult result = dormManager->findBestMatch(currentUserId);
    
    if (result.dormitoryId > 0) {
        return dormManager->executeAssignment(result);
    } else {
        // 如果智能分配失败，使用简单分配
        return dormManager->assignDormitory(currentUserId);
    }
}

void MainWindow::updateAssignmentDisplay()
{
    QMap<QString, QVariant> assignment = dormManager->getStudentDormitory(currentUserId);
    
    if (!assignment.isEmpty()) {
        QString dormName = assignment["dormitory_name"].toString();
        QString building = assignment["building"].toString();
        QString roomNumber = assignment["room_number"].toString();
        int bedNumber = assignment["bed_number"].toInt();
        bool isUpper = assignment["is_upper"].toBool();
        
        QString assignmentText = QString("宿舍：%1\n楼栋：%2\n房间号：%3\n床位：%4号%5")
                               .arg(dormName)
                               .arg(building)
                               .arg(roomNumber)
                               .arg(bedNumber)
                               .arg(isUpper ? "上铺" : "下铺");
        
        ui->assignmentInfoLabel->setText(assignmentText);
    } else {
        ui->assignmentInfoLabel->setText("暂未分配宿舍");
    }
}

StudentPreference MainWindow::getCurrentPreferences()
{
    StudentPreference pref;
    pref.userId = currentUserId;
    
    // 床位偏好
    pref.preferUpper = (ui->preferUpperInput->currentText() == "上铺");
    
    // 容量偏好
    QString capacityText = ui->preferCapacityInput->currentText();
    if (capacityText == "4人") pref.preferCapacity = 4;
    else if (capacityText == "6人") pref.preferCapacity = 6;
    else if (capacityText == "8人") pref.preferCapacity = 8;
    else pref.preferCapacity = 4;
    
    // 作息偏好
    if (ui->earlyBirdRadio->isChecked()) {
        pref.isEarlyBird = true;
        pref.isNightOwl = false;
        pref.scheduleType = "早睡早起";
    } else if (ui->nightOwlRadio->isChecked()) {
        pref.isEarlyBird = false;
        pref.isNightOwl = true;
        pref.scheduleType = "夜猫子";
    } else {
        pref.isEarlyBird = false;
        pref.isNightOwl = false;
        pref.scheduleType = "正常作息";
    }
    
    // 专业偏好
    pref.acceptDifferentMajor = ui->acceptDifferentMajorInput->isChecked();
    
    return pref;
}

// 菜单动作槽函数实现
void MainWindow::on_actionLogin_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->loginPage);
}

void MainWindow::on_actionLogout_triggered()
{
    on_logoutButton_clicked();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionAddDormitory_triggered()
{
    if (!isAdminUser) {
        QMessageBox::warning(this, "权限不足", "只有管理员可以添加宿舍");
        return;
    }
    ui->stackedWidget->setCurrentWidget(ui->dormitoryManagementPage);
    refreshDormitoryList();
}

void MainWindow::on_actionEditDormitory_triggered()
{
    if (!isAdminUser) {
        QMessageBox::warning(this, "权限不足", "只有管理员可以编辑宿舍");
        return;
    }
    ui->stackedWidget->setCurrentWidget(ui->dormitoryManagementPage);
    refreshDormitoryList();
}

void MainWindow::on_actionDeleteDormitory_triggered()
{
    if (!isAdminUser) {
        QMessageBox::warning(this, "权限不足", "只有管理员可以删除宿舍");
        return;
    }
    on_deleteDormitoryButton_clicked();
}

void MainWindow::on_actionViewDormitories_triggered()
{
    if (isAdminUser) {
        ui->stackedWidget->setCurrentWidget(ui->dormitoryManagementPage);
    } else {
        ui->stackedWidget->setCurrentWidget(ui->homePage);
    }
    refreshDormitoryList();
}

void MainWindow::on_actionSmartAssignment_triggered()
{
    if (isAdminUser) {
        QMessageBox::information(this, "提示", "管理员无需分配宿舍");
        return;
    }
    on_assignDormitoryButton_clicked();
}

void MainWindow::on_actionRegister_triggered()
{
    if (currentUserId != -1) {
        QMessageBox::information(this, "提示", "您已登录，无需注册");
        return;
    }
    on_registerButton_clicked();
}

void MainWindow::on_actionViewUsers_triggered()
{
    if (!isAdminUser) {
        QMessageBox::warning(this, "权限不足", "只有管理员可以查看用户列表");
        return;
    }
    
    QString userList = "用户列表：\n\n";
    QSqlQuery query("SELECT name, student_id, major, gender FROM users ORDER BY name");
    
    while (query.next()) {
        QString name = query.value(0).toString();
        QString studentId = query.value(1).toString();
        QString major = query.value(2).toString();
        QString gender = query.value(3).toString();
        
        userList += QString("姓名：%1\n学号：%2\n专业：%3\n性别：%4\n\n")
                   .arg(name, studentId, major, gender);
    }
    
    QMessageBox::information(this, "用户列表", userList);
}

void MainWindow::on_actionUserPreferences_triggered()
{
    if (isAdminUser) {
        QMessageBox::information(this, "提示", "管理员无需设置偏好");
        return;
    }
    
    if (currentUserId == -1) {
        QMessageBox::warning(this, "提示", "请先登录");
        return;
    }
    
    ui->stackedWidget->setCurrentWidget(ui->preferencesPage);
    loadUserPreferences();
}

void MainWindow::on_actionSendMessage_triggered()
{
    if (currentUserId == -1) {
        QMessageBox::warning(this, "提示", "请先登录");
        return;
    }
    
    on_viewMessagesButton_clicked();
}

void MainWindow::on_actionViewMessages_triggered()
{
    if (currentUserId == -1) {
        QMessageBox::warning(this, "提示", "请先登录");
        return;
    }
    
    on_viewMessagesButton_clicked();
}

void MainWindow::on_actionMessageSettings_triggered()
{
    QString settings = "消息设置：\n\n";
    settings += "• 消息检查间隔：3秒\n";
    settings += "• 自动滚动到最新消息：是\n";
    settings += "• 消息提醒：是\n";
    settings += "• 未读消息计数：是\n\n";
    settings += "如需修改设置，请联系系统管理员。";
    
    QMessageBox::information(this, "消息设置", settings);
}

void MainWindow::on_actionAbout_triggered()
{
    QString about = "宿舍分配系统 v1.0\n\n";
    about += "功能特性：\n";
    about += "• 智能宿舍分配\n";
    about += "• 用户偏好设置\n";
    about += "• 实时消息系统\n";
    about += "• 宿舍管理功能\n";
    about += "• 现代化界面设计\n\n";
    about += "技术支持：Qt C++\n";
    about += "数据库：SQLite\n\n";
    about += "© 2024 宿舍管理系统";
    
    QMessageBox::about(this, "关于系统", about);
}

void MainWindow::on_actionUserGuide_triggered()
{
    QString guide = "用户指南\n\n";
    guide += "学生用户：\n";
    guide += "1. 注册账号并登录\n";
    guide += "2. 设置个人偏好（床位、容量、作息等）\n";
    guide += "3. 点击\"智能分配\"进行宿舍分配\n";
    guide += "4. 在消息中心与管理员沟通\n\n";
    guide += "管理员用户：\n";
    guide += "1. 使用管理员账号登录\n";
    guide += "2. 管理宿舍信息（增删改查）\n";
    guide += "3. 查看用户列表和分配情况\n";
    guide += "4. 通过消息中心回复学生咨询\n\n";
    guide += "快捷键：\n";
    guide += "Ctrl+L：登录  Ctrl+Q：退出\n";
    guide += "Ctrl+M：消息  Ctrl+A：智能分配\n";
    guide += "F1：关于系统  F2：用户指南";
    
    QMessageBox::information(this, "用户指南", guide);
}

void MainWindow::on_actionSystemInfo_triggered()
{
    QString info = "系统信息\n\n";
    info += "操作系统：" + QSysInfo::prettyProductName() + "\n";
    info += "架构：" + QSysInfo::currentCpuArchitecture() + "\n";
    info += "Qt版本：" + QString(qVersion()) + "\n";
    info += "数据库：SQLite\n";
    info += QString("当前用户ID：%1\n").arg(currentUserId);
    info += QString("用户类型：%1\n").arg(isAdminUser ? "管理员" : "学生");
    info += QString("登录状态：%1\n\n").arg(currentUserId != -1 ? "已登录" : "未登录");
    info += QString("数据库状态：%1").arg(db.isOpen() ? "已连接" : "未连接");
    
    QMessageBox::information(this, "系统信息", info);
}

void MainWindow::setupMenuBar()
{
    // 系统菜单
    QMenu *systemMenu = ui->menuSystem;
    QAction *loginAction = new QAction("登录", this);
    loginAction->setShortcut(QKeySequence("Ctrl+L"));
    loginAction->setIcon(QIcon(":/icons/login.png"));
    connect(loginAction, &QAction::triggered, this, &MainWindow::on_actionLogin_triggered);
    systemMenu->addAction(loginAction);
    
    QAction *logoutAction = new QAction("登出", this);
    logoutAction->setShortcut(QKeySequence("Ctrl+Shift+L"));
    logoutAction->setIcon(QIcon(":/icons/logout.png"));
    connect(logoutAction, &QAction::triggered, this, &MainWindow::on_actionLogout_triggered);
    systemMenu->addAction(logoutAction);
    
    systemMenu->addSeparator();
    
    QAction *exitAction = new QAction("退出", this);
    exitAction->setShortcut(QKeySequence("Ctrl+Q"));
    exitAction->setIcon(QIcon(":/icons/exit.png"));
    connect(exitAction, &QAction::triggered, this, &MainWindow::on_actionExit_triggered);
    systemMenu->addAction(exitAction);
    
    // 宿舍管理菜单
    QMenu *dormMenu = ui->menuDormitory;
    QAction *addDormAction = new QAction("添加宿舍", this);
    addDormAction->setShortcut(QKeySequence("Ctrl+N"));
    addDormAction->setIcon(QIcon(":/icons/add.png"));
    connect(addDormAction, &QAction::triggered, this, &MainWindow::on_actionAddDormitory_triggered);
    dormMenu->addAction(addDormAction);
    
    QAction *editDormAction = new QAction("编辑宿舍", this);
    editDormAction->setShortcut(QKeySequence("Ctrl+E"));
    editDormAction->setIcon(QIcon(":/icons/edit.png"));
    connect(editDormAction, &QAction::triggered, this, &MainWindow::on_actionEditDormitory_triggered);
    dormMenu->addAction(editDormAction);
    
    QAction *deleteDormAction = new QAction("删除宿舍", this);
    deleteDormAction->setShortcut(QKeySequence("Delete"));
    deleteDormAction->setIcon(QIcon(":/icons/delete.png"));
    connect(deleteDormAction, &QAction::triggered, this, &MainWindow::on_actionDeleteDormitory_triggered);
    dormMenu->addAction(deleteDormAction);
    
    dormMenu->addSeparator();
    
    QAction *viewDormsAction = new QAction("查看宿舍列表", this);
    viewDormsAction->setShortcut(QKeySequence("Ctrl+D"));
    viewDormsAction->setIcon(QIcon(":/icons/list.png"));
    connect(viewDormsAction, &QAction::triggered, this, &MainWindow::on_actionViewDormitories_triggered);
    dormMenu->addAction(viewDormsAction);
    
    QAction *smartAssignAction = new QAction("智能分配", this);
    smartAssignAction->setShortcut(QKeySequence("Ctrl+A"));
    smartAssignAction->setIcon(QIcon(":/icons/assign.png"));
    connect(smartAssignAction, &QAction::triggered, this, &MainWindow::on_actionSmartAssignment_triggered);
    dormMenu->addAction(smartAssignAction);
    
    // 用户管理菜单
    QMenu *userMenu = ui->menuUser;
    QAction *registerAction = new QAction("用户注册", this);
    registerAction->setShortcut(QKeySequence("Ctrl+R"));
    registerAction->setIcon(QIcon(":/icons/register.png"));
    connect(registerAction, &QAction::triggered, this, &MainWindow::on_actionRegister_triggered);
    userMenu->addAction(registerAction);
    
    QAction *viewUsersAction = new QAction("查看用户", this);
    viewUsersAction->setShortcut(QKeySequence("Ctrl+U"));
    viewUsersAction->setIcon(QIcon(":/icons/users.png"));
    connect(viewUsersAction, &QAction::triggered, this, &MainWindow::on_actionViewUsers_triggered);
    userMenu->addAction(viewUsersAction);
    
    QAction *preferencesAction = new QAction("偏好设置", this);
    preferencesAction->setShortcut(QKeySequence("Ctrl+P"));
    preferencesAction->setIcon(QIcon(":/icons/preferences.png"));
    connect(preferencesAction, &QAction::triggered, this, &MainWindow::on_actionUserPreferences_triggered);
    userMenu->addAction(preferencesAction);
    
    // 消息菜单
    QMenu *messageMenu = ui->menuUser;
    messageMenu->addSeparator();
    
    QAction *sendMessageAction = new QAction("发送消息", this);
    sendMessageAction->setShortcut(QKeySequence("Ctrl+M"));
    sendMessageAction->setIcon(QIcon(":/icons/image/chat.png"));
    connect(sendMessageAction, &QAction::triggered, this, &MainWindow::on_actionSendMessage_triggered);
    messageMenu->addAction(sendMessageAction);
    
    QAction *viewMessagesAction = new QAction("查看消息", this);
    viewMessagesAction->setShortcut(QKeySequence("Ctrl+Shift+M"));
    viewMessagesAction->setIcon(QIcon(":/icons/image/chat.png"));
    connect(viewMessagesAction, &QAction::triggered, this, &MainWindow::on_actionViewMessages_triggered);
    messageMenu->addAction(viewMessagesAction);
    
    // 帮助菜单
    QMenu *helpMenu = ui->menuHelp;
    QAction *aboutAction = new QAction("关于系统", this);
    aboutAction->setShortcut(QKeySequence("F1"));
    aboutAction->setIcon(QIcon(":/icons/about.png"));
    connect(aboutAction, &QAction::triggered, this, &MainWindow::on_actionAbout_triggered);
    helpMenu->addAction(aboutAction);
    
    QAction *guideAction = new QAction("用户指南", this);
    guideAction->setShortcut(QKeySequence("F2"));
    guideAction->setIcon(QIcon(":/icons/guide.png"));
    connect(guideAction, &QAction::triggered, this, &MainWindow::on_actionUserGuide_triggered);
    helpMenu->addAction(guideAction);
    
    QAction *infoAction = new QAction("系统信息", this);
    infoAction->setShortcut(QKeySequence("F3"));
    infoAction->setIcon(QIcon(":/icons/info.png"));
    connect(infoAction, &QAction::triggered, this, &MainWindow::on_actionSystemInfo_triggered);
    helpMenu->addAction(infoAction);
    
    // 主题菜单
    helpMenu->addSeparator();
    
    QAction *blueThemeAction = new QAction("蓝色主题", this);
    connect(blueThemeAction, &QAction::triggered, this, &MainWindow::on_actionBlueTheme_triggered);
    helpMenu->addAction(blueThemeAction);
    
    QAction *greenThemeAction = new QAction("绿色主题", this);
    connect(greenThemeAction, &QAction::triggered, this, &MainWindow::on_actionGreenTheme_triggered);
    helpMenu->addAction(greenThemeAction);
    
    QAction *purpleThemeAction = new QAction("紫色主题", this);
    connect(purpleThemeAction, &QAction::triggered, this, &MainWindow::on_actionPurpleTheme_triggered);
    helpMenu->addAction(purpleThemeAction);
    
    QAction *orangeThemeAction = new QAction("橙色主题", this);
    connect(orangeThemeAction, &QAction::triggered, this, &MainWindow::on_actionOrangeTheme_triggered);
    helpMenu->addAction(orangeThemeAction);
    
    // 设置菜单栏的字体和样式
    QFont menuFont = ui->menubar->font();
    menuFont.setPointSize(12);
    menuFont.setWeight(QFont::Medium);
    ui->menubar->setFont(menuFont);
    
    // 设置菜单栏的高度
    ui->menubar->setFixedHeight(32);
}

// 动画和视觉效果方法实现
void MainWindow::setupPageTransitions()
{
    // 为所有页面添加淡入效果
    QList<QWidget*> pages = {
        ui->loginPage, ui->registerPage, ui->homePage, 
        ui->dormitoryManagementPage, ui->messagePage, ui->preferencesPage
    };
    
    for (QWidget *page : pages) {
        page->setGraphicsEffect(new QGraphicsOpacityEffect(page));
        page->graphicsEffect()->setProperty("opacity", 1.0);
    }
}

void MainWindow::centerWindow()
{
    // 获取屏幕几何信息
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    
    // 计算窗口居中位置
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    
    // 移动窗口到居中位置
    move(x, y);
}

void MainWindow::showStartupAnimation()
{
    // 创建启动动画效果
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(this);
    setGraphicsEffect(effect);
    
    // 创建动画
    QPropertyAnimation *animation = new QPropertyAnimation(effect, "opacity");
    animation->setDuration(800);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->setEasingCurve(QEasingCurve::OutCubic);
    
    // 启动动画
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    
    // 动画结束后移除效果
    connect(animation, &QPropertyAnimation::finished, [this]() {
        setGraphicsEffect(nullptr);
    });
}

void MainWindow::animatePageSwitch(QWidget *fromPage, QWidget *toPage)
{
    if (!fromPage || !toPage) return;
    
    // 创建淡出动画
    QGraphicsOpacityEffect *fadeOutEffect = new QGraphicsOpacityEffect(fromPage);
    fromPage->setGraphicsEffect(fadeOutEffect);
    
    QPropertyAnimation *fadeOutAnimation = new QPropertyAnimation(fadeOutEffect, "opacity");
    fadeOutAnimation->setDuration(300);
    fadeOutAnimation->setStartValue(1.0);
    fadeOutAnimation->setEndValue(0.0);
    fadeOutAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    
    // 创建淡入动画
    QGraphicsOpacityEffect *fadeInEffect = new QGraphicsOpacityEffect(toPage);
    toPage->setGraphicsEffect(fadeInEffect);
    
    QPropertyAnimation *fadeInAnimation = new QPropertyAnimation(fadeInEffect, "opacity");
    fadeInAnimation->setDuration(300);
    fadeInAnimation->setStartValue(0.0);
    fadeInAnimation->setEndValue(1.0);
    fadeInAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    
    // 连接动画序列
    connect(fadeOutAnimation, &QPropertyAnimation::finished, [=]() {
        ui->stackedWidget->setCurrentWidget(toPage);
        fadeInAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    });
    
    connect(fadeInAnimation, &QPropertyAnimation::finished, [=]() {
        fromPage->setGraphicsEffect(nullptr);
        toPage->setGraphicsEffect(nullptr);
    });
    
    // 启动动画
    fadeOutAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

// 主题切换槽函数实现
void MainWindow::on_actionBlueTheme_triggered()
{
    applyTheme("blue");
    QMessageBox::information(this, "主题切换", "已切换到蓝色主题");
}

void MainWindow::on_actionGreenTheme_triggered()
{
    applyTheme("green");
    QMessageBox::information(this, "主题切换", "已切换到绿色主题");
}

void MainWindow::on_actionPurpleTheme_triggered()
{
    applyTheme("purple");
    QMessageBox::information(this, "主题切换", "已切换到紫色主题");
}

void MainWindow::on_actionOrangeTheme_triggered()
{
    applyTheme("orange");
    QMessageBox::information(this, "主题切换", "已切换到橙色主题");
}

// 主题管理方法实现
void MainWindow::applyTheme(const QString &themeName)
{
    QString styleSheet;
    
    if (themeName == "blue") {
        styleSheet = R"(
QMainWindow {
    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
        stop:0 #667eea, stop:1 #764ba2);
}

QPushButton {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #3498db, stop:1 #2980b9);
}

QPushButton:hover {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #5dade2, stop:1 #3498db);
}
)";
    } else if (themeName == "green") {
        styleSheet = R"(
QMainWindow {
    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
        stop:0 #56ab2f, stop:1 #a8e6cf);
}

QPushButton {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #27ae60, stop:1 #229954);
}

QPushButton:hover {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #2ecc71, stop:1 #27ae60);
}
)";
    } else if (themeName == "purple") {
        styleSheet = R"(
QMainWindow {
    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
        stop:0 #8e2de2, stop:1 #4a00e0);
}

QPushButton {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #9b59b6, stop:1 #8e44ad);
}

QPushButton:hover {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #a569bd, stop:1 #9b59b6);
}
)";
    } else if (themeName == "orange") {
        styleSheet = R"(
QMainWindow {
    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
        stop:0 #f093fb, stop:1 #f5576c);
}

QPushButton {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #e67e22, stop:1 #d35400);
}

QPushButton:hover {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
        stop:0 #f39c12, stop:1 #e67e22);
}
)";
    }
    
    // 应用主题样式表
    qApp->setStyleSheet(styleSheet);
    
    // 保存主题偏好
    saveThemePreference(themeName);
}

QString MainWindow::getCurrentTheme() const
{
    return loadThemePreference();
}

void MainWindow::saveThemePreference(const QString &themeName)
{
    QSettings settings("DormManager", "Theme");
    settings.setValue("currentTheme", themeName);
}

QString MainWindow::loadThemePreference() const
{
    QSettings settings("DormManager", "Theme");
    return settings.value("currentTheme", "blue").toString();
}
