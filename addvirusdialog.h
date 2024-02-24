#ifndef ADDVIRUSDIALOG_H
#define ADDVIRUSDIALOG_H

#include <QDialog>

namespace Ui {
class addVirusDialog;
}

class addVirusDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addVirusDialog(QWidget *parent = nullptr);
    ~addVirusDialog();

public:
    int m_virusType;
    QString m_virusName;
    QString m_virusPic;
    QString m_virusNum;
    int m_virusLevel;
    QString m_virusSize;
    QString m_virusLocal;
    QString m_virusCheckTime;
    int m_virusStatus;
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    void addVirusType();
    void initData();
    void addVirusLevel();
    void addVirusStatus();
private:
    Ui::addVirusDialog *ui;
};

#endif // ADDVIRUSDIALOG_H
