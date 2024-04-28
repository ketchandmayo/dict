#ifndef MANEUVERSETTINGSWIDGET_H
#define MANEUVERSETTINGSWIDGET_H

#include <QWidget>
#include "ui_ManeuverSettingsWidget.h"

class ManeuverSettingsWidget : public QDialog
{
    Q_OBJECT
public:
    explicit ManeuverSettingsWidget(QWidget *parent = 0);

signals:

public slots:

private:
    Ui::Form ui;

};

#endif // MANEUVERSETTINGSWIDGET_H
