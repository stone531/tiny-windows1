#ifndef VIRUSMANAGERWINDOW_H
#define VIRUSMANAGERWINDOW_H

#include <QDialog>
#include <addvirusdialog.h>
#include <QTableWidgetItem>
#include <QVBoxLayout>
namespace Ui {
class VirusManagerWindow;
}

class VirusManagerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit VirusManagerWindow(QWidget *parent = nullptr);
    ~VirusManagerWindow();
protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    void initTableWidget(QTableWidget *pTableWidget);
    QStringList DefaultHeaderDatas();
private slots:
    void showAddDialog();
    void QueryTable();
private:
    Ui::VirusManagerWindow *ui;

    addVirusDialog *m_addVirusDialog;

    void addData(const QString &data);
    int countNonEmptyCells(QTableWidget *tableWidget);

    void initComboboxData();

    QString  convertQStringValue(int timeValue);
    void tablewidgePageInit(QVBoxLayout *nlayout);
    QPushButton *nextButton;
    QPushButton *prevButton;
    void nextPage();
    void prevPage();
    void populateTable();
    int currentPage;
    int pageSize;
private slots:
    void receiveData(const int &virType,const QString &virName,const QString &virPic,
                     const QString &virNum,const int &virLevel,const QString &virSize,
                     const QString &virLocal,const int &virTime,const int &virStatus);
    void deleteData();
    void editData();
    void on_findVir_clicked();
};

#endif // VIRUSMANAGERWINDOW_H
