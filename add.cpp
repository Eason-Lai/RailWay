#include "add.h"
#include "ui_add.h"

add::add(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::add)
{
    ui->setupUi(this);
    QStringList qsl;
    int i,n;
    n = Data::citylist.size();
    for (i=0;i<n;i++)
    {
        qsl.append(Data::citylist[i].name);
    }
    ui->comboBox1->addItems(qsl);
    ui->comboBox2->addItems(qsl);

    ui->dateTimeEdit->setDateTime(Data::current_time);
    ui->dateTimeEdit->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
    //ui->dateTimeEdit
}

add::~add()
{
    delete ui;
}

void add::on_pushButton_clicked()
{
    int c1,c2,cost;
    QString cn1,cn2,t1,t2;
    QDateTime dt;
    int startx,starty,endx,endy;

    c1 = ui->comboBox1->currentIndex();
    c2 = ui->comboBox2->currentIndex();
    cn1 = ui->comboBox1->currentText();
    cn2 = ui->comboBox2->currentText();

    startx = Data::citylist[c1].x;
    starty = Data::citylist[c1].y;
    endx = Data::citylist[c2].x;
    endy = Data::citylist[c2].y;
    t1 = ui->dateTimeEdit->text();
    cost = sqrt(((startx-endx)*(startx-endx) + (starty-endy)*(starty-endy)))*20;
    dt = QDateTime::fromString(t1,"yyyy-MM-dd hh:mm:ss");
    dt = dt.addSecs(cost*7.2);
    t2 = dt.toString("yyyy-MM-dd hh:mm:ss");

    QSqlQuery query;
    query.exec(QString("insert into train(city1,city2,time1,time2,cost,cityid1,cityid2,state) values('%1','%2','%3','%4',%5,%6,%7,'等待');")
               .arg(cn1,cn2,t1,t2,QString::number(cost),QString::number(c1),QString::number(c2)));
    close();
}

void add::on_pushButton_2_clicked()
{
    close();
}


void add::on_pushButton_3_clicked()
{
    QString cn1,cn2;
    cn1 = ui->comboBox1->currentText();
    cn2 = ui->comboBox2->currentText();
    QSqlQuery query;
    query.exec(QString("select MAX(time1) from train where city1 = '%1'").arg(cn1));
    query.next();
    if ( query.value(0).toString().isEmpty() )
    {
        ui->dateTimeEdit->setDateTime(Data::current_time);
        return;
    }
    QString str = query.value(0).toString();
    QDateTime qdt = QDateTime::fromString(str,"yyyy-MM-dd hh:mm:ss");
    qdt = qdt.addSecs(30*60);
    ui->dateTimeEdit->setDateTime(qdt);
}
