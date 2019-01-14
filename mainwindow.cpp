#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
using namespace std;

std::vector<City> Data::citylist;
std::vector<Train> Data::trainlist;
QString Data::qtime;
int Data::pass_time;
QDateTime Data::current_time;
QDateTime Data::next_time;
QString Data::nexttime;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->resize(1220,750);

    bg = new Background(this);
    this->setCentralWidget(bg);

    ui->action->setShortcut(QKeySequence::Print);
    ui->action_2->setShortcut(QKeySequence::AddTab);
    ui->action_3->setShortcut(QKeySequence::Back);

    if (createConnection())
    {
        City city;
        QSqlQuery query("select * from city");
        //query.exec("select name from city");
        Data data;
        data.init();
        while (query.next())
        {
            int id = query.value(0).toInt();
            QString name = query.value(1).toString();
            int x = query.value(2).toInt();
            int y = query.value(3).toInt();
            QRadioButton *qb = new QRadioButton(bg);
            qb->setGeometry(x,y,20,20);
            qb->setChecked(false);
            qb->setCheckable(false);
            qb->setText("");
            qb->show();
            city.setdata(id,name,x,y);
            data.add_city(city);
        }
        query.exec("select time from data");
        query.next();
        Data::qtime = query.value(0).toString();
        Data::current_time = QDateTime::fromString(Data::qtime,"yyyy-MM-dd hh:mm:ss");
    }

    MouseX = new QLabel(ui->statusBar);
    MouseX->setFixedHeight(20);
    MouseX->setIndent(3);

    MouseY = new QLabel(ui->statusBar);
    MouseY->setFixedHeight(20);
    MouseY->setIndent(3);

    qltime = new QLabel(ui->statusBar);
    qltime->setText(Data::qtime);
    qltime->setFixedHeight(20);
    qltime->setIndent(3);

    ui->statusBar->addWidget(MouseX);
    ui->statusBar->addWidget(MouseY);
    ui->statusBar->addWidget(qltime);


    setMouseTracking(true);

    //bg->repaint();

    pt = new PassTime();
    connect(pt,SIGNAL(sendData(int)),this,SLOT(getData(int)));
}

 bool MainWindow::createConnection()
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
    QSqlQuery query(db);

    return true;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    MouseX->setNum(event->x());
    MouseY->setNum(event->y());
}

void MainWindow::getData(int n)
{
    Data::pass_time = n;
    QString str;
    QDateTime dt ;
    if ( n >=  24 )
    {
        Data::next_time = Data::current_time.addDays(int(n/24));
    }
    n = n % 24;
    Data::next_time = Data::current_time.addSecs(n*3600);
    Data::nexttime = Data::next_time.toString("yyyy-MM-dd hh:mm:ss");
    qltime->setText(Data::nexttime);
    QSqlQuery query;
    //query.exec(QString("update data set time ='%1'").arg(Data::nexttime));

    bg->repaint();
}

MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}

void MainWindow::on_action_triggered()
{
   Timetable_Widget *tw = new Timetable_Widget();
   tw->show();
}

void MainWindow::on_action_2_triggered()
{
    add *addwidget = new add();
    addwidget->show();
}

void MainWindow::on_action_3_triggered()
{
    pt->show();
}
