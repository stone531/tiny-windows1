#ifndef VIRUSMANAGERWINDOW_H
#define VIRUSMANAGERWINDOW_H

#include <QDialog>
#include <addvirusdialog.h>
#include <QTableWidgetItem>
namespace Ui {
class VirusManagerWindow;
}

class VirusManagerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit VirusManagerWindow(QWidget *parent = nullptr);
    ~VirusManagerWindow();

private:
    void initTableWidget(QTableWidget *pTableWidget);
    QStringList DefaultHeaderDatas();
private slots:
    void showAddDialog();
    void QueryTable();
private:
    Ui::VirusManagerWindow *ui;

    addVirusDialog *m_addVirusDialog;
};

#endif // VIRUSMANAGERWINDOW_H
