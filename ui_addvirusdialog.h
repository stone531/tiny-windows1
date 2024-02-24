/********************************************************************************
** Form generated from reading UI file 'addvirusdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDVIRUSDIALOG_H
#define UI_ADDVIRUSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_addVirusDialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QComboBox *comboBox;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QLabel *label_4;
    QLineEdit *lineEdit_2;
    QLabel *label_5;
    QLineEdit *lineEdit_3;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_9;
    QComboBox *comboBox_2;
    QLabel *label_10;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QLabel *label_11;
    QComboBox *comboBox_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QDateTimeEdit *dateTimeEdit;

    void setupUi(QDialog *addVirusDialog)
    {
        if (addVirusDialog->objectName().isEmpty())
            addVirusDialog->setObjectName(QString::fromUtf8("addVirusDialog"));
        addVirusDialog->resize(364, 458);
        label = new QLabel(addVirusDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 10, 51, 21));
        label_2 = new QLabel(addVirusDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 40, 71, 16));
        comboBox = new QComboBox(addVirusDialog);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(150, 40, 181, 31));
        label_3 = new QLabel(addVirusDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(40, 80, 71, 16));
        lineEdit = new QLineEdit(addVirusDialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(150, 80, 181, 31));
        label_4 = new QLabel(addVirusDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(40, 120, 71, 16));
        lineEdit_2 = new QLineEdit(addVirusDialog);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(150, 120, 181, 31));
        label_5 = new QLabel(addVirusDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(40, 160, 71, 16));
        lineEdit_3 = new QLineEdit(addVirusDialog);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(150, 160, 181, 31));
        label_6 = new QLabel(addVirusDialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(40, 210, 71, 16));
        label_7 = new QLabel(addVirusDialog);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(40, 250, 61, 16));
        label_9 = new QLabel(addVirusDialog);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(40, 290, 54, 12));
        comboBox_2 = new QComboBox(addVirusDialog);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(150, 200, 181, 31));
        label_10 = new QLabel(addVirusDialog);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(40, 330, 71, 16));
        lineEdit_4 = new QLineEdit(addVirusDialog);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(150, 240, 181, 31));
        lineEdit_5 = new QLineEdit(addVirusDialog);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(150, 280, 181, 31));
        label_11 = new QLabel(addVirusDialog);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(40, 370, 71, 16));
        comboBox_3 = new QComboBox(addVirusDialog);
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));
        comboBox_3->setGeometry(QRect(150, 360, 181, 31));
        pushButton = new QPushButton(addVirusDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(69, 410, 101, 31));
        pushButton_2 = new QPushButton(addVirusDialog);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(240, 410, 91, 31));
        dateTimeEdit = new QDateTimeEdit(addVirusDialog);
        dateTimeEdit->setObjectName(QString::fromUtf8("dateTimeEdit"));
        dateTimeEdit->setGeometry(QRect(150, 321, 181, 31));

        retranslateUi(addVirusDialog);

        QMetaObject::connectSlotsByName(addVirusDialog);
    } // setupUi

    void retranslateUi(QDialog *addVirusDialog)
    {
        addVirusDialog->setWindowTitle(QCoreApplication::translate("addVirusDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("addVirusDialog", "\346\267\273\345\212\240", nullptr));
        label_2->setText(QCoreApplication::translate("addVirusDialog", "\347\227\205\346\257\222\347\261\273\345\236\213", nullptr));
        label_3->setText(QCoreApplication::translate("addVirusDialog", "\347\227\205\346\257\222\345\220\215\347\247\260", nullptr));
        label_4->setText(QCoreApplication::translate("addVirusDialog", "\345\233\276\347\211\207\345\234\260\345\235\200", nullptr));
        label_5->setText(QCoreApplication::translate("addVirusDialog", "\347\227\205\346\257\222\347\274\226\347\240\201", nullptr));
        label_6->setText(QCoreApplication::translate("addVirusDialog", "\347\227\205\346\257\222\347\272\247\345\210\253", nullptr));
        label_7->setText(QCoreApplication::translate("addVirusDialog", "\345\260\272   \345\257\270", nullptr));
        label_9->setText(QCoreApplication::translate("addVirusDialog", "\344\275\215  \347\275\256", nullptr));
        label_10->setText(QCoreApplication::translate("addVirusDialog", "\346\243\200\346\265\213\346\227\266\351\227\264", nullptr));
        label_11->setText(QCoreApplication::translate("addVirusDialog", "\345\244\204\347\220\206\347\212\266\346\200\201", nullptr));
        pushButton->setText(QCoreApplication::translate("addVirusDialog", "\345\217\226\346\266\210", nullptr));
        pushButton_2->setText(QCoreApplication::translate("addVirusDialog", "\347\241\256\350\256\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class addVirusDialog: public Ui_addVirusDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDVIRUSDIALOG_H
