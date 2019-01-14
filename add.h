#ifndef ADD_H
#define ADD_H

#include <QWidget>
#include <QSqlQuery>
#include "data.h"
#include "math.h"

namespace Ui {
class add;
}

class add : public QWidget
{
    Q_OBJECT

public:
    explicit add(QWidget *parent = nullptr);
    ~add();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::add *ui;
    City city1;
    City city2;
    QDateTime qdt1;
    QDateTime qdt2;
    int cost;
};

#endif // ADD_H
