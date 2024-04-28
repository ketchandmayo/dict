/********************************************************************************
** Form generated from reading UI file 'ManeuverSettingsWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANEUVERSETTINGSWIDGET_H
#define UI_MANEUVERSETTINGSWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QGridLayout *gridLayout;
    QGraphicsView *graphicsView;
    QGroupBox *groupBox;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;

    void setupUi(QDialog *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->setWindowModality(Qt::WindowModal);
        Form->resize(1280, 840);
        Form->setModal(true);
        gridLayout = new QGridLayout(Form);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        graphicsView = new QGraphicsView(Form);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        gridLayout->addWidget(graphicsView, 0, 1, 1, 1);

        groupBox = new QGroupBox(Form);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        checkBox = new QCheckBox(groupBox);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(20, 40, 161, 20));
        checkBox_2 = new QCheckBox(groupBox);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setGeometry(QRect(20, 70, 141, 20));

        gridLayout->addWidget(groupBox, 0, 0, 1, 1);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QDialog *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("Form", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270 \320\274\320\260\321\200\321\210\321\200\321\203\321\202\320\260 \320\222\320\236", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("Form", "\320\223\321\200\320\260\321\204\320\270\320\272 \320\262\321\213\321\201\320\276\321\202\321\213", 0, QApplication::UnicodeUTF8));
        checkBox_2->setText(QApplication::translate("Form", "\320\223\321\200\320\260\321\204\320\270\320\272 \321\201\320\272\320\276\321\200\320\276\321\201\321\202\320\270", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANEUVERSETTINGSWIDGET_H
