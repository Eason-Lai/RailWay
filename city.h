#ifndef CITY_H
#define CITY_H
#include <QString>
#include <vector>
#include <iostream>

const int Maxtrain = 10;
class  City
{  
public:
    City();
    //City(int d, QString n, int xl, int yl);
    void setdata(int d, QString n, int xl, int yl);
    //城市id
    int id;
    //城市名称
    QString name;
    //地图坐标
    int x;
    int y;
    //在站火车数
    int tnum;
    //在站火车id
    int  tl[Maxtrain] = {0};
};

#endif // CITY_H
