#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QMouseEvent>
#include "background.h"
#include "add.h"
#include "timetable_widget.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtDebug>
#include <QPushButton>
#include <QRadioButton>
#include "data.h"
#include "passtime.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void mouseMoveEvent(QMouseEvent *event);
    bool createConnection();
    QLabel *MouseX;
    QLabel *MouseY;
    QLabel *qltime;
    Background *bg;
    ~MainWindow();

private slots:
    void on_action_triggered();

    void on_action_2_triggered();

    void on_action_3_triggered();

    void getData(int n);
private:
//    std::vector<City> citylist;
//    std::vector<Train> trainlist;
    PassTime *pt;
    QSqlDatabase db;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
