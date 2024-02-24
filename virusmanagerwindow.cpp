#include "virusmanagerwindow.h"
#include "ui_virusmanagerwindow.h"
#include <QTableWidget>
#include <QDateTime>
#include <QVBoxLayout>
#include <QWidget>
#include <qdebug.h>
#include <QContextMenuEvent>
#include <QMenu>
#include <QInputDialog>
#include <QPushButton>
#include "common.h"
#include "datamanager.h"
#include <QMessageBox>

VirusManagerWindow::VirusManagerWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VirusManagerWindow)
{
    qDebug() << "病害管理窗口";
    ui->setupUi(this);
    setWindowTitle("病害管理窗口");
    //ui->horizontalLayout->setGeometry(QRect(100, 100, 600, 100));
    //this->setFixedSize(900, 900);
    this->setFixedSize(1200, 600);

    ui->widget->setFixedSize(1100, 50);

    ui->tableWidget->setFixedSize(1100, 300);

     connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(showAddDialog()));

     //QStandardItemModel model(5, 3);
     //model.setHorizontalHeaderLabels({"列1", "列2", "列3"});
     //ui->printAgeingTableView->setIndexWidget(standardItemModel->index(i, 5), interval);
     //QWidget mainWindow;
    initTableWidget(ui->tableWidget);


    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu); // 设置为自定义上下文菜单策略
    connect(ui->tableWidget, &QTableWidget::customContextMenuRequested, [this](const QPoint &pos){
        QMenu *menu = new QMenu(this);
        QAction *editAction = new QAction("编辑", this);
        connect(editAction, &QAction::triggered, this, &VirusManagerWindow::editData);
        menu->addAction(editAction);

        QAction *deleteAction = new QAction("删除", this);
        connect(deleteAction, &QAction::triggered, this, &VirusManagerWindow::deleteData);
        menu->addAction(deleteAction);

        menu->popup(ui->tableWidget->viewport()->mapToGlobal(pos));
    });

    setLayout(new QVBoxLayout(this));
    layout()->addWidget(ui->tableWidget);

    QueryTable();
    initComboboxData();
}

VirusManagerWindow::~VirusManagerWindow()
{
    delete ui;
}


void VirusManagerWindow::showAddDialog()
{
    m_addVirusDialog = new addVirusDialog(this);
    connect(m_addVirusDialog, &addVirusDialog::dataAdded, this, &VirusManagerWindow::receiveData);
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
    tableWidget->setColumnCount(9);//设置列数
    tableWidget->setRowCount(0);//设置行数

    //设置列头QHeaderView
    //tableWidget->setHorizontalHeaderLabels(DefaultHeaderDatas());//设置列标签

    tableWidget->setHorizontalHeaderLabels({ "病害类型","病害名称", "图片地址", "病害编码","病害级别","尺寸","位置","检测时间","处理状态"});

    tableWidget->horizontalHeader()->setFont(font);//设置行字体
    tableWidget->horizontalHeader()->setDefaultSectionSize(100);//默认列宽
    tableWidget->horizontalHeader()->setStretchLastSection(true); //行头自适应表格
//    tableWidget->horizontalHeader()->setVisible(false);//关闭行头
//    tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//关闭滑条

    //设置行头QHeaderView
    tableWidget->verticalHeader()->setFont(font);//设置行字体
    tableWidget->verticalHeader()->setDefaultSectionSize(100);//默认行高
    //    tableWidget->verticalHeader()->setVisible(false);//关闭列头
    //    tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//关闭滑条


}


QStringList VirusManagerWindow::DefaultHeaderDatas()
{
    QStringList dataList;
#if 1
    dataList.push_back("姓名1");

#endif
    return dataList;
}
void VirusManagerWindow::QueryTable() {

    qDebug()<<"start insert data";
//    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
//    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
//    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//可以选中单个

    std::vector<Virus_Detail*> allV = DataManager::GetInstance()->queryAllVir();
    if(allV.empty()) return;

    int RowCont;
    for (auto element : allV) {
        RowCont=ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(RowCont);//增加一行

        ui->tableWidget->setItem(RowCont,0,new QTableWidgetItem(CCommFunc::getVirusType(element->virType)));
        ui->tableWidget->setItem(RowCont,1,new QTableWidgetItem(element->virName));
        ui->tableWidget->setItem(RowCont,2,new QTableWidgetItem(element->virPic));

        ui->tableWidget->setItem(RowCont,3,new QTableWidgetItem(element->virNum));
        ui->tableWidget->setItem(RowCont,4,new QTableWidgetItem(CCommFunc::getVirusLevel(element->virLevel)));
        ui->tableWidget->setItem(RowCont,5,new QTableWidgetItem(element->virSize));
        ui->tableWidget->setItem(RowCont,6,new QTableWidgetItem(element->virLocal));

        //qDebug()<<"aaaaaaaaaaaa time:"<<element->virTime;
        ui->tableWidget->setItem(RowCont,7,new QTableWidgetItem(convertQStringValue(element->virTime)));

        ui->tableWidget->setItem(RowCont,8,new QTableWidgetItem(CCommFunc::getVirusStatus(element->virStatus)));
        if (element != nullptr) {
            delete element;
            element = nullptr;
        }

     }
}

void VirusManagerWindow::receiveData(const int &virType,const QString &virName,const QString &virPic,
                                     const QString &virNum,const int &virLevel,const QString &virSize,
                                     const QString &virLocal,const int &virTime,const int &virStatus){
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    qDebug()<<"receiveData ===============data";
    //ui->tableWidget->setItem(row, 0, item);
    //插入元素
    //int numberOfNonEmptyCells = countNonEmptyCells(ui->tableWidget);
    //QTableWidgetItem *item = new QTableWidgetItem(QString::number(numberOfNonEmptyCells+1));
    //ui->tableWidget->setItem(row,0,item);

    ui->tableWidget->setItem(row,0,new QTableWidgetItem(CCommFunc::getVirusType(virType)));
    ui->tableWidget->setItem(row,1,new QTableWidgetItem(virName));
    ui->tableWidget->setItem(row,2,new QTableWidgetItem(virPic));

    ui->tableWidget->setItem(row,3,new QTableWidgetItem(virNum));
    ui->tableWidget->setItem(row,4,new QTableWidgetItem(CCommFunc::getVirusLevel(virLevel)));
    ui->tableWidget->setItem(row,5,new QTableWidgetItem(virSize));
    ui->tableWidget->setItem(row,6,new QTableWidgetItem(virLocal));

    ui->tableWidget->setItem(row,7,new QTableWidgetItem(convertQStringValue(virTime)));
    ui->tableWidget->setItem(row,8,new QTableWidgetItem(CCommFunc::getVirusStatus(virStatus)));

    DataManager::GetInstance()->addVirusInfo(virType,virName,virPic,virNum,virLevel,virSize,virLocal,virTime,virStatus);
}


void VirusManagerWindow::contextMenuEvent(QContextMenuEvent *event) {
    QMenu menu(this);
//    QAction addAction("Add Data", this);
//    connect(&addAction, &QAction::triggered, this, [this](){
//        addData("New Data");
//    });
//    menu.addAction(&addAction);

    QAction editAction("编辑", this);
    connect(&editAction, &QAction::triggered, this, &VirusManagerWindow::editData);
    menu.addAction(&editAction);

    QAction deleteAction("删除", this);
    connect(&deleteAction, &QAction::triggered, this, &VirusManagerWindow::deleteData);
    menu.addAction(&deleteAction);

    menu.exec(event->globalPos());
}

void VirusManagerWindow::addData(const QString &data) {
    //emit receiveData(data);
}

void VirusManagerWindow::deleteData() {
    //QList<QTableWidgetItem *> selectedItems = ui->tableWidget->selectedItems();
    //for (QTableWidgetItem *item : selectedItems) {
    //    ui->tableWidget->removeRow(item->row());
    //    delete item;
    //}
    int currentRow = ui->tableWidget->currentRow();
    if (currentRow != -1) { // 如果有行被选中

        QTableWidgetItem *item = ui->tableWidget->item(currentRow, 3); // column_index 是你想要获取数据的列索引
        if (item != nullptr) {
            QString virNum = item->text(); // 获取单元格文本数据
            qDebug()<<"select del data:"<<virNum;
            DataManager::GetInstance()->delVirus(virNum.toInt());
            ui->tableWidget->removeRow(currentRow); // 删除当前选中行
        }

    }
}

void VirusManagerWindow::editData() {
    int currentRow = ui->tableWidget->currentRow();
    int currentCol = ui->tableWidget->currentColumn();

    if (currentCol == 0 || currentCol == 3) {
        QMessageBox msg;
        msg.setText("禁止更新属性");
        msg.exec();
        return;
    }
    if (currentRow != -1) { // 如果有行被选中
        QTableWidgetItem *item = ui->tableWidget->item(currentRow, currentCol); // 获取当前选中行的第一列数据
        if (item) {
            bool ok;
            QString newData = QInputDialog::getText(this, "Edit Data", "请输入新的值:", QLineEdit::Normal, item->text(), &ok);
            if (ok && !newData.isEmpty()) {
                item->setText(newData); // 更新表格中的数据

                //get numid
                QTableWidgetItem *numItem = ui->tableWidget->item(currentRow, 3);
                int virNum =numItem->text().toInt();

                QString dbColName ="";
                if(currentCol == 0) {
                    dbColName ="virus_type";
                } else if(currentCol == 1) {
                    dbColName ="virus_name";
                }else if(currentCol == 2) {
                    dbColName ="pic";
                }else if(currentCol == 3) {
                    dbColName ="virus_num";
                }else if(currentCol == 4) {
                    dbColName ="virus_level";
                }else if(currentCol == 5) {
                    dbColName ="size";
                }else if(currentCol == 6) {
                    dbColName ="localtion";
                }else if(currentCol == 7) {
                    dbColName ="op_time";
                }else if(currentCol == 8) {
                    dbColName ="process_state";
                } else {
                    dbColName ="";
                }

                DataManager::GetInstance()->updateVirusItemValue(virNum,dbColName,newData);
            }
        }
    }
}

int VirusManagerWindow::countNonEmptyCells(QTableWidget *tableWidget) {
    int rowCount = tableWidget->rowCount();
    int columnCount = tableWidget->columnCount();
    int count = 0;

    for (int row = 0; row < rowCount; ++row) {
        for (int column = 0; column < columnCount; ++column) {
            if (tableWidget->item(row, column) != nullptr) {
                ++count;
            }
        }
    }

    return count;
}

void VirusManagerWindow::initComboboxData(){

    ui->comboBox->setFixedHeight(30);
    ui->comboBox_2->setFixedHeight(30);
    ui->comboBox_2->setFixedWidth(140);

    ui->comboBox_3->setFixedHeight(30);   
    ui->findVir->setFixedHeight(30);
    ui->pushButton_2->setFixedHeight(30);

    ui->lineEdit->setFixedWidth(130);
    ui->lineEdit->setFixedHeight(30);

    ui->tableWidget->setColumnWidth(2, 250);
    ui->tableWidget->setColumnWidth(2, 100);
    ui->tableWidget->setColumnWidth(5, 50);
    ui->tableWidget->setColumnWidth(7, 180);

    ui->comboBox->addItem("全部");
    ui->comboBox->addItem("裂缝");
    ui->comboBox->addItem("混泥土脱落");
    ui->comboBox->addItem("渗水");
    ui->comboBox->addItem("钢筋锈蚀");
    ui->comboBox->addItem("桥面铺装破损");
    ui->comboBox->addItem("桥面排水堵塞");
    ui->comboBox->addItem("伸缩缝损坏");

    ui->comboBox_2->addItem("全部");
    ui->comboBox_2->addItem("一级(细微)");
    ui->comboBox_2->addItem("二级(重点关注)");
    ui->comboBox_2->addItem("三级(急需处理)");

    ui->comboBox_3->addItem("全部");
    ui->comboBox_3->addItem("未处理");
    ui->comboBox_3->addItem("处理中");
    ui->comboBox_3->addItem("已完成");

    ui->lineEdit->setPlaceholderText("请输病害名称");
}

void VirusManagerWindow::on_findVir_clicked()
{
    int virusType = ui->comboBox->currentIndex();
    qDebug() << "m_virusType select Input Value: " << virusType;

    int virusLevel = ui->comboBox_2->currentIndex();
    qDebug() << "virusLevel select Input Value: " << virusLevel;

    int virusStatus = ui->comboBox_3->currentIndex();
    qDebug() << "virusLevel select Input Value: " << virusStatus;

    QString virusName = ui->lineEdit->text();
    qDebug() << "m_virusName Input Value: " << virusName;


    std::vector<Virus_Detail*> allV = DataManager::GetInstance()->queryVirByVirCondition(virusType,virusLevel,virusStatus,virusName);
    if(allV.empty()) {
        ui->tableWidget->setRowCount(0);
        return;
    }
    ui->tableWidget->setRowCount(0);

    int RowCont;
    for (auto element : allV) {
        RowCont=ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(RowCont);//增加一行

        ui->tableWidget->setItem(RowCont,0,new QTableWidgetItem(CCommFunc::getVirusType(element->virType)));
        ui->tableWidget->setItem(RowCont,1,new QTableWidgetItem(element->virName));
        ui->tableWidget->setItem(RowCont,2,new QTableWidgetItem(element->virPic));

        ui->tableWidget->setItem(RowCont,3,new QTableWidgetItem(element->virNum));
        ui->tableWidget->setItem(RowCont,4,new QTableWidgetItem(CCommFunc::getVirusLevel(element->virLevel)));
        ui->tableWidget->setItem(RowCont,5,new QTableWidgetItem(element->virSize));
        ui->tableWidget->setItem(RowCont,6,new QTableWidgetItem(element->virLocal));

        ui->tableWidget->setItem(RowCont,7,new QTableWidgetItem(convertQStringValue(element->virTime)));
        ui->tableWidget->setItem(RowCont,8,new QTableWidgetItem(CCommFunc::getVirusStatus(element->virStatus)));
        if (element != nullptr) {
            delete element;
            element = nullptr;
        }
     }

}

QString VirusManagerWindow::convertQStringValue(int timeValue) {
    QDateTime dateTime = QDateTime::fromSecsSinceEpoch(timeValue);
    QString formattedDateTime = dateTime.toString("yyyy/M/d hh:mm");
    return formattedDateTime;
}
