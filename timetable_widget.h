#ifndef TIMETABLE_WIDGET_H
#define TIMETABLE_WIDGET_H

#include <QWidget>

namespace Ui {
class Timetable_Widget;
}

class Timetable_Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Timetable_Widget(QWidget *parent = nullptr);
    ~Timetable_Widget();

private:
    Ui::Timetable_Widget *ui;
};

#endif // TIMETABLE_WIDGET_H
