#ifndef DATA_H
#define DATA_H
#include <QDateTime>
#include <QMessagebox>
#include <QSqlDatabase>
#include <iostream>
#include <vector>
#include "city.h"
#include "train.h"
class Data
{
public:
    static void init()
    {
        citylist.clear();
        trainlist.clear();
    }
    static void add_city(City city)
    {
        citylist.push_back(city);
    }
    static void search_city(QString name);
    static void add_train(Train train);
    static void search_train(QString name);
    static QDateTime current_time;
    static std::vector<City> citylist;
    static std::vector<Train> trainlist;
    static QString qtime;
    static QString nexttime;
    static QDateTime next_time;
    static QSqlDatabase db;
    static int pass_time;
    static bool createConnection()
    {
        db = QSqlDatabase::addDatabase("QMYSQL");
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

        return true;
    }
};

#endif // DATA_H
