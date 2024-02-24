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


private slots:

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    void chongjiandashiCreate();
    void wanggedashiCreate();
    void mofangCreate();
    void initLoading();

private:
    Ui::MainWindow *ui;
    QWidget* chongjiandashiContainer = nullptr;
    QWidget* wanggedashiContainer = nullptr;
    QWidget* mofangContainer = nullptr;
    VirusManagerWindow *m_virusManager;
};
#endif // MAINWINDOW_H
