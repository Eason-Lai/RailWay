#include "passtime.h"
#include "ui_passtime.h"

PassTime::PassTime(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PassTime)
{
    ui->setupUi(this);
}

PassTime::~PassTime()
{
    delete ui;
}

void PassTime::on_pushButton_clicked()
{
    int n;
    n = ui->lineEdit->text().toInt();
    emit sendData(n);
    close();
}

void PassTime::on_pushButton_2_clicked()
{
    close();
}
