#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QCryptographicHash>
#include <QTimer>
#include <QDateTime>
#include "dormitory_manager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loginButton_clicked();
    void on_registerButton_clicked();
    void on_submitRegisterButton_clicked();
    void on_backToLoginButton_clicked();
    void on_logoutButton_clicked();
    void on_addDormitoryButton_clicked();
    void on_editDormitoryButton_clicked();
    void on_deleteDormitoryButton_clicked();
    void on_sendMessageButton_clicked();
    void on_viewMessagesButton_clicked();
    void on_replyMessageButton_clicked();
    void on_assignDormitoryButton_clicked();
    void on_submitPreferencesButton_clicked();
    void on_startAssignmentButton_clicked();
    void on_cancelPreferencesButton_clicked();
    void refreshMessages();
    void checkNewMessages();
    
    // 菜单动作槽函数
    void on_actionLogin_triggered();
    void on_actionLogout_triggered();
    void on_actionExit_triggered();
    void on_actionAddDormitory_triggered();
    void on_actionEditDormitory_triggered();
    void on_actionDeleteDormitory_triggered();
    void on_actionViewDormitories_triggered();
    void on_actionSmartAssignment_triggered();
    void on_actionRegister_triggered();
    void on_actionViewUsers_triggered();
    void on_actionUserPreferences_triggered();
    void on_actionSendMessage_triggered();
    void on_actionViewMessages_triggered();
    void on_actionMessageSettings_triggered();
    void on_actionAbout_triggered();
    void on_actionUserGuide_triggered();
    void on_actionSystemInfo_triggered();
    
    // 主题切换槽函数
    void on_actionBlueTheme_triggered();
    void on_actionGreenTheme_triggered();
    void on_actionPurpleTheme_triggered();
    void on_actionOrangeTheme_triggered();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    int currentUserId = -1;
    bool isAdminUser = false;
    DormitoryManager *dormManager;
    QTimer *messageCheckTimer;
    QDateTime lastMessageCheck;
    int unreadMessageCount;

    bool initDatabase();
    bool isAdmin(const QString &studentId, const QString &password);
    QString hashPassword(const QString &password);
    void refreshDormitoryList();
    QString generateStudentId();
    void setupMessageUI();
    void sendMessage(int receiverId, const QString &content);
    void markMessageAsRead(int messageId);
    bool hasUnreadMessages();
    void updateMessageNotification();
    QString getUserName(int userId);
    int getSelectedUserId();
    void loadStudentListForAdmin();
    
    // 微信风格聊天界面相关方法
    void createMessageWidget(const QString &senderName, const QString &content, 
                           const QString &time, bool isFromMe);
    void addMessageToChat(const QString &senderName, const QString &content, 
                         const QString &time, bool isFromMe);
    
    // 宿舍分配相关方法
    void loadUserPreferences();
    bool saveUserPreferences();
    bool performDormitoryAssignment();
    void updateAssignmentDisplay();
    StudentPreference getCurrentPreferences();
    
    // 菜单栏设置
    void setupMenuBar();
    
    // 动画和视觉效果
    void setupPageTransitions();
    void centerWindow();
    void showStartupAnimation();
    void animatePageSwitch(QWidget *fromPage, QWidget *toPage);
    
    // 主题管理
    void applyTheme(const QString &themeName);
    QString getCurrentTheme() const;
    void saveThemePreference(const QString &themeName);
    QString loadThemePreference() const;
};

#endif // MAINWINDOW_H
