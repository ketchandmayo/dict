#ifndef MANEUVERWIDGET_H
#define MANEUVERWIDGET_H

#include <QWidget>
#include "ui_maneuverwidget.h"

class ManeuverWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ManeuverWidget(QWidget *parent = 0);
    ~ManeuverWidget();

private:
    Ui::ManeuverWidget ui;
};

#endif // MANEUVERWIDGET_H
