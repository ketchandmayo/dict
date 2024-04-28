#ifndef DRAWINGSBD_WIDGET_H
#define DRAWINGSBD_WIDGET_H

#include <QWidget>

#include "ui_drawingsbd_widget.h"
#include "../graphics/GraphicsEngine.hpp"

class DrawingsBDWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DrawingsBDWidget(QWidget *parent = 0);
    ~DrawingsBDWidget();

signals:
    void sigSetMaximumRadius(double radius);

public slots:

private slots:

private:
    Ui::DrawingsBDWidget ui;
    GraphicsEngine*      m_graphicsEngine;

    void init();

    void connectSigSlot();
};

#endif // DRAWINGSBD_WIDGET_H
