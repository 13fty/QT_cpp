#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>

bool initDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.db");
    
    if (!db.open()) {
        QMessageBox::critical(nullptr, "数据库错误", 
            QString("无法打开数据库: %1").arg(db.lastError().text()));
        return false;
    }
    
    return true;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    if (!initDatabase()) {
        return -1;
    }
    
    MainWindow w;
    w.show();
    
    return a.exec();
}



