#include "timetable_widget.h"
#include "ui_timetable_widget.h"

#include <QSqlTableModel>

Timetable_Widget::Timetable_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Timetable_Widget)
{
    ui->setupUi(this);
    QSqlTableModel *model = new QSqlTableModel(this);
    QString tableName("train");
    model->setTable(tableName);
    model->select();
    model->removeColumns(5,3);
//    model->removeColumn(5);
//    model->removeColumn(6);
//    model->removeColumn(7);
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->setHeaderData(0,Qt::Horizontal,"列车编号");
    model->setHeaderData(1,Qt::Horizontal,"出发城市");
    model->setHeaderData(2,Qt::Horizontal,"到达城市");
    model->setHeaderData(3,Qt::Horizontal,"出发时间");
    model->setHeaderData(4,Qt::Horizontal,"到达时间");
    model->setHeaderData(5,Qt::Horizontal,"状态");

    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0,90);
    ui->tableView->setColumnWidth(3,170);
    ui->tableView->setColumnWidth(4,170);
    ui->tableView->setColumnWidth(5,90);


}

Timetable_Widget::~Timetable_Widget()
{
    delete ui;
}
