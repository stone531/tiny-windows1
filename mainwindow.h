#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QProcess>
#include <Windows.h>
#include <QWindow>
#include <QVBoxLayout>
#include "virusmanagerwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
//private slots:
//    void startOpen();

private slots:
    void showNewWindow();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();


    void on_pushButton_4_clicked();

private:
    void chongjiandashiCreate();
    void wanggedashiCreate();
    void mofangCreate();
    void initLoading();

    void readFileConfig();
private:
    Ui::MainWindow *ui;

    VirusManagerWindow *m_virusManager;
    //QPushButton *m_pushButton_virusManager;
    QVBoxLayout *m_layout;

    QString pathfun = "../ModelFun/ModelFun.exe";
    QString pathwange = "../GridMaster_V1.0.7/GridMaster.exe";
    QString pathchongjian = "../g3d/G3D64.exe";
    QWidget* chongjiandashiContainer = nullptr;
    QWidget* wanggedashiContainer = nullptr;
    QWidget* mofangContainer = nullptr;

};
#endif // MAINWINDOW_H
