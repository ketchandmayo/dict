/********************************************************************************
** Form generated from reading UI file 'maneuverwidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANEUVERWIDGET_H
#define UI_MANEUVERWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QTimeEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ManeuverWidget
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QTimeEdit *timeEditEndManeuver;
    QLabel *lblTimeEndManeuver;
    QLabel *lblTimeStartManeuver;
    QTimeEdit *timeEditStartManeuver;
    QLabel *lblRadius;
    QDoubleSpinBox *doubleSpinBoxRadius;
    QLabel *lblMaxOverload;
    QDoubleSpinBox *doubleSpinBoxMaxOverload;
    QGroupBox *groupBoxParameters;
    QGridLayout *gridLayout_2;
    QDoubleSpinBox *doubleSpinBoxEndCourse;
    QDoubleSpinBox *doubleSpinBoxStartCourse;
    QLabel *lblCourse;
    QDoubleSpinBox *doubleSpinBoxStartHeight;
    QDoubleSpinBox *doubleSpinBoxEndSpeed;
    QLabel *lblStartParam;
    QLabel *lblHeight;
    QDoubleSpinBox *doubleSpinBoxEndHeight;
    QDoubleSpinBox *doubleSpinBoxStartSpeed;
    QLabel *lblEndParam;
    QLabel *lblSpeed;

    void setupUi(QWidget *ManeuverWidget)
    {
        if (ManeuverWidget->objectName().isEmpty())
            ManeuverWidget->setObjectName(QString::fromUtf8("ManeuverWidget"));
        ManeuverWidget->resize(253, 317);
        gridLayout = new QGridLayout(ManeuverWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox = new QGroupBox(ManeuverWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        timeEditEndManeuver = new QTimeEdit(groupBox);
        timeEditEndManeuver->setObjectName(QString::fromUtf8("timeEditEndManeuver"));

        gridLayout_3->addWidget(timeEditEndManeuver, 1, 1, 1, 1);

        lblTimeEndManeuver = new QLabel(groupBox);
        lblTimeEndManeuver->setObjectName(QString::fromUtf8("lblTimeEndManeuver"));

        gridLayout_3->addWidget(lblTimeEndManeuver, 1, 0, 1, 1);

        lblTimeStartManeuver = new QLabel(groupBox);
        lblTimeStartManeuver->setObjectName(QString::fromUtf8("lblTimeStartManeuver"));

        gridLayout_3->addWidget(lblTimeStartManeuver, 0, 0, 1, 1);

        timeEditStartManeuver = new QTimeEdit(groupBox);
        timeEditStartManeuver->setObjectName(QString::fromUtf8("timeEditStartManeuver"));

        gridLayout_3->addWidget(timeEditStartManeuver, 0, 1, 1, 1);

        lblRadius = new QLabel(groupBox);
        lblRadius->setObjectName(QString::fromUtf8("lblRadius"));
        lblRadius->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(lblRadius, 3, 0, 1, 1);

        doubleSpinBoxRadius = new QDoubleSpinBox(groupBox);
        doubleSpinBoxRadius->setObjectName(QString::fromUtf8("doubleSpinBoxRadius"));

        gridLayout_3->addWidget(doubleSpinBoxRadius, 3, 1, 1, 1);

        lblMaxOverload = new QLabel(groupBox);
        lblMaxOverload->setObjectName(QString::fromUtf8("lblMaxOverload"));
        lblMaxOverload->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(lblMaxOverload, 4, 0, 1, 1);

        doubleSpinBoxMaxOverload = new QDoubleSpinBox(groupBox);
        doubleSpinBoxMaxOverload->setObjectName(QString::fromUtf8("doubleSpinBoxMaxOverload"));

        gridLayout_3->addWidget(doubleSpinBoxMaxOverload, 4, 1, 1, 1);

        groupBoxParameters = new QGroupBox(groupBox);
        groupBoxParameters->setObjectName(QString::fromUtf8("groupBoxParameters"));
        groupBoxParameters->setFlat(true);
        gridLayout_2 = new QGridLayout(groupBoxParameters);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        doubleSpinBoxEndCourse = new QDoubleSpinBox(groupBoxParameters);
        doubleSpinBoxEndCourse->setObjectName(QString::fromUtf8("doubleSpinBoxEndCourse"));

        gridLayout_2->addWidget(doubleSpinBoxEndCourse, 3, 2, 1, 1);

        doubleSpinBoxStartCourse = new QDoubleSpinBox(groupBoxParameters);
        doubleSpinBoxStartCourse->setObjectName(QString::fromUtf8("doubleSpinBoxStartCourse"));
        doubleSpinBoxStartCourse->setEnabled(false);

        gridLayout_2->addWidget(doubleSpinBoxStartCourse, 3, 1, 1, 1);

        lblCourse = new QLabel(groupBoxParameters);
        lblCourse->setObjectName(QString::fromUtf8("lblCourse"));

        gridLayout_2->addWidget(lblCourse, 3, 0, 1, 1);

        doubleSpinBoxStartHeight = new QDoubleSpinBox(groupBoxParameters);
        doubleSpinBoxStartHeight->setObjectName(QString::fromUtf8("doubleSpinBoxStartHeight"));
        doubleSpinBoxStartHeight->setEnabled(false);

        gridLayout_2->addWidget(doubleSpinBoxStartHeight, 2, 1, 1, 1);

        doubleSpinBoxEndSpeed = new QDoubleSpinBox(groupBoxParameters);
        doubleSpinBoxEndSpeed->setObjectName(QString::fromUtf8("doubleSpinBoxEndSpeed"));

        gridLayout_2->addWidget(doubleSpinBoxEndSpeed, 1, 2, 1, 1);

        lblStartParam = new QLabel(groupBoxParameters);
        lblStartParam->setObjectName(QString::fromUtf8("lblStartParam"));

        gridLayout_2->addWidget(lblStartParam, 0, 1, 1, 1);

        lblHeight = new QLabel(groupBoxParameters);
        lblHeight->setObjectName(QString::fromUtf8("lblHeight"));

        gridLayout_2->addWidget(lblHeight, 2, 0, 1, 1);

        doubleSpinBoxEndHeight = new QDoubleSpinBox(groupBoxParameters);
        doubleSpinBoxEndHeight->setObjectName(QString::fromUtf8("doubleSpinBoxEndHeight"));

        gridLayout_2->addWidget(doubleSpinBoxEndHeight, 2, 2, 1, 1);

        doubleSpinBoxStartSpeed = new QDoubleSpinBox(groupBoxParameters);
        doubleSpinBoxStartSpeed->setObjectName(QString::fromUtf8("doubleSpinBoxStartSpeed"));
        doubleSpinBoxStartSpeed->setEnabled(false);

        gridLayout_2->addWidget(doubleSpinBoxStartSpeed, 1, 1, 1, 1);

        lblEndParam = new QLabel(groupBoxParameters);
        lblEndParam->setObjectName(QString::fromUtf8("lblEndParam"));

        gridLayout_2->addWidget(lblEndParam, 0, 2, 1, 1);

        lblSpeed = new QLabel(groupBoxParameters);
        lblSpeed->setObjectName(QString::fromUtf8("lblSpeed"));

        gridLayout_2->addWidget(lblSpeed, 1, 0, 1, 1);


        gridLayout_3->addWidget(groupBoxParameters, 2, 0, 1, 2);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);


        retranslateUi(ManeuverWidget);

        QMetaObject::connectSlotsByName(ManeuverWidget);
    } // setupUi

    void retranslateUi(QWidget *ManeuverWidget)
    {
        ManeuverWidget->setWindowTitle(QApplication::translate("ManeuverWidget", "Form", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("ManeuverWidget", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \320\234\320\260\320\275\320\265\320\262\321\200\320\260", 0, QApplication::UnicodeUTF8));
        timeEditEndManeuver->setDisplayFormat(QApplication::translate("ManeuverWidget", "HH:mm:ss", 0, QApplication::UnicodeUTF8));
        lblTimeEndManeuver->setText(QApplication::translate("ManeuverWidget", "\320\242 \320\272\320\276\320\275\321\206\320\260 \320\274\320\260\320\275\320\265\320\262\321\200\320\260", 0, QApplication::UnicodeUTF8));
        lblTimeStartManeuver->setText(QApplication::translate("ManeuverWidget", "\320\242 \320\275\320\260\321\207\320\260\320\273\320\260 \320\274\320\260\320\275\320\265\320\262\321\200\320\260", 0, QApplication::UnicodeUTF8));
        timeEditStartManeuver->setDisplayFormat(QApplication::translate("ManeuverWidget", "HH:mm:ss", 0, QApplication::UnicodeUTF8));
        lblRadius->setText(QApplication::translate("ManeuverWidget", "\320\240\320\260\320\264\320\270\321\203\321\201", 0, QApplication::UnicodeUTF8));
        lblMaxOverload->setText(QApplication::translate("ManeuverWidget", "Max. \320\277\320\265\321\200\320\265\320\263\321\200\321\203\320\267\320\272\320\260", 0, QApplication::UnicodeUTF8));
        groupBoxParameters->setTitle(QString());
        lblCourse->setText(QApplication::translate("ManeuverWidget", "Q", 0, QApplication::UnicodeUTF8));
        lblStartParam->setText(QApplication::translate("ManeuverWidget", "\320\222 \320\275\320\260\321\207\320\260\320\273\320\265", 0, QApplication::UnicodeUTF8));
        lblHeight->setText(QApplication::translate("ManeuverWidget", "H", 0, QApplication::UnicodeUTF8));
        lblEndParam->setText(QApplication::translate("ManeuverWidget", "\320\222 \320\272\320\276\320\275\321\206\320\265", 0, QApplication::UnicodeUTF8));
        lblSpeed->setText(QApplication::translate("ManeuverWidget", "V", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ManeuverWidget: public Ui_ManeuverWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANEUVERWIDGET_H
