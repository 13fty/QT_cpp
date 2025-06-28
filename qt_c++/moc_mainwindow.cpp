/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[40];
    char stringdata0[1138];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 22), // "on_loginButton_clicked"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 25), // "on_registerButton_clicked"
QT_MOC_LITERAL(4, 61, 31), // "on_submitRegisterButton_clicked"
QT_MOC_LITERAL(5, 93, 28), // "on_backToLoginButton_clicked"
QT_MOC_LITERAL(6, 122, 23), // "on_logoutButton_clicked"
QT_MOC_LITERAL(7, 146, 29), // "on_addDormitoryButton_clicked"
QT_MOC_LITERAL(8, 176, 30), // "on_editDormitoryButton_clicked"
QT_MOC_LITERAL(9, 207, 32), // "on_deleteDormitoryButton_clicked"
QT_MOC_LITERAL(10, 240, 28), // "on_sendMessageButton_clicked"
QT_MOC_LITERAL(11, 269, 29), // "on_viewMessagesButton_clicked"
QT_MOC_LITERAL(12, 299, 29), // "on_replyMessageButton_clicked"
QT_MOC_LITERAL(13, 329, 32), // "on_assignDormitoryButton_clicked"
QT_MOC_LITERAL(14, 362, 34), // "on_submitPreferencesButton_cl..."
QT_MOC_LITERAL(15, 397, 32), // "on_startAssignmentButton_clicked"
QT_MOC_LITERAL(16, 430, 34), // "on_cancelPreferencesButton_cl..."
QT_MOC_LITERAL(17, 465, 15), // "refreshMessages"
QT_MOC_LITERAL(18, 481, 16), // "checkNewMessages"
QT_MOC_LITERAL(19, 498, 24), // "on_actionLogin_triggered"
QT_MOC_LITERAL(20, 523, 25), // "on_actionLogout_triggered"
QT_MOC_LITERAL(21, 549, 23), // "on_actionExit_triggered"
QT_MOC_LITERAL(22, 573, 31), // "on_actionAddDormitory_triggered"
QT_MOC_LITERAL(23, 605, 32), // "on_actionEditDormitory_triggered"
QT_MOC_LITERAL(24, 638, 34), // "on_actionDeleteDormitory_trig..."
QT_MOC_LITERAL(25, 673, 34), // "on_actionViewDormitories_trig..."
QT_MOC_LITERAL(26, 708, 34), // "on_actionSmartAssignment_trig..."
QT_MOC_LITERAL(27, 743, 27), // "on_actionRegister_triggered"
QT_MOC_LITERAL(28, 771, 28), // "on_actionViewUsers_triggered"
QT_MOC_LITERAL(29, 800, 34), // "on_actionUserPreferences_trig..."
QT_MOC_LITERAL(30, 835, 30), // "on_actionSendMessage_triggered"
QT_MOC_LITERAL(31, 866, 31), // "on_actionViewMessages_triggered"
QT_MOC_LITERAL(32, 898, 34), // "on_actionMessageSettings_trig..."
QT_MOC_LITERAL(33, 933, 24), // "on_actionAbout_triggered"
QT_MOC_LITERAL(34, 958, 28), // "on_actionUserGuide_triggered"
QT_MOC_LITERAL(35, 987, 29), // "on_actionSystemInfo_triggered"
QT_MOC_LITERAL(36, 1017, 28), // "on_actionBlueTheme_triggered"
QT_MOC_LITERAL(37, 1046, 29), // "on_actionGreenTheme_triggered"
QT_MOC_LITERAL(38, 1076, 30), // "on_actionPurpleTheme_triggered"
QT_MOC_LITERAL(39, 1107, 30) // "on_actionOrangeTheme_triggered"

    },
    "MainWindow\0on_loginButton_clicked\0\0"
    "on_registerButton_clicked\0"
    "on_submitRegisterButton_clicked\0"
    "on_backToLoginButton_clicked\0"
    "on_logoutButton_clicked\0"
    "on_addDormitoryButton_clicked\0"
    "on_editDormitoryButton_clicked\0"
    "on_deleteDormitoryButton_clicked\0"
    "on_sendMessageButton_clicked\0"
    "on_viewMessagesButton_clicked\0"
    "on_replyMessageButton_clicked\0"
    "on_assignDormitoryButton_clicked\0"
    "on_submitPreferencesButton_clicked\0"
    "on_startAssignmentButton_clicked\0"
    "on_cancelPreferencesButton_clicked\0"
    "refreshMessages\0checkNewMessages\0"
    "on_actionLogin_triggered\0"
    "on_actionLogout_triggered\0"
    "on_actionExit_triggered\0"
    "on_actionAddDormitory_triggered\0"
    "on_actionEditDormitory_triggered\0"
    "on_actionDeleteDormitory_triggered\0"
    "on_actionViewDormitories_triggered\0"
    "on_actionSmartAssignment_triggered\0"
    "on_actionRegister_triggered\0"
    "on_actionViewUsers_triggered\0"
    "on_actionUserPreferences_triggered\0"
    "on_actionSendMessage_triggered\0"
    "on_actionViewMessages_triggered\0"
    "on_actionMessageSettings_triggered\0"
    "on_actionAbout_triggered\0"
    "on_actionUserGuide_triggered\0"
    "on_actionSystemInfo_triggered\0"
    "on_actionBlueTheme_triggered\0"
    "on_actionGreenTheme_triggered\0"
    "on_actionPurpleTheme_triggered\0"
    "on_actionOrangeTheme_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      38,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  204,    2, 0x08 /* Private */,
       3,    0,  205,    2, 0x08 /* Private */,
       4,    0,  206,    2, 0x08 /* Private */,
       5,    0,  207,    2, 0x08 /* Private */,
       6,    0,  208,    2, 0x08 /* Private */,
       7,    0,  209,    2, 0x08 /* Private */,
       8,    0,  210,    2, 0x08 /* Private */,
       9,    0,  211,    2, 0x08 /* Private */,
      10,    0,  212,    2, 0x08 /* Private */,
      11,    0,  213,    2, 0x08 /* Private */,
      12,    0,  214,    2, 0x08 /* Private */,
      13,    0,  215,    2, 0x08 /* Private */,
      14,    0,  216,    2, 0x08 /* Private */,
      15,    0,  217,    2, 0x08 /* Private */,
      16,    0,  218,    2, 0x08 /* Private */,
      17,    0,  219,    2, 0x08 /* Private */,
      18,    0,  220,    2, 0x08 /* Private */,
      19,    0,  221,    2, 0x08 /* Private */,
      20,    0,  222,    2, 0x08 /* Private */,
      21,    0,  223,    2, 0x08 /* Private */,
      22,    0,  224,    2, 0x08 /* Private */,
      23,    0,  225,    2, 0x08 /* Private */,
      24,    0,  226,    2, 0x08 /* Private */,
      25,    0,  227,    2, 0x08 /* Private */,
      26,    0,  228,    2, 0x08 /* Private */,
      27,    0,  229,    2, 0x08 /* Private */,
      28,    0,  230,    2, 0x08 /* Private */,
      29,    0,  231,    2, 0x08 /* Private */,
      30,    0,  232,    2, 0x08 /* Private */,
      31,    0,  233,    2, 0x08 /* Private */,
      32,    0,  234,    2, 0x08 /* Private */,
      33,    0,  235,    2, 0x08 /* Private */,
      34,    0,  236,    2, 0x08 /* Private */,
      35,    0,  237,    2, 0x08 /* Private */,
      36,    0,  238,    2, 0x08 /* Private */,
      37,    0,  239,    2, 0x08 /* Private */,
      38,    0,  240,    2, 0x08 /* Private */,
      39,    0,  241,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_loginButton_clicked(); break;
        case 1: _t->on_registerButton_clicked(); break;
        case 2: _t->on_submitRegisterButton_clicked(); break;
        case 3: _t->on_backToLoginButton_clicked(); break;
        case 4: _t->on_logoutButton_clicked(); break;
        case 5: _t->on_addDormitoryButton_clicked(); break;
        case 6: _t->on_editDormitoryButton_clicked(); break;
        case 7: _t->on_deleteDormitoryButton_clicked(); break;
        case 8: _t->on_sendMessageButton_clicked(); break;
        case 9: _t->on_viewMessagesButton_clicked(); break;
        case 10: _t->on_replyMessageButton_clicked(); break;
        case 11: _t->on_assignDormitoryButton_clicked(); break;
        case 12: _t->on_submitPreferencesButton_clicked(); break;
        case 13: _t->on_startAssignmentButton_clicked(); break;
        case 14: _t->on_cancelPreferencesButton_clicked(); break;
        case 15: _t->refreshMessages(); break;
        case 16: _t->checkNewMessages(); break;
        case 17: _t->on_actionLogin_triggered(); break;
        case 18: _t->on_actionLogout_triggered(); break;
        case 19: _t->on_actionExit_triggered(); break;
        case 20: _t->on_actionAddDormitory_triggered(); break;
        case 21: _t->on_actionEditDormitory_triggered(); break;
        case 22: _t->on_actionDeleteDormitory_triggered(); break;
        case 23: _t->on_actionViewDormitories_triggered(); break;
        case 24: _t->on_actionSmartAssignment_triggered(); break;
        case 25: _t->on_actionRegister_triggered(); break;
        case 26: _t->on_actionViewUsers_triggered(); break;
        case 27: _t->on_actionUserPreferences_triggered(); break;
        case 28: _t->on_actionSendMessage_triggered(); break;
        case 29: _t->on_actionViewMessages_triggered(); break;
        case 30: _t->on_actionMessageSettings_triggered(); break;
        case 31: _t->on_actionAbout_triggered(); break;
        case 32: _t->on_actionUserGuide_triggered(); break;
        case 33: _t->on_actionSystemInfo_triggered(); break;
        case 34: _t->on_actionBlueTheme_triggered(); break;
        case 35: _t->on_actionGreenTheme_triggered(); break;
        case 36: _t->on_actionPurpleTheme_triggered(); break;
        case 37: _t->on_actionOrangeTheme_triggered(); break;
        default: ;
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 38)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 38;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 38)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 38;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
