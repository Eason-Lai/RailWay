#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <vector>
#include <QPropertyAnimation>
#include <QSqlQuery>
#include <math.h>
#include <data.h>

class Background : public QWidget
{
    Q_OBJECT
public:
    explicit Background(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void update();
    void play();
    double angele(int x1,int y1,int x2,int y2);
    void repaint();
signals:


public slots:


private:

};

#endif // BACKGROUND_H
