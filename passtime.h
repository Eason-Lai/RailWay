#ifndef PASSTIME_H
#define PASSTIME_H

#include <QWidget>

namespace Ui {
class PassTime;
}

class PassTime : public QWidget
{
    Q_OBJECT

public:
    explicit PassTime(QWidget *parent = nullptr);
    ~PassTime();

signals:
    void sendData(int n);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
private:
    Ui::PassTime *ui;
};

#endif // PASSTIME_H
