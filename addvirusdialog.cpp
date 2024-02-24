#include "addvirusdialog.h"
#include "ui_addvirusdialog.h"
#include "qdebug.h"
#include "common.h"
#include <QLayout>
#include <QMessageBox>

addVirusDialog::addVirusDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addVirusDialog)
{
    ui->setupUi(this);

    setWindowTitle("添加病毒-管理窗口");

    setFixedSize(500, 700);

    //设置初始值
    initData();
}

addVirusDialog::~addVirusDialog()
{
    delete ui;
}

void addVirusDialog::initData() {
    addVirusType();
    ui->lineEdit->setText("请输入病毒名称");
    ui->lineEdit_2->setText("请输入图片地址，支持多个图片地址中间以';'分开");
    ui->lineEdit_3->setText("请输入病毒编码");
    //ui->lineEdit_4->setText("请选择病毒级别");
    ui->lineEdit_4->setText("请输入尺寸");
    ui->lineEdit_5->setText("请输入位置");
    //ui->lineEdit_6->setText("请选择时间");
    addVirusLevel();
    addVirusStatus();
}
void addVirusDialog::addVirusType() {

    ui->comboBox->addItem("请选择病毒类型");
    ui->comboBox->addItem("裂缝");
    ui->comboBox->addItem("混泥土脱落");
    ui->comboBox->addItem("渗水");
    ui->comboBox->addItem("钢筋锈蚀");
    ui->comboBox->addItem("桥面铺装破损");
    ui->comboBox->addItem("桥面排水堵塞");
    ui->comboBox->addItem("伸缩缝损坏");
}

void addVirusDialog::addVirusLevel() {

    ui->comboBox_2->addItem("请选择病害级别");
    ui->comboBox_2->addItem("一级(细微)");
    ui->comboBox_2->addItem("二级(重点关注)");
    ui->comboBox_2->addItem("三级(急需处理)");
}

void addVirusDialog::addVirusStatus() {

    ui->comboBox_3->addItem("请选择处理状态");
    ui->comboBox_3->addItem("未处理");
    ui->comboBox_3->addItem("处理中");
    ui->comboBox_3->addItem("已完成");
}

void addVirusDialog::on_pushButton_2_clicked()
{
    //QMessageBox messageBox;
    //病毒类型
    m_virusType = ui->comboBox->currentIndex();
    qDebug() << "m_virusType select Input Value: " << m_virusType;
    if(m_virusType == 0) {
        QMessageBox::information(this, "添加", "请选择正确的病毒类型", QMessageBox::Ok);
        return;
    }

    //病毒名称
    m_virusName = ui->lineEdit->text();
    qDebug() << "m_virusName Input Value: " << m_virusName;
    if(m_virusName.compare("请输入病毒名称") ==0) {
        QMessageBox::information(this, "添加","请选择正确的病毒名称",  QMessageBox::Ok);
        return;
    }

    //图片地址
    m_virusPic = ui->lineEdit_2->text();;
    qDebug() << "m_virusPic Input Value: " << m_virusPic;
    if(m_virusPic.compare("请输入图片地址") ==0) {
        QMessageBox::information(this,"添加", "请选择正确的图片地址",  QMessageBox::Ok);
        return;
    }
    //图片编码
    m_virusNum = ui->lineEdit_3->text();
    qDebug() << "m_virusNum Input Value: " << m_virusNum;
    if(m_virusNum.compare("请输入病毒编码") ==0) {
        QMessageBox::information(this, "添加","请选择正确的图片编码",  QMessageBox::Ok);
        return;
    }

    //病害级别
    m_virusLevel = ui->comboBox_2->currentIndex();
    qDebug() << "m_virusLevel select Input Value: " << m_virusLevel;
    if(m_virusLevel == 0) {
        QMessageBox::information(this, "添加","请选择正确的病毒级别", QMessageBox::Ok);
        return;
    }

    //尺寸
    m_virusSize = ui->lineEdit_4->text();
    qDebug() << "m_virusSize Input Value: " << m_virusSize;

    //图片位置
    m_virusLocal = ui->lineEdit_5->text();
    qDebug() << "m_virusLocal Input Value: " << m_virusLocal;

    //检测时间


    //处理状态
    m_virusStatus = ui->comboBox_3->currentIndex();
    qDebug() << "m_virusStatus Input Value: " << m_virusStatus;
    if(m_virusStatus == 0) {

        QMessageBox::information(this, "添加","请选择正确的状态", QMessageBox::Ok);
        return;
    }
}

void addVirusDialog::on_pushButton_clicked()
{
    close();
}