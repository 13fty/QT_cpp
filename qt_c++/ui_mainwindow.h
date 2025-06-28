/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *loginPage;
    QVBoxLayout *verticalLayout_2;
    QLabel *loginTitle;
    QLineEdit *studentIdInput;
    QLineEdit *passwordInput;
    QPushButton *loginButton;
    QPushButton *registerButton;
    QWidget *registerPage;
    QVBoxLayout *verticalLayout_3;
    QLabel *registerTitle;
    QLabel *regIdCardLabel;
    QLineEdit *regIdCardInput;
    QLabel *regNameLabel;
    QLineEdit *regNameInput;
    QLabel *regGenderLabel;
    QComboBox *regGenderInput;
    QLabel *regMajorLabel;
    QComboBox *regMajorInput;
    QLabel *regPasswordLabel;
    QLineEdit *regPasswordInput;
    QPushButton *submitRegisterButton;
    QPushButton *backToLoginButton;
    QWidget *homePage;
    QVBoxLayout *verticalLayout_home;
    QLabel *welcomeLabel;
    QPushButton *studentMessageCenterButton;
    QPushButton *assignDormitoryButton;
    QGroupBox *userInfoGroup;
    QGroupBox *dormitoryAssignmentGroup;
    QVBoxLayout *verticalLayout_assignment;
    QLabel *assignmentInfoLabel;
    QPushButton *studentLogoutButton;
    QWidget *preferencesPage;
    QVBoxLayout *verticalLayout_7;
    QLabel *preferencesTitle;
    QGroupBox *bedPreferenceGroup;
    QFormLayout *formLayout_3;
    QLabel *preferUpperLabel;
    QComboBox *preferUpperInput;
    QLabel *preferCapacityLabel;
    QComboBox *preferCapacityInput;
    QGroupBox *scheduleGroup;
    QVBoxLayout *verticalLayout_8;
    QRadioButton *earlyBirdRadio;
    QRadioButton *normalRadio;
    QRadioButton *nightOwlRadio;
    QGroupBox *hobbiesGroup;
    QGridLayout *gridLayout;
    QCheckBox *readingCheck;
    QCheckBox *gamingCheck;
    QCheckBox *sportsCheck;
    QCheckBox *musicCheck;
    QCheckBox *artCheck;
    QCheckBox *programmingCheck;
    QCheckBox *photographyCheck;
    QCheckBox *cookingCheck;
    QCheckBox *travelCheck;
    QCheckBox *otherCheck;
    QCheckBox *acceptDifferentMajorInput;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *submitPreferencesButton;
    QPushButton *startAssignmentButton;
    QPushButton *cancelPreferencesButton;
    QWidget *dormitoryManagementPage;
    QVBoxLayout *verticalLayout_5;
    QPushButton *messageCenterButton;
    QPushButton *logoutButton;
    QLabel *dormitoryManagementTitle;
    QGridLayout *gridLayout1;
    QLabel *dormitoryNameLabel;
    QLineEdit *dormitoryNameInput;
    QLabel *buildingLabel;
    QLineEdit *buildingInput;
    QLabel *roomNumberLabel;
    QLineEdit *roomNumberInput;
    QLabel *capacityLabel;
    QComboBox *capacityInput;
    QLabel *dormitoryGenderLabel;
    QComboBox *dormitoryGenderInput;
    QLabel *scheduleTypeLabel;
    QComboBox *scheduleTypeInput;
    QCheckBox *acceptDifferentMajorCheckBox;
    QHBoxLayout *horizontalLayout;
    QPushButton *addDormitoryButton;
    QPushButton *editDormitoryButton;
    QPushButton *deleteDormitoryButton;
    QTableWidget *dormitoryTable;
    QPushButton *backToHomeButton;
    QWidget *messagePage;
    QVBoxLayout *verticalLayout_message;
    QLabel *messagePageTitle;
    QHBoxLayout *messageLayout;
    QTableWidget *userTable;
    QVBoxLayout *messageContentLayout;
    QListWidget *messageList;
    QHBoxLayout *messageInputLayout;
    QLineEdit *messageInput;
    QPushButton *sendMessageButton;
    QHBoxLayout *messageButtonLayout;
    QPushButton *backToHomeButton1;
    QMenuBar *menubar;
    QMenu *menuSystem;
    QMenu *menuDormitory;
    QMenu *menuUser;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        loginPage = new QWidget();
        loginPage->setObjectName(QString::fromUtf8("loginPage"));
        verticalLayout_2 = new QVBoxLayout(loginPage);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        loginTitle = new QLabel(loginPage);
        loginTitle->setObjectName(QString::fromUtf8("loginTitle"));

        verticalLayout_2->addWidget(loginTitle);

        studentIdInput = new QLineEdit(loginPage);
        studentIdInput->setObjectName(QString::fromUtf8("studentIdInput"));

        verticalLayout_2->addWidget(studentIdInput);

        passwordInput = new QLineEdit(loginPage);
        passwordInput->setObjectName(QString::fromUtf8("passwordInput"));
        passwordInput->setEchoMode(QLineEdit::Password);

        verticalLayout_2->addWidget(passwordInput);

        loginButton = new QPushButton(loginPage);
        loginButton->setObjectName(QString::fromUtf8("loginButton"));

        verticalLayout_2->addWidget(loginButton);

        registerButton = new QPushButton(loginPage);
        registerButton->setObjectName(QString::fromUtf8("registerButton"));

        verticalLayout_2->addWidget(registerButton);

        stackedWidget->addWidget(loginPage);
        registerPage = new QWidget();
        registerPage->setObjectName(QString::fromUtf8("registerPage"));
        verticalLayout_3 = new QVBoxLayout(registerPage);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        registerTitle = new QLabel(registerPage);
        registerTitle->setObjectName(QString::fromUtf8("registerTitle"));

        verticalLayout_3->addWidget(registerTitle);

        regIdCardLabel = new QLabel(registerPage);
        regIdCardLabel->setObjectName(QString::fromUtf8("regIdCardLabel"));

        verticalLayout_3->addWidget(regIdCardLabel);

        regIdCardInput = new QLineEdit(registerPage);
        regIdCardInput->setObjectName(QString::fromUtf8("regIdCardInput"));

        verticalLayout_3->addWidget(regIdCardInput);

        regNameLabel = new QLabel(registerPage);
        regNameLabel->setObjectName(QString::fromUtf8("regNameLabel"));

        verticalLayout_3->addWidget(regNameLabel);

        regNameInput = new QLineEdit(registerPage);
        regNameInput->setObjectName(QString::fromUtf8("regNameInput"));

        verticalLayout_3->addWidget(regNameInput);

        regGenderLabel = new QLabel(registerPage);
        regGenderLabel->setObjectName(QString::fromUtf8("regGenderLabel"));

        verticalLayout_3->addWidget(regGenderLabel);

        regGenderInput = new QComboBox(registerPage);
        regGenderInput->addItem(QString());
        regGenderInput->addItem(QString());
        regGenderInput->setObjectName(QString::fromUtf8("regGenderInput"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(regGenderInput->sizePolicy().hasHeightForWidth());
        regGenderInput->setSizePolicy(sizePolicy);
        regGenderInput->setMinimumSize(QSize(0, 40));

        verticalLayout_3->addWidget(regGenderInput);

        regMajorLabel = new QLabel(registerPage);
        regMajorLabel->setObjectName(QString::fromUtf8("regMajorLabel"));

        verticalLayout_3->addWidget(regMajorLabel);

        regMajorInput = new QComboBox(registerPage);
        regMajorInput->addItem(QString());
        regMajorInput->addItem(QString());
        regMajorInput->addItem(QString());
        regMajorInput->addItem(QString());
        regMajorInput->addItem(QString());
        regMajorInput->addItem(QString());
        regMajorInput->addItem(QString());
        regMajorInput->addItem(QString());
        regMajorInput->addItem(QString());
        regMajorInput->addItem(QString());
        regMajorInput->addItem(QString());
        regMajorInput->addItem(QString());
        regMajorInput->addItem(QString());
        regMajorInput->addItem(QString());
        regMajorInput->addItem(QString());
        regMajorInput->addItem(QString());
        regMajorInput->addItem(QString());
        regMajorInput->addItem(QString());
        regMajorInput->addItem(QString());
        regMajorInput->addItem(QString());
        regMajorInput->addItem(QString());
        regMajorInput->addItem(QString());
        regMajorInput->addItem(QString());
        regMajorInput->addItem(QString());
        regMajorInput->addItem(QString());
        regMajorInput->addItem(QString());
        regMajorInput->addItem(QString());
        regMajorInput->addItem(QString());
        regMajorInput->addItem(QString());
        regMajorInput->addItem(QString());
        regMajorInput->addItem(QString());
        regMajorInput->setObjectName(QString::fromUtf8("regMajorInput"));
        sizePolicy.setHeightForWidth(regMajorInput->sizePolicy().hasHeightForWidth());
        regMajorInput->setSizePolicy(sizePolicy);
        regMajorInput->setMinimumSize(QSize(0, 40));

        verticalLayout_3->addWidget(regMajorInput);

        regPasswordLabel = new QLabel(registerPage);
        regPasswordLabel->setObjectName(QString::fromUtf8("regPasswordLabel"));

        verticalLayout_3->addWidget(regPasswordLabel);

        regPasswordInput = new QLineEdit(registerPage);
        regPasswordInput->setObjectName(QString::fromUtf8("regPasswordInput"));
        regPasswordInput->setEchoMode(QLineEdit::Password);

        verticalLayout_3->addWidget(regPasswordInput);

        submitRegisterButton = new QPushButton(registerPage);
        submitRegisterButton->setObjectName(QString::fromUtf8("submitRegisterButton"));

        verticalLayout_3->addWidget(submitRegisterButton);

        backToLoginButton = new QPushButton(registerPage);
        backToLoginButton->setObjectName(QString::fromUtf8("backToLoginButton"));

        verticalLayout_3->addWidget(backToLoginButton);

        stackedWidget->addWidget(registerPage);
        homePage = new QWidget();
        homePage->setObjectName(QString::fromUtf8("homePage"));
        verticalLayout_home = new QVBoxLayout(homePage);
        verticalLayout_home->setObjectName(QString::fromUtf8("verticalLayout_home"));
        welcomeLabel = new QLabel(homePage);
        welcomeLabel->setObjectName(QString::fromUtf8("welcomeLabel"));

        verticalLayout_home->addWidget(welcomeLabel);

        studentMessageCenterButton = new QPushButton(homePage);
        studentMessageCenterButton->setObjectName(QString::fromUtf8("studentMessageCenterButton"));

        verticalLayout_home->addWidget(studentMessageCenterButton);

        assignDormitoryButton = new QPushButton(homePage);
        assignDormitoryButton->setObjectName(QString::fromUtf8("assignDormitoryButton"));

        verticalLayout_home->addWidget(assignDormitoryButton);

        userInfoGroup = new QGroupBox(homePage);
        userInfoGroup->setObjectName(QString::fromUtf8("userInfoGroup"));

        verticalLayout_home->addWidget(userInfoGroup);

        dormitoryAssignmentGroup = new QGroupBox(homePage);
        dormitoryAssignmentGroup->setObjectName(QString::fromUtf8("dormitoryAssignmentGroup"));
        verticalLayout_assignment = new QVBoxLayout(dormitoryAssignmentGroup);
        verticalLayout_assignment->setObjectName(QString::fromUtf8("verticalLayout_assignment"));
        assignmentInfoLabel = new QLabel(dormitoryAssignmentGroup);
        assignmentInfoLabel->setObjectName(QString::fromUtf8("assignmentInfoLabel"));
        assignmentInfoLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_assignment->addWidget(assignmentInfoLabel);


        verticalLayout_home->addWidget(dormitoryAssignmentGroup);

        studentLogoutButton = new QPushButton(homePage);
        studentLogoutButton->setObjectName(QString::fromUtf8("studentLogoutButton"));

        verticalLayout_home->addWidget(studentLogoutButton);

        stackedWidget->addWidget(homePage);
        preferencesPage = new QWidget();
        preferencesPage->setObjectName(QString::fromUtf8("preferencesPage"));
        verticalLayout_7 = new QVBoxLayout(preferencesPage);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        preferencesTitle = new QLabel(preferencesPage);
        preferencesTitle->setObjectName(QString::fromUtf8("preferencesTitle"));

        verticalLayout_7->addWidget(preferencesTitle);

        bedPreferenceGroup = new QGroupBox(preferencesPage);
        bedPreferenceGroup->setObjectName(QString::fromUtf8("bedPreferenceGroup"));
        formLayout_3 = new QFormLayout(bedPreferenceGroup);
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        preferUpperLabel = new QLabel(bedPreferenceGroup);
        preferUpperLabel->setObjectName(QString::fromUtf8("preferUpperLabel"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, preferUpperLabel);

        preferUpperInput = new QComboBox(bedPreferenceGroup);
        preferUpperInput->addItem(QString());
        preferUpperInput->addItem(QString());
        preferUpperInput->setObjectName(QString::fromUtf8("preferUpperInput"));
        sizePolicy.setHeightForWidth(preferUpperInput->sizePolicy().hasHeightForWidth());
        preferUpperInput->setSizePolicy(sizePolicy);
        preferUpperInput->setMinimumSize(QSize(0, 40));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, preferUpperInput);

        preferCapacityLabel = new QLabel(bedPreferenceGroup);
        preferCapacityLabel->setObjectName(QString::fromUtf8("preferCapacityLabel"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, preferCapacityLabel);

        preferCapacityInput = new QComboBox(bedPreferenceGroup);
        preferCapacityInput->addItem(QString());
        preferCapacityInput->addItem(QString());
        preferCapacityInput->addItem(QString());
        preferCapacityInput->setObjectName(QString::fromUtf8("preferCapacityInput"));
        sizePolicy.setHeightForWidth(preferCapacityInput->sizePolicy().hasHeightForWidth());
        preferCapacityInput->setSizePolicy(sizePolicy);
        preferCapacityInput->setMinimumSize(QSize(0, 40));

        formLayout_3->setWidget(1, QFormLayout::FieldRole, preferCapacityInput);


        verticalLayout_7->addWidget(bedPreferenceGroup);

        scheduleGroup = new QGroupBox(preferencesPage);
        scheduleGroup->setObjectName(QString::fromUtf8("scheduleGroup"));
        verticalLayout_8 = new QVBoxLayout(scheduleGroup);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        earlyBirdRadio = new QRadioButton(scheduleGroup);
        earlyBirdRadio->setObjectName(QString::fromUtf8("earlyBirdRadio"));

        verticalLayout_8->addWidget(earlyBirdRadio);

        normalRadio = new QRadioButton(scheduleGroup);
        normalRadio->setObjectName(QString::fromUtf8("normalRadio"));
        normalRadio->setChecked(true);

        verticalLayout_8->addWidget(normalRadio);

        nightOwlRadio = new QRadioButton(scheduleGroup);
        nightOwlRadio->setObjectName(QString::fromUtf8("nightOwlRadio"));

        verticalLayout_8->addWidget(nightOwlRadio);


        verticalLayout_7->addWidget(scheduleGroup);

        hobbiesGroup = new QGroupBox(preferencesPage);
        hobbiesGroup->setObjectName(QString::fromUtf8("hobbiesGroup"));
        gridLayout = new QGridLayout(hobbiesGroup);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        readingCheck = new QCheckBox(hobbiesGroup);
        readingCheck->setObjectName(QString::fromUtf8("readingCheck"));

        gridLayout->addWidget(readingCheck, 0, 0, 1, 1);

        gamingCheck = new QCheckBox(hobbiesGroup);
        gamingCheck->setObjectName(QString::fromUtf8("gamingCheck"));

        gridLayout->addWidget(gamingCheck, 0, 1, 1, 1);

        sportsCheck = new QCheckBox(hobbiesGroup);
        sportsCheck->setObjectName(QString::fromUtf8("sportsCheck"));

        gridLayout->addWidget(sportsCheck, 0, 2, 1, 1);

        musicCheck = new QCheckBox(hobbiesGroup);
        musicCheck->setObjectName(QString::fromUtf8("musicCheck"));

        gridLayout->addWidget(musicCheck, 1, 0, 1, 1);

        artCheck = new QCheckBox(hobbiesGroup);
        artCheck->setObjectName(QString::fromUtf8("artCheck"));

        gridLayout->addWidget(artCheck, 1, 1, 1, 1);

        programmingCheck = new QCheckBox(hobbiesGroup);
        programmingCheck->setObjectName(QString::fromUtf8("programmingCheck"));

        gridLayout->addWidget(programmingCheck, 1, 2, 1, 1);

        photographyCheck = new QCheckBox(hobbiesGroup);
        photographyCheck->setObjectName(QString::fromUtf8("photographyCheck"));

        gridLayout->addWidget(photographyCheck, 2, 0, 1, 1);

        cookingCheck = new QCheckBox(hobbiesGroup);
        cookingCheck->setObjectName(QString::fromUtf8("cookingCheck"));

        gridLayout->addWidget(cookingCheck, 2, 1, 1, 1);

        travelCheck = new QCheckBox(hobbiesGroup);
        travelCheck->setObjectName(QString::fromUtf8("travelCheck"));

        gridLayout->addWidget(travelCheck, 2, 2, 1, 1);

        otherCheck = new QCheckBox(hobbiesGroup);
        otherCheck->setObjectName(QString::fromUtf8("otherCheck"));

        gridLayout->addWidget(otherCheck, 3, 0, 1, 1);


        verticalLayout_7->addWidget(hobbiesGroup);

        acceptDifferentMajorInput = new QCheckBox(preferencesPage);
        acceptDifferentMajorInput->setObjectName(QString::fromUtf8("acceptDifferentMajorInput"));

        verticalLayout_7->addWidget(acceptDifferentMajorInput);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        submitPreferencesButton = new QPushButton(preferencesPage);
        submitPreferencesButton->setObjectName(QString::fromUtf8("submitPreferencesButton"));

        horizontalLayout_2->addWidget(submitPreferencesButton);

        startAssignmentButton = new QPushButton(preferencesPage);
        startAssignmentButton->setObjectName(QString::fromUtf8("startAssignmentButton"));

        horizontalLayout_2->addWidget(startAssignmentButton);

        cancelPreferencesButton = new QPushButton(preferencesPage);
        cancelPreferencesButton->setObjectName(QString::fromUtf8("cancelPreferencesButton"));

        horizontalLayout_2->addWidget(cancelPreferencesButton);


        verticalLayout_7->addLayout(horizontalLayout_2);

        stackedWidget->addWidget(preferencesPage);
        dormitoryManagementPage = new QWidget();
        dormitoryManagementPage->setObjectName(QString::fromUtf8("dormitoryManagementPage"));
        verticalLayout_5 = new QVBoxLayout(dormitoryManagementPage);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        messageCenterButton = new QPushButton(dormitoryManagementPage);
        messageCenterButton->setObjectName(QString::fromUtf8("messageCenterButton"));

        verticalLayout_5->addWidget(messageCenterButton);

        logoutButton = new QPushButton(dormitoryManagementPage);
        logoutButton->setObjectName(QString::fromUtf8("logoutButton"));

        verticalLayout_5->addWidget(logoutButton);

        dormitoryManagementTitle = new QLabel(dormitoryManagementPage);
        dormitoryManagementTitle->setObjectName(QString::fromUtf8("dormitoryManagementTitle"));

        verticalLayout_5->addWidget(dormitoryManagementTitle);

        gridLayout1 = new QGridLayout();
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        dormitoryNameLabel = new QLabel(dormitoryManagementPage);
        dormitoryNameLabel->setObjectName(QString::fromUtf8("dormitoryNameLabel"));

        gridLayout1->addWidget(dormitoryNameLabel, 0, 0, 1, 1);

        dormitoryNameInput = new QLineEdit(dormitoryManagementPage);
        dormitoryNameInput->setObjectName(QString::fromUtf8("dormitoryNameInput"));

        gridLayout1->addWidget(dormitoryNameInput, 0, 1, 1, 1);

        buildingLabel = new QLabel(dormitoryManagementPage);
        buildingLabel->setObjectName(QString::fromUtf8("buildingLabel"));

        gridLayout1->addWidget(buildingLabel, 1, 0, 1, 1);

        buildingInput = new QLineEdit(dormitoryManagementPage);
        buildingInput->setObjectName(QString::fromUtf8("buildingInput"));

        gridLayout1->addWidget(buildingInput, 1, 1, 1, 1);

        roomNumberLabel = new QLabel(dormitoryManagementPage);
        roomNumberLabel->setObjectName(QString::fromUtf8("roomNumberLabel"));

        gridLayout1->addWidget(roomNumberLabel, 2, 0, 1, 1);

        roomNumberInput = new QLineEdit(dormitoryManagementPage);
        roomNumberInput->setObjectName(QString::fromUtf8("roomNumberInput"));

        gridLayout1->addWidget(roomNumberInput, 2, 1, 1, 1);

        capacityLabel = new QLabel(dormitoryManagementPage);
        capacityLabel->setObjectName(QString::fromUtf8("capacityLabel"));

        gridLayout1->addWidget(capacityLabel, 3, 0, 1, 1);

        capacityInput = new QComboBox(dormitoryManagementPage);
        capacityInput->addItem(QString());
        capacityInput->addItem(QString());
        capacityInput->addItem(QString());
        capacityInput->setObjectName(QString::fromUtf8("capacityInput"));
        sizePolicy.setHeightForWidth(capacityInput->sizePolicy().hasHeightForWidth());
        capacityInput->setSizePolicy(sizePolicy);
        capacityInput->setMinimumSize(QSize(0, 40));

        gridLayout1->addWidget(capacityInput, 3, 1, 1, 1);

        dormitoryGenderLabel = new QLabel(dormitoryManagementPage);
        dormitoryGenderLabel->setObjectName(QString::fromUtf8("dormitoryGenderLabel"));

        gridLayout1->addWidget(dormitoryGenderLabel, 4, 0, 1, 1);

        dormitoryGenderInput = new QComboBox(dormitoryManagementPage);
        dormitoryGenderInput->addItem(QString());
        dormitoryGenderInput->addItem(QString());
        dormitoryGenderInput->setObjectName(QString::fromUtf8("dormitoryGenderInput"));
        sizePolicy.setHeightForWidth(dormitoryGenderInput->sizePolicy().hasHeightForWidth());
        dormitoryGenderInput->setSizePolicy(sizePolicy);
        dormitoryGenderInput->setMinimumSize(QSize(0, 40));

        gridLayout1->addWidget(dormitoryGenderInput, 4, 1, 1, 1);

        scheduleTypeLabel = new QLabel(dormitoryManagementPage);
        scheduleTypeLabel->setObjectName(QString::fromUtf8("scheduleTypeLabel"));

        gridLayout1->addWidget(scheduleTypeLabel, 5, 0, 1, 1);

        scheduleTypeInput = new QComboBox(dormitoryManagementPage);
        scheduleTypeInput->addItem(QString());
        scheduleTypeInput->addItem(QString());
        scheduleTypeInput->setObjectName(QString::fromUtf8("scheduleTypeInput"));
        sizePolicy.setHeightForWidth(scheduleTypeInput->sizePolicy().hasHeightForWidth());
        scheduleTypeInput->setSizePolicy(sizePolicy);
        scheduleTypeInput->setMinimumSize(QSize(0, 40));

        gridLayout1->addWidget(scheduleTypeInput, 5, 1, 1, 1);

        acceptDifferentMajorCheckBox = new QCheckBox(dormitoryManagementPage);
        acceptDifferentMajorCheckBox->setObjectName(QString::fromUtf8("acceptDifferentMajorCheckBox"));

        gridLayout1->addWidget(acceptDifferentMajorCheckBox, 6, 0, 1, 2);


        verticalLayout_5->addLayout(gridLayout1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        addDormitoryButton = new QPushButton(dormitoryManagementPage);
        addDormitoryButton->setObjectName(QString::fromUtf8("addDormitoryButton"));

        horizontalLayout->addWidget(addDormitoryButton);

        editDormitoryButton = new QPushButton(dormitoryManagementPage);
        editDormitoryButton->setObjectName(QString::fromUtf8("editDormitoryButton"));

        horizontalLayout->addWidget(editDormitoryButton);

        deleteDormitoryButton = new QPushButton(dormitoryManagementPage);
        deleteDormitoryButton->setObjectName(QString::fromUtf8("deleteDormitoryButton"));

        horizontalLayout->addWidget(deleteDormitoryButton);


        verticalLayout_5->addLayout(horizontalLayout);

        dormitoryTable = new QTableWidget(dormitoryManagementPage);
        if (dormitoryTable->columnCount() < 9)
            dormitoryTable->setColumnCount(9);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        dormitoryTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        dormitoryTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        dormitoryTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        dormitoryTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        dormitoryTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        dormitoryTable->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        dormitoryTable->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        dormitoryTable->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        dormitoryTable->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        dormitoryTable->setObjectName(QString::fromUtf8("dormitoryTable"));

        verticalLayout_5->addWidget(dormitoryTable);

        backToHomeButton = new QPushButton(dormitoryManagementPage);
        backToHomeButton->setObjectName(QString::fromUtf8("backToHomeButton"));

        verticalLayout_5->addWidget(backToHomeButton);

        stackedWidget->addWidget(dormitoryManagementPage);
        messagePage = new QWidget();
        messagePage->setObjectName(QString::fromUtf8("messagePage"));
        verticalLayout_message = new QVBoxLayout(messagePage);
        verticalLayout_message->setObjectName(QString::fromUtf8("verticalLayout_message"));
        messagePageTitle = new QLabel(messagePage);
        messagePageTitle->setObjectName(QString::fromUtf8("messagePageTitle"));
        messagePageTitle->setAlignment(Qt::AlignCenter);

        verticalLayout_message->addWidget(messagePageTitle);

        messageLayout = new QHBoxLayout();
        messageLayout->setObjectName(QString::fromUtf8("messageLayout"));
        userTable = new QTableWidget(messagePage);
        userTable->setObjectName(QString::fromUtf8("userTable"));
        userTable->setMaximumWidth(200);
        userTable->setVisible(false);

        messageLayout->addWidget(userTable);

        messageContentLayout = new QVBoxLayout();
        messageContentLayout->setObjectName(QString::fromUtf8("messageContentLayout"));
        messageList = new QListWidget(messagePage);
        messageList->setObjectName(QString::fromUtf8("messageList"));
        messageList->setAlternatingRowColors(true);
        messageList->setSpacing(5);

        messageContentLayout->addWidget(messageList);

        messageInputLayout = new QHBoxLayout();
        messageInputLayout->setObjectName(QString::fromUtf8("messageInputLayout"));
        messageInput = new QLineEdit(messagePage);
        messageInput->setObjectName(QString::fromUtf8("messageInput"));

        messageInputLayout->addWidget(messageInput);

        sendMessageButton = new QPushButton(messagePage);
        sendMessageButton->setObjectName(QString::fromUtf8("sendMessageButton"));
        sendMessageButton->setMinimumWidth(60);

        messageInputLayout->addWidget(sendMessageButton);


        messageContentLayout->addLayout(messageInputLayout);


        messageLayout->addLayout(messageContentLayout);


        verticalLayout_message->addLayout(messageLayout);

        messageButtonLayout = new QHBoxLayout();
        messageButtonLayout->setObjectName(QString::fromUtf8("messageButtonLayout"));
        backToHomeButton1 = new QPushButton(messagePage);
        backToHomeButton1->setObjectName(QString::fromUtf8("backToHomeButton1"));

        messageButtonLayout->addWidget(backToHomeButton1);


        verticalLayout_message->addLayout(messageButtonLayout);

        stackedWidget->addWidget(messagePage);

        verticalLayout->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menuSystem = new QMenu(menubar);
        menuSystem->setObjectName(QString::fromUtf8("menuSystem"));
        menuDormitory = new QMenu(menubar);
        menuDormitory->setObjectName(QString::fromUtf8("menuDormitory"));
        menuUser = new QMenu(menubar);
        menuUser->setObjectName(QString::fromUtf8("menuUser"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\345\256\277\350\210\215\345\210\206\351\205\215\347\263\273\347\273\237", nullptr));
        loginTitle->setText(QCoreApplication::translate("MainWindow", "\345\256\277\350\210\215\345\210\206\351\205\215\347\263\273\347\273\237", nullptr));
        studentIdInput->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\345\255\246\345\217\267", nullptr));
        passwordInput->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201", nullptr));
        loginButton->setText(QCoreApplication::translate("MainWindow", "\347\231\273\345\275\225", nullptr));
        registerButton->setText(QCoreApplication::translate("MainWindow", "\346\263\250\345\206\214\346\226\260\347\224\250\346\210\267", nullptr));
        registerTitle->setText(QCoreApplication::translate("MainWindow", "\346\226\260\347\224\250\346\210\267\346\263\250\345\206\214", nullptr));
        regIdCardLabel->setText(QCoreApplication::translate("MainWindow", "\350\272\253\344\273\275\350\257\201\345\217\267\357\274\232", nullptr));
        regIdCardInput->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\24518\344\275\215\350\272\253\344\273\275\350\257\201\345\217\267", nullptr));
        regNameLabel->setText(QCoreApplication::translate("MainWindow", "\345\247\223\345\220\215\357\274\232", nullptr));
        regNameInput->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\345\247\223\345\220\215", nullptr));
        regGenderLabel->setText(QCoreApplication::translate("MainWindow", "\346\200\247\345\210\253\357\274\232", nullptr));
        regGenderInput->setItemText(0, QCoreApplication::translate("MainWindow", "\347\224\267", nullptr));
        regGenderInput->setItemText(1, QCoreApplication::translate("MainWindow", "\345\245\263", nullptr));

        regMajorLabel->setText(QCoreApplication::translate("MainWindow", "\344\270\223\344\270\232\357\274\232", nullptr));
        regMajorInput->setItemText(0, QCoreApplication::translate("MainWindow", "\350\256\241\347\256\227\346\234\272\347\247\221\345\255\246\344\270\216\346\212\200\346\234\257", nullptr));
        regMajorInput->setItemText(1, QCoreApplication::translate("MainWindow", "\350\275\257\344\273\266\345\267\245\347\250\213", nullptr));
        regMajorInput->setItemText(2, QCoreApplication::translate("MainWindow", "\344\272\272\345\267\245\346\231\272\350\203\275", nullptr));
        regMajorInput->setItemText(3, QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\347\247\221\345\255\246", nullptr));
        regMajorInput->setItemText(4, QCoreApplication::translate("MainWindow", "\347\224\265\345\255\220\344\277\241\346\201\257\345\267\245\347\250\213", nullptr));
        regMajorInput->setItemText(5, QCoreApplication::translate("MainWindow", "\351\200\232\344\277\241\345\267\245\347\250\213", nullptr));
        regMajorInput->setItemText(6, QCoreApplication::translate("MainWindow", "\350\207\252\345\212\250\345\214\226", nullptr));
        regMajorInput->setItemText(7, QCoreApplication::translate("MainWindow", "\346\234\272\346\242\260\345\267\245\347\250\213", nullptr));
        regMajorInput->setItemText(8, QCoreApplication::translate("MainWindow", "\347\224\265\346\260\224\345\267\245\347\250\213", nullptr));
        regMajorInput->setItemText(9, QCoreApplication::translate("MainWindow", "\345\234\237\346\234\250\345\267\245\347\250\213", nullptr));
        regMajorInput->setItemText(10, QCoreApplication::translate("MainWindow", "\345\214\226\345\255\246\345\267\245\347\250\213", nullptr));
        regMajorInput->setItemText(11, QCoreApplication::translate("MainWindow", "\347\224\237\347\211\251\345\267\245\347\250\213", nullptr));
        regMajorInput->setItemText(12, QCoreApplication::translate("MainWindow", "\347\216\257\345\242\203\345\267\245\347\250\213", nullptr));
        regMajorInput->setItemText(13, QCoreApplication::translate("MainWindow", "\346\235\220\346\226\231\347\247\221\345\255\246\344\270\216\345\267\245\347\250\213", nullptr));
        regMajorInput->setItemText(14, QCoreApplication::translate("MainWindow", "\345\267\245\344\270\232\345\267\245\347\250\213", nullptr));
        regMajorInput->setItemText(15, QCoreApplication::translate("MainWindow", "\347\273\217\346\265\216\345\255\246", nullptr));
        regMajorInput->setItemText(16, QCoreApplication::translate("MainWindow", "\351\207\221\350\236\215\345\255\246", nullptr));
        regMajorInput->setItemText(17, QCoreApplication::translate("MainWindow", "\345\267\245\345\225\206\347\256\241\347\220\206", nullptr));
        regMajorInput->setItemText(18, QCoreApplication::translate("MainWindow", "\345\270\202\345\234\272\350\220\245\351\224\200", nullptr));
        regMajorInput->setItemText(19, QCoreApplication::translate("MainWindow", "\344\274\232\350\256\241\345\255\246", nullptr));
        regMajorInput->setItemText(20, QCoreApplication::translate("MainWindow", "\346\263\225\345\255\246", nullptr));
        regMajorInput->setItemText(21, QCoreApplication::translate("MainWindow", "\346\226\260\351\227\273\344\274\240\346\222\255\345\255\246", nullptr));
        regMajorInput->setItemText(22, QCoreApplication::translate("MainWindow", "\345\277\203\347\220\206\345\255\246", nullptr));
        regMajorInput->setItemText(23, QCoreApplication::translate("MainWindow", "\346\225\231\350\202\262\345\255\246", nullptr));
        regMajorInput->setItemText(24, QCoreApplication::translate("MainWindow", "\345\214\273\345\255\246", nullptr));
        regMajorInput->setItemText(25, QCoreApplication::translate("MainWindow", "\350\215\257\345\255\246", nullptr));
        regMajorInput->setItemText(26, QCoreApplication::translate("MainWindow", "\346\212\244\347\220\206\345\255\246", nullptr));
        regMajorInput->setItemText(27, QCoreApplication::translate("MainWindow", "\350\211\272\346\234\257\350\256\276\350\256\241", nullptr));
        regMajorInput->setItemText(28, QCoreApplication::translate("MainWindow", "\351\237\263\344\271\220\345\255\246", nullptr));
        regMajorInput->setItemText(29, QCoreApplication::translate("MainWindow", "\344\275\223\350\202\262\345\255\246", nullptr));
        regMajorInput->setItemText(30, QCoreApplication::translate("MainWindow", "\345\205\266\344\273\226", nullptr));

        regPasswordLabel->setText(QCoreApplication::translate("MainWindow", "\345\257\206\347\240\201\357\274\232", nullptr));
        regPasswordInput->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201", nullptr));
        submitRegisterButton->setText(QCoreApplication::translate("MainWindow", "\346\217\220\344\272\244\346\263\250\345\206\214", nullptr));
        backToLoginButton->setText(QCoreApplication::translate("MainWindow", "\350\277\224\345\233\236\347\231\273\345\275\225", nullptr));
        studentMessageCenterButton->setText(QCoreApplication::translate("MainWindow", "\346\266\210\346\201\257\344\270\255\345\277\203", nullptr));
        assignDormitoryButton->setText(QCoreApplication::translate("MainWindow", "\345\210\206\351\205\215\345\256\277\350\210\215", nullptr));
        dormitoryAssignmentGroup->setTitle(QCoreApplication::translate("MainWindow", "\345\256\277\350\210\215\345\210\206\351\205\215\344\277\241\346\201\257", nullptr));
        assignmentInfoLabel->setText(QCoreApplication::translate("MainWindow", "\346\232\202\346\234\252\345\210\206\351\205\215\345\256\277\350\210\215", nullptr));
        studentLogoutButton->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272\347\231\273\345\275\225", nullptr));
        preferencesTitle->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256\345\256\277\350\210\215\345\201\217\345\245\275", nullptr));
        bedPreferenceGroup->setTitle(QCoreApplication::translate("MainWindow", "\345\272\212\344\275\215\345\201\217\345\245\275", nullptr));
        preferUpperLabel->setText(QCoreApplication::translate("MainWindow", "\345\272\212\344\275\215\344\275\215\347\275\256\357\274\232", nullptr));
        preferUpperInput->setItemText(0, QCoreApplication::translate("MainWindow", "\344\270\212\351\223\272", nullptr));
        preferUpperInput->setItemText(1, QCoreApplication::translate("MainWindow", "\344\270\213\351\223\272", nullptr));

        preferCapacityLabel->setText(QCoreApplication::translate("MainWindow", "\345\256\277\350\210\215\345\256\271\351\207\217\357\274\232", nullptr));
        preferCapacityInput->setItemText(0, QCoreApplication::translate("MainWindow", "4\344\272\272", nullptr));
        preferCapacityInput->setItemText(1, QCoreApplication::translate("MainWindow", "6\344\272\272", nullptr));
        preferCapacityInput->setItemText(2, QCoreApplication::translate("MainWindow", "8\344\272\272", nullptr));

        scheduleGroup->setTitle(QCoreApplication::translate("MainWindow", "\344\275\234\346\201\257\346\227\266\351\227\264", nullptr));
        earlyBirdRadio->setText(QCoreApplication::translate("MainWindow", "\346\227\251\347\235\241\346\227\251\350\265\267\345\236\213\357\274\21022:00\345\211\215\347\235\241\350\247\211\357\274\211", nullptr));
        normalRadio->setText(QCoreApplication::translate("MainWindow", "\346\255\243\345\270\270\344\275\234\346\201\257\345\236\213\357\274\21023:00\345\211\215\347\235\241\350\247\211\357\274\211", nullptr));
        nightOwlRadio->setText(QCoreApplication::translate("MainWindow", "\345\244\234\347\214\253\345\255\220\345\236\213\357\274\21023:00\345\220\216\347\235\241\350\247\211\357\274\211", nullptr));
        hobbiesGroup->setTitle(QCoreApplication::translate("MainWindow", "\345\205\264\350\266\243\347\210\261\345\245\275", nullptr));
        readingCheck->setText(QCoreApplication::translate("MainWindow", "\351\230\205\350\257\273", nullptr));
        gamingCheck->setText(QCoreApplication::translate("MainWindow", "\346\270\270\346\210\217", nullptr));
        sportsCheck->setText(QCoreApplication::translate("MainWindow", "\350\277\220\345\212\250", nullptr));
        musicCheck->setText(QCoreApplication::translate("MainWindow", "\351\237\263\344\271\220", nullptr));
        artCheck->setText(QCoreApplication::translate("MainWindow", "\350\211\272\346\234\257", nullptr));
        programmingCheck->setText(QCoreApplication::translate("MainWindow", "\347\274\226\347\250\213", nullptr));
        photographyCheck->setText(QCoreApplication::translate("MainWindow", "\346\221\204\345\275\261", nullptr));
        cookingCheck->setText(QCoreApplication::translate("MainWindow", "\347\203\271\351\245\252", nullptr));
        travelCheck->setText(QCoreApplication::translate("MainWindow", "\346\227\205\350\241\214", nullptr));
        otherCheck->setText(QCoreApplication::translate("MainWindow", "\345\205\266\344\273\226", nullptr));
        acceptDifferentMajorInput->setText(QCoreApplication::translate("MainWindow", "\346\216\245\345\217\227\344\270\216\344\270\215\345\220\214\344\270\223\344\270\232\347\232\204\345\255\246\347\224\237\345\220\214\344\275\217", nullptr));
        submitPreferencesButton->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230\345\201\217\345\245\275", nullptr));
        startAssignmentButton->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\345\210\206\351\205\215", nullptr));
        cancelPreferencesButton->setText(QCoreApplication::translate("MainWindow", "\345\217\226\346\266\210", nullptr));
        messageCenterButton->setText(QCoreApplication::translate("MainWindow", "\346\266\210\346\201\257\344\270\255\345\277\203", nullptr));
        logoutButton->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272\347\231\273\345\275\225", nullptr));
        dormitoryNameLabel->setText(QCoreApplication::translate("MainWindow", "\345\256\277\350\210\215\345\220\215\347\247\260\357\274\232", nullptr));
        dormitoryNameInput->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\345\256\277\350\210\215\345\220\215\347\247\260", nullptr));
        buildingLabel->setText(QCoreApplication::translate("MainWindow", "\346\245\274\346\240\213\357\274\232", nullptr));
        buildingInput->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\346\245\274\346\240\213\345\217\267", nullptr));
        roomNumberLabel->setText(QCoreApplication::translate("MainWindow", "\346\210\277\351\227\264\345\217\267\357\274\232", nullptr));
        roomNumberInput->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\346\210\277\351\227\264\345\217\267", nullptr));
        capacityLabel->setText(QCoreApplication::translate("MainWindow", "\345\256\271\351\207\217\357\274\232", nullptr));
        capacityInput->setItemText(0, QCoreApplication::translate("MainWindow", "4\344\272\272", nullptr));
        capacityInput->setItemText(1, QCoreApplication::translate("MainWindow", "6\344\272\272", nullptr));
        capacityInput->setItemText(2, QCoreApplication::translate("MainWindow", "8\344\272\272", nullptr));

        dormitoryGenderLabel->setText(QCoreApplication::translate("MainWindow", "\346\200\247\345\210\253\357\274\232", nullptr));
        dormitoryGenderInput->setItemText(0, QCoreApplication::translate("MainWindow", "\347\224\267", nullptr));
        dormitoryGenderInput->setItemText(1, QCoreApplication::translate("MainWindow", "\345\245\263", nullptr));

        scheduleTypeLabel->setText(QCoreApplication::translate("MainWindow", "\344\275\234\346\201\257\347\261\273\345\236\213\357\274\232", nullptr));
        scheduleTypeInput->setItemText(0, QCoreApplication::translate("MainWindow", "\346\227\251", nullptr));
        scheduleTypeInput->setItemText(1, QCoreApplication::translate("MainWindow", "\346\231\232", nullptr));

        acceptDifferentMajorCheckBox->setText(QCoreApplication::translate("MainWindow", "\346\216\245\345\217\227\344\270\215\345\220\214\344\270\223\344\270\232", nullptr));
        addDormitoryButton->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\345\256\277\350\210\215", nullptr));
        editDormitoryButton->setText(QCoreApplication::translate("MainWindow", "\347\274\226\350\276\221\345\256\277\350\210\215", nullptr));
        deleteDormitoryButton->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\345\256\277\350\210\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem = dormitoryTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = dormitoryTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "\345\256\277\350\210\215\345\220\215\347\247\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = dormitoryTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "\346\245\274\346\240\213", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = dormitoryTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "\346\210\277\351\227\264\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = dormitoryTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "\345\256\271\351\207\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = dormitoryTable->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "\346\200\247\345\210\253", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = dormitoryTable->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "\345\275\223\345\211\215\344\272\272\346\225\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = dormitoryTable->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "\344\275\234\346\201\257\347\261\273\345\236\213", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = dormitoryTable->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "\346\216\245\345\217\227\344\270\215\345\220\214\344\270\223\344\270\232", nullptr));
        backToHomeButton->setText(QCoreApplication::translate("MainWindow", "\350\277\224\345\233\236\344\270\273\351\241\265", nullptr));
        messagePageTitle->setText(QCoreApplication::translate("MainWindow", "\346\266\210\346\201\257\344\270\255\345\277\203", nullptr));
        messageInput->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\276\223\345\205\245\346\266\210\346\201\257...", nullptr));
        sendMessageButton->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        backToHomeButton1->setText(QCoreApplication::translate("MainWindow", "\350\277\224\345\233\236", nullptr));
        menuSystem->setTitle(QCoreApplication::translate("MainWindow", "\347\263\273\347\273\237", nullptr));
        menuDormitory->setTitle(QCoreApplication::translate("MainWindow", "\345\256\277\350\210\215\347\256\241\347\220\206", nullptr));
        menuUser->setTitle(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267\347\256\241\347\220\206", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "\345\270\256\345\212\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
