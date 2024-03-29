#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QtWidgets/QWidget>
#include <QWindow>
#include <Windows.h>
#include <QDebug>
#include <QVBoxLayout>
#include <qprocess.h>
#include <QPushButton>
//#include <qwinwidget.h>
#include <qfile.h>
#include "datamanager.h"
#include <iostream>

#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>

/*const QString pathfun = "D:/BaiduNetdiskDownload/20240220/ModelFun/ModelFun.exe";
const QString pathwange = "D:/BaiduNetdiskDownload/20240220/GridMaster_V1.0.7/GridMaster.exe";
const QString pathchongjian = "D:/BaiduNetdiskDownload/20240220/重建大师/G3D64.exe";
*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showMaximized();
    //this->setFixedSize(1500, 1200);
    setWindowState(Qt::WindowFullScreen);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    readFileConfig();
    initLoading();

    DataManager::GetInstance();

    if (mofangContainer)
    {
        mofangContainer->setVisible(true);
    }
    if (chongjiandashiContainer)
    {
        chongjiandashiContainer->setVisible(false);
    }
    if (wanggedashiContainer)
    {
        wanggedashiContainer->setVisible(false);
    }

    /*if (mofangContainer)
    {
        mofangContainer->setFixedSize(ui->centerWidget->size());
    }
    if (chongjiandashiContainer)
    {
        chongjiandashiContainer->setFixedSize(ui->centerWidget->size());
    }
    if (wanggedashiContainer)
    {
        wanggedashiContainer->setFixedSize(ui->centerWidget->size());
    }*/

    //connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::on_pushButton_5_clicked);

    std::vector<Virus_Detail*> allV = DataManager::GetInstance()->queryAllVir();
    for(auto newButton : allV) {
        QPushButton *tmpButton = new QPushButton(CCommFunc::getVirusType(newButton->virType));
        ui->verticalLayout->addWidget(tmpButton);
        ui->verticalLayout->insertWidget(1, tmpButton);
        tmpButton->setFixedHeight(60);
        tmpButton->setFixedWidth(200);
        connect(tmpButton, &QPushButton::clicked, [=]() {
            QMessageBox::information(this, CCommFunc::getVirusType(newButton->virType), "Button 1 was clicked!");
        });
    }
    initButtonSize();
}
HWND createhandle(const QString& title, const QString& path)
{
    HWND hwnd = FindWindowEx(0, 0, L"Qt5QWindowIcon", (LPWSTR)title.toStdWString().c_str());
    if (hwnd == NULL) {
        STARTUPINFO si = { sizeof(si) };
        PROCESS_INFORMATION pi;
        si.dwFlags = STARTF_USESHOWWINDOW;
        si.wShowWindow = SW_NORMAL;
        bool bRet = CreateProcess(
            NULL,
            (LPWSTR)path.toStdWString().c_str(),
            NULL,
            NULL,
            FALSE,
            CREATE_NEW_CONSOLE,
            NULL,
            NULL, &si, &pi);
        if (!bRet) return hwnd;
        while (hwnd == NULL) {
           // hwnd = FindWindow(0, (LPWSTR)title.toStdWString().c_str());
            hwnd = FindWindowEx(0, 0, L"Qt5QWindowIcon", (LPWSTR)title.toStdWString().c_str());
            Sleep(1000);
        }
    }
    //hwnd = FindWindow(0, (LPWSTR)title.toStdWString().c_str());
    return hwnd;

}


void MainWindow::chongjiandashiCreate()
{
    //HWND hwnd = FindWindowEx(0, 0, L"Qt5QWindowIcon", L"重建大师v6.2.23.758");
    //if (hwnd == NULL) {
    //   // system("F:/公司项目/公路院项目/重建大师/G3D64.exe");
    //    QString cmd = "F:/公司项目/公路院项目/重建大师/G3D64.exe";
    //    STARTUPINFO si = { sizeof(si) };
    //    PROCESS_INFORMATION pi;
    //    si.dwFlags = STARTF_USESHOWWINDOW;
    //    si.wShowWindow = true;
    //    bool bRet = CreateProcess(
    //        NULL,
    //        (LPWSTR)cmd.toStdWString().c_str(),
    //        NULL,
    //        NULL,
    //        FALSE,
    //        CREATE_NEW_CONSOLE,
    //        NULL,
    //        NULL, &si, &pi);
    //    if (!bRet) return;

    //    while (hwnd == NULL) {
    //        hwnd = FindWindowEx(0, 0, L"Qt5QWindowIcon", L"重建大师v6.2.23.758");
    //        Sleep(1000);
    //    }
    //}

    auto hwnd = createhandle("重建大师v6.2.23.758", pathchongjian);
    qDebug()<<"重建大师 hwnd"<<hwnd;
    if (!hwnd) return;
    QWindow* window = QWindow::fromWinId((WId)hwnd);
    chongjiandashiContainer = createWindowContainer(window, ui->centerWidget);

    qDebug()<<"重建大师 1111 :"<<chongjiandashiContainer;
    //chongjiandashiContainer->setFixedSize(ui->centerWidget->size());
    ui->centerLayout->addWidget(chongjiandashiContainer);
    qDebug()<<"重建大师 2222";
}
void MainWindow::on_pushButton_clicked()
{
    if (mofangContainer)
        mofangContainer->setVisible(true);

    if (wanggedashiContainer)
        wanggedashiContainer->setHidden(true);

    if (chongjiandashiContainer)
        chongjiandashiContainer->setHidden(true);

    ui->centerWidget->update();
    ui->centerLayout->update();
}

void MainWindow::on_pushButton_2_clicked()
{
    if (wanggedashiContainer)
        wanggedashiContainer->setVisible(true);
    if (mofangContainer)
        mofangContainer->setHidden(true);
    if (chongjiandashiContainer)
        chongjiandashiContainer->setHidden(true);


    ui->centerWidget->update();
    ui->centerLayout->update();
}
void MainWindow::on_pushButton_3_clicked()
{
    if (chongjiandashiContainer)
        chongjiandashiContainer->setVisible(true);
    if (mofangContainer)
        mofangContainer->setHidden(true);
    if (wanggedashiContainer)
        wanggedashiContainer->setHidden(true);

    ui->centerWidget->update();
    ui->centerLayout->update();
}

void MainWindow::showNewWindow() {

}
void MainWindow::wanggedashiCreate()
{
    //HWND hwnd = FindWindowEx(0, 0, L"Qt5QWindowIcon", L"网格大师");
    //if (hwnd == NULL) {
    //    //system("F:/公司项目/公路院项目/网格大师/网格大师.exe");
    //    QString cmd = "F:/公司项目/公路院项目/网格大师/网格大师.exe";
    //    STARTUPINFO si = { sizeof(si) };
    //    PROCESS_INFORMATION pi;
    //    si.dwFlags = STARTF_USESHOWWINDOW;
    //    si.wShowWindow = true;
    //    bool bRet = CreateProcess(
    //        NULL,
    //        (LPWSTR)cmd.toStdWString().c_str(),
    //        NULL,
    //        NULL,
    //        FALSE,
    //        CREATE_NEW_CONSOLE,
    //        NULL,
    //        NULL, &si, &pi);
    //    if (!bRet) return;
    //    while (hwnd == NULL) {
    //        hwnd = FindWindowEx(0, 0, L"Qt5QWindowIcon", L"网格大师");
    //        Sleep(1000);
    //    }
    //}
    auto hwnd = createhandle("网格大师", pathwange);
    if (!hwnd) return;
    QWindow* window = QWindow::fromWinId((WId)hwnd);
    wanggedashiContainer = createWindowContainer(window, ui->centerWidget);
    //wanggedashiContainer->setHidden(true);
    //wanggedashiContainer->setFixedSize(ui->centerWidget->size());
    ui->centerLayout->addWidget(wanggedashiContainer);
}

void MainWindow::mofangCreate()
{
    //HWND hwnd = FindWindowEx(0, 0, L"Qt5QWindowIcon", L"模方ModelFun @ 大势智慧");
    //if (hwnd == NULL) {
    //    ///system("F:/公司项目/公路院项目/ModelFun/ModelFun.exe");
    //    QString cmd = "F:/公司项目/公路院项目/ModelFun/ModelFun.exe";
    //    STARTUPINFO si = { sizeof(si) };
    //    PROCESS_INFORMATION pi;
    //    si.dwFlags = STARTF_USESHOWWINDOW;
    //    si.wShowWindow = true;

    //    bool bRet = CreateProcess(
    //        NULL,
    //        (LPWSTR)cmd.toStdWString().c_str(),
    //        NULL,
    //        NULL,
    //        FALSE,
    //        CREATE_NEW_CONSOLE,
    //        NULL,
    //        NULL, &si, &pi);
    //    if (!bRet) return;

    //    while (hwnd == NULL) {
    //        hwnd = FindWindowEx(0, 0, L"Qt5QWindowIcon", L"模方ModelFun @ 大势智慧");
    //        Sleep(1000);
    //    }
    //}

    auto hwnd = createhandle("模方ModelFun @ 大势智慧", pathfun);
    if (!hwnd) return;
    QWindow* window = QWindow::fromWinId((WId)hwnd);
    mofangContainer = createWindowContainer(window, ui->centerWidget);
    ui->centerLayout->addWidget(mofangContainer);
}

void MainWindow::initLoading()
{
    chongjiandashiCreate();
    wanggedashiCreate();
    mofangCreate();
}

void MainWindow::readFileConfig()
{
    QString fileName = QCoreApplication::applicationDirPath() + "/appPath.txt";
    QFile file(fileName);//txt的路径
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    QTextStream in(&file);
    QString line = in.readLine();
    while (!line.isNull())
    {
        auto list = line.split(":");
        if (list.size() != 2) continue;
        if (list[0].trimmed() == "ModelFun")  pathfun = list[1].trimmed();
        if (list[0].trimmed() == QString::fromUtf8("网格大师"))  pathwange = list[1].trimmed();
        if (list[0].trimmed() == QString::fromUtf8("重建大师"))  pathchongjian = list[1].trimmed();
        line = in.readLine();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_4_clicked()
{
    m_virusManager = new VirusManagerWindow(this);
    m_virusManager->show();
}

void MainWindow::on_pushButton_5_clicked()
{
    //TableView *tv = new TableView(this);
    //tv->setFixedSize(1000,800);
    //tv->show();

    //m_birdge = new bridgeManager;
    //m_birdge->show();
}

void MainWindow::initButtonSize(){
    ui->pushButton->setFixedHeight(60);
    ui->pushButton->setFixedWidth(200);

    ui->pushButton_2->setFixedHeight(60);
    ui->pushButton_2->setFixedWidth(200);

    ui->pushButton_3->setFixedHeight(60);
    ui->pushButton_3->setFixedWidth(200);

    ui->pushButton_4->setFixedHeight(60);
    ui->pushButton_4->setFixedWidth(200);

    ui->pushButton_8->setFixedHeight(60);
    ui->pushButton_8->setFixedWidth(200);

    ui->pushButton_5->setFixedHeight(60);
    ui->pushButton_5->setFixedWidth(200);
}
