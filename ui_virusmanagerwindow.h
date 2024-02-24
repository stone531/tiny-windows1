/********************************************************************************
** Form generated from reading UI file 'virusmanagerwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIRUSMANAGERWINDOW_H
#define UI_VIRUSMANAGERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_VirusManagerWindow
{
public:
    QLabel *label;
    QComboBox *comboBox;
    QLabel *label_2;
    QComboBox *comboBox_2;
    QLabel *label_3;
    QComboBox *comboBox_3;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QTableWidget *tableWidget;

    void setupUi(QDialog *VirusManagerWindow)
    {
        if (VirusManagerWindow->objectName().isEmpty())
            VirusManagerWindow->setObjectName(QString::fromUtf8("VirusManagerWindow"));
        VirusManagerWindow->resize(679, 370);
        label = new QLabel(VirusManagerWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 10, 54, 12));
        comboBox = new QComboBox(VirusManagerWindow);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(90, 10, 72, 22));
        label_2 = new QLabel(VirusManagerWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(170, 10, 54, 12));
        comboBox_2 = new QComboBox(VirusManagerWindow);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(230, 10, 72, 22));
        label_3 = new QLabel(VirusManagerWindow);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(310, 10, 54, 12));
        comboBox_3 = new QComboBox(VirusManagerWindow);
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));
        comboBox_3->setGeometry(QRect(370, 10, 51, 22));
        lineEdit = new QLineEdit(VirusManagerWindow);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(430, 10, 91, 20));
        pushButton = new QPushButton(VirusManagerWindow);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(540, 10, 51, 20));
        pushButton_2 = new QPushButton(VirusManagerWindow);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(610, 10, 51, 20));
        tableWidget = new QTableWidget(VirusManagerWindow);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(40, 60, 601, 201));

        retranslateUi(VirusManagerWindow);

        QMetaObject::connectSlotsByName(VirusManagerWindow);
    } // setupUi

    void retranslateUi(QDialog *VirusManagerWindow)
    {
        VirusManagerWindow->setWindowTitle(QCoreApplication::translate("VirusManagerWindow", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("VirusManagerWindow", "\347\227\205\346\257\222\347\261\273\345\236\213", nullptr));
        label_2->setText(QCoreApplication::translate("VirusManagerWindow", "\347\227\205\346\257\222\347\272\247\345\210\253", nullptr));
        label_3->setText(QCoreApplication::translate("VirusManagerWindow", "\345\244\204\347\220\206\347\212\266\346\200\201", nullptr));
        pushButton->setText(QCoreApplication::translate("VirusManagerWindow", "\346\237\245\346\211\276", nullptr));
        pushButton_2->setText(QCoreApplication::translate("VirusManagerWindow", "\346\267\273\345\212\240", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VirusManagerWindow: public Ui_VirusManagerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIRUSMANAGERWINDOW_H
