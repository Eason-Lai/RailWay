#include "background.h"

#include <QSequentialAnimationGroup>
#include <qdatetime.h>

#include <QParallelAnimationGroup>
#include <QPauseAnimation>
#include <iostream>
using namespace std;

Background::Background(QWidget *parent) : QWidget(parent)
{

}

void Background::paintEvent(QPaintEvent *event)
{
    QImage bg;
    bg.load(":/new/image/background.png");
    QPainter painter(this);
    painter.fillRect(0,0,this->width(),this->height(),QColor(255,255,255));
    painter.drawImage(this->rect(),bg);

//    painter.setPen(QPen(Qt::blue,4));
//    int startx,starty,endx,endy;
//    startx = 714;
//    starty = 669;
//    endx = 891;
//    endy = 482;
//    painter.drawLine(startx,starty,endx,endy);

}

void Background::update()
{
    QLabel l1;
}

void Background::repaint()
{
    QPixmap pix;
    QMatrix matrix;
    pix.load(":/new/image/huoche.png");//图片的位置
    //QSequentialAnimationGroup *pPosGroup = new QSequentialAnimationGroup(this);
    QParallelAnimationGroup *pPosGroup2 = new QParallelAnimationGroup(this);
    int c1,c2,cost;
    int startx,starty,endx,endy;
    QDateTime qdt1,qdt2;
    uint timen,timex,timed;
    QString qstime;
    qdt1 = Data::current_time;
    //cout<<"timen="<<timen<<endl;
    //数据库查询
    QSqlQuery query(QString("select * from train where time1 <= '%1' and state = '等待' order by time1 asc").arg(Data::nexttime));
    while(query.next())
    {
        //导出数据库数据
        c1 = query.value(6).toInt();
        c2 = query.value(7).toInt();
        qstime = query.value(3).toString();
        cost = query.value(5).toInt();
        qdt2= QDateTime::fromString(qstime,"yyyy-MM-dd hh:mm:ss");
        //cout<<"timex="<<timex<<endl;
        timed = qdt1.secsTo(qdt2)/7.2;
        cout<<"timed="<<timed<<endl;
        timen = timex;

        //得到两点坐标
        startx = Data::citylist[c1].x;
        starty = Data::citylist[c1].y;
        endx = Data::citylist[c2].x;
        endy = Data::citylist[c2].y;

        //计算图片旋转角度

        double ang = angele(startx,starty,endx,endy);
        cout<<"ang="<<ang<<endl;
        matrix.rotate(ang);

        QLabel *l1 = new QLabel(this);
        l1->setGeometry(startx,starty,20,20);

        pix.scaled(l1->size(), Qt::KeepAspectRatio);
        l1->setScaledContents(true);
        l1->setPixmap(pix.transformed(matrix, Qt::SmoothTransformation));
        matrix.reset();

        QSequentialAnimationGroup *pPosGroup = new QSequentialAnimationGroup(this);
        QPropertyAnimation *pPosAnimation1 = new QPropertyAnimation(l1, "pos");
        pPosAnimation1->setDuration(cost);
        pPosAnimation1->setStartValue(QPoint(startx, starty));
        pPosAnimation1->setEndValue(QPoint(endx, endy));
        pPosAnimation1->setEasingCurve(QEasingCurve::InOutQuad);

        QPauseAnimation *pp = new QPauseAnimation(this);
        pp->setDuration(timed*5);
        pPosGroup->addAnimation(pp);
        pPosGroup->addAnimation(pPosAnimation1);
        pPosGroup2->addAnimation(pPosGroup);

        connect(pPosAnimation1, &QPropertyAnimation::stateChanged, [=] {
            //要处理的函数
            if ( pPosAnimation1->state() ==  QPropertyAnimation::Running) {
            l1->show();
            cout<<"delete123213"<<endl;
            QSqlQuery query("update train set state = '行驶中' where state = '等待' order by time1 asc limit 1;");}
       });

        connect(pPosAnimation1, &QPropertyAnimation::finished, [=] {
            //要处理的函数
            cout<<"delete"<<endl;
            QSqlQuery query("update train set state = '已到站' where state = '行驶中' order by time1 asc limit 1;");
            //delete pPosAnimation1;
            delete l1;
       });
    }

    pPosGroup2->start();

    Data::current_time = Data::next_time;
    Data::qtime = Data::nexttime;

    /*int startx,starty,endx,endy;
    startx = 719;
    starty = 674;
    endx = 891;
    endy = 482;

    pPosGroup->addPause(500);
    //pPosGroup->addAnimation(pPosAnimation1);

    int d;
    d = sqrt(((startx-endx)*(startx-endx) + (starty-endy)*(starty-endy)))*20;
    double ang = angele(startx,starty,endx,endy);

    QMatrix matrix;
    matrix.rotate(ang);

    QPainter painter(this);
    painter.fillRect(0,0,this->width(),this->height(),QColor(255,255,255));
    QLabel *l1 = new QLabel(this);
    l1->setGeometry(714,669,20,20);
    QPixmap pix;
    pix.load(":/new/image/huoche.png");//图片的位置

    pix.scaled(l1->size(), Qt::KeepAspectRatio);
    l1->setScaledContents(true);
    l1->setPixmap(pix.transformed(matrix, Qt::SmoothTransformation));
    l1->show();

    QPropertyAnimation *pPosAnimation1 = new QPropertyAnimation(l1, "pos");
    pPosAnimation1->setDuration(d);
    pPosAnimation1->setStartValue(QPoint(startx, starty));
    pPosAnimation1->setEndValue(QPoint(endx, endy));
    pPosAnimation1->setEasingCurve(QEasingCurve::InOutQuad);
    pPosAnimation1->start();

    connect(pPosAnimation1, &QPropertyAnimation::finished, [=] {
               //要处理的函数
        delete l1;
   })*/;
}

double Background::angele(int x1,int y1,int x2,int y2)
{
    bool flagx,flagy;
    int dx,dy;
    double t,a;
    dx = x2 - x1;
    dy = y1 - y2;

    if ( dx > 0 ) flagx = true;
    else if ( dx < 0 )
    {
        flagx = false;
        dx = -dx;
    }
    else return 0;

    if ( dy > 0 ) flagy = true;
    else if ( dy < 0 )
    {
        flagy = false;
        dy = -dy;
    }
    else return 90;

    t = (dx*1.0)/(dy*1.0);
    a = atan(t)*180/3.14156;
    if ( !flagy ) a = 180 - a;
    if ( !flagx ) a = -a;
    return a;
}

void play()
{
    QDateTime date;

}
