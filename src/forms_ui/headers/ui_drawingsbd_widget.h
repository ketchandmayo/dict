/********************************************************************************
** Form generated from reading UI file 'drawingsbd_widget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRAWINGSBD_WIDGET_H
#define UI_DRAWINGSBD_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DrawingsBDWidget
{
public:
    QGridLayout *gridLayout;
    QGraphicsView *graphicsView;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QDoubleSpinBox *doubleSpinBoxMaxRadius;
    QLabel *label;

    void setupUi(QWidget *DrawingsBDWidget)
    {
        if (DrawingsBDWidget->objectName().isEmpty())
            DrawingsBDWidget->setObjectName(QString::fromUtf8("DrawingsBDWidget"));
        DrawingsBDWidget->resize(1015, 666);
        QFont font;
        font.setFamily(QString::fromUtf8("Liberation Sans"));
        font.setBold(true);
        font.setWeight(75);
        DrawingsBDWidget->setFont(font);
        gridLayout = new QGridLayout(DrawingsBDWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        graphicsView = new QGraphicsView(DrawingsBDWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        QPalette palette;
        QBrush brush(QColor(38, 38, 38, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        graphicsView->setPalette(palette);
        graphicsView->setMouseTracking(true);
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setRenderHints(QPainter::TextAntialiasing);
        graphicsView->setDragMode(QGraphicsView::NoDrag);
        graphicsView->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
        graphicsView->setResizeAnchor(QGraphicsView::AnchorViewCenter);
        graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
        graphicsView->setRubberBandSelectionMode(Qt::IntersectsItemShape);

        gridLayout->addWidget(graphicsView, 0, 0, 2, 1);

        groupBox = new QGroupBox(DrawingsBDWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        doubleSpinBoxMaxRadius = new QDoubleSpinBox(groupBox);
        doubleSpinBoxMaxRadius->setObjectName(QString::fromUtf8("doubleSpinBoxMaxRadius"));
        doubleSpinBoxMaxRadius->setMaximum(1600);

        gridLayout_2->addWidget(doubleSpinBoxMaxRadius, 0, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setWordWrap(true);

        gridLayout_2->addWidget(label, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox, 0, 1, 1, 1);


        retranslateUi(DrawingsBDWidget);

        QMetaObject::connectSlotsByName(DrawingsBDWidget);
    } // setupUi

    void retranslateUi(QWidget *DrawingsBDWidget)
    {
        DrawingsBDWidget->setWindowTitle(QApplication::translate("DrawingsBDWidget", "Form", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("DrawingsBDWidget", "GroupBox", 0, QApplication::UnicodeUTF8));
        doubleSpinBoxMaxRadius->setSuffix(QApplication::translate("DrawingsBDWidget", "\320\272\320\274", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("DrawingsBDWidget", "\320\234\320\260\320\272\321\201\320\270\320\274\320\260\320\273\321\214\320\275\321\213\320\271 \321\200\320\260\320\264\320\270\321\203\321\201 \321\200\320\260\320\267\320\262\320\276\321\200\320\276\321\202\320\260", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DrawingsBDWidget: public Ui_DrawingsBDWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRAWINGSBD_WIDGET_H
