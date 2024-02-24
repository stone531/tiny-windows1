#include "virusmanagerwindow.h"
#include "ui_virusmanagerwindow.h"
#include <QTableWidget>

#include <QVBoxLayout>
#include <QWidget>
#include <qdebug.h>

VirusManagerWindow::VirusManagerWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VirusManagerWindow)
{
    ui->setupUi(this);
    setWindowTitle("病毒管理窗口");
    this->setFixedSize(800, 500);
     connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(showAddDialog()));

     //QStandardItemModel model(5, 3);
     //model.setHorizontalHeaderLabels({"列1", "列2", "列3"});
     //ui->printAgeingTableView->setIndexWidget(standardItemModel->index(i, 5), interval);
     //QWidget mainWindow;
    initTableWidget(ui->tableWidget);

    QueryTable();
}

VirusManagerWindow::~VirusManagerWindow()
{
    delete ui;
}


void VirusManagerWindow::showAddDialog()
{
    m_addVirusDialog = new addVirusDialog(this);
    m_addVirusDialog->show();
}

void VirusManagerWindow::initTableWidget(QTableWidget *pTableWidget)
{
    QTableWidget * tableWidget = pTableWidget;

    int iPixelSizeFont = 18;
#ifdef Def_ScreenPixel_19201080
    CRateHouse::Instance()->execute(iPixelSizeFont);
#endif

    QFont font;
//    font.setFamily(gGetFontPath());//设置字体类型
    font.setPixelSize(iPixelSizeFont);//设置字体像素大小
    font.setBold(false);//是否加粗

    //设置tablewidget
    tableWidget->setFrameShape(QFrame::NoFrame);//关闭边框
    tableWidget->setShowGrid(false);//关闭格子线
    tableWidget->setFocusPolicy(Qt::NoFocus);//关闭选中颜色
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止编辑
    tableWidget->setSelectionMode(QAbstractItemView::ContiguousSelection);//选中模式为多行选中
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows); //整行选中的方式
    tableWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);//像素滚动
    tableWidget->setColumnCount(7);//设置列数
    tableWidget->setRowCount(0);//设置行数

    //设置列头QHeaderView
    //tableWidget->setHorizontalHeaderLabels(DefaultHeaderDatas());//设置列标签
    tableWidget->setHorizontalHeaderLabels({"序号", "病害类型", "图片地址", "病害编码","病害级别","尺寸","位置","检测时间","处理状态","操作"});
    tableWidget->horizontalHeader()->setFont(font);//设置行字体
    tableWidget->horizontalHeader()->setDefaultSectionSize(150);//默认列宽
//    tableWidget->horizontalHeader()->setStretchLastSection(true); //行头自适应表格
//    tableWidget->horizontalHeader()->setVisible(false);//关闭行头
//    tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//关闭滑条

    //设置行头QHeaderView
    tableWidget->verticalHeader()->setFont(font);//设置行字体
    tableWidget->verticalHeader()->setDefaultSectionSize(150);//默认行高
    //    tableWidget->verticalHeader()->setVisible(false);//关闭列头
    //    tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//关闭滑条


}


QStringList VirusManagerWindow::DefaultHeaderDatas()
{
    QStringList dataList;
#if 1
    dataList.push_back("姓名1");
    dataList.push_back("姓名2");
    dataList.push_back("姓名3");
    dataList.push_back("姓名4");
    dataList.push_back("姓名5");
    dataList.push_back("姓名6");
    dataList.push_back("姓名7");
#endif
    return dataList;
}
void VirusManagerWindow::QueryTable() {
    qDebug()<<"start insert data";
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//可以选中单个

    int RowCont;
    RowCont=ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(RowCont);//增加一行

    //插入元素
    ui->tableWidget->setItem(RowCont,0,new QTableWidgetItem("1"));
    ui->tableWidget->setItem(RowCont,1,new QTableWidgetItem("KeyWord"));
    ui->tableWidget->setItem(RowCont,2,new QTableWidgetItem("PaperBrief"));
}
