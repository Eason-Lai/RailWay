#ifndef CONNECTION_H
#define CONNECTION_H
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtDebug>
static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("RailwaySystem");
    db.setUserName("root");
    db.setPassword("");
    if (!db.open())
    {
        QMessageBox::critical(0,QObject::tr("无法打开数据库"),"无法创建数据库连接",QMessageBox::Cancel);
        return false;
    }
    //QSqlQuery query(db);
    //query.exec("create table city (id int primary key,name varchar(20),siteX int,siteY int)");
    //query.exec("insert into city values(2,'上海',897,488);");
    return true;
}
#endif // CONNECTION_H
