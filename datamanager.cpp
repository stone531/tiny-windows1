#include "datamanager.h"

#include <QCollator>
#include <QDateTime>

#include "DataBase/dbconn.h"
#include <QDebug>

DataManager * DataManager::m_pDataManager = nullptr;

DataManager::DataManager()
{

}

DataManager::~DataManager()
{
}


bool DataManager::dbInit()
{
    QList<QString> lstSql;
    lstSql.append("CREATE TABLE IF NOT EXISTS virus_info(id INTEGER DEFAULT 1 ,virus_type INTEGER, "
                  "virus_name TEXT DEFAULT '',pic TEXT DEFAULT '',virus_num INTEGER, virus_level INTEGER DEFAULT 0,"
                   "size TEXT ,localtion TEXT ,op_time INTEGER, process_state INTEGER, "
                  "options TEXT DEFAULT '')");
    Err_struct srt_err;
    DBHelper *dbhelper;
    Err_struct srtErr;

    qDebug() << "dbInit   ======craete table";
    DBConn dbconn;
    dbhelper = dbconn.getDBConn();
    if (nullptr == dbhelper ) return false;
    return dbhelper->execute_sql_tran(lstSql ,srt_err);
}



void DataManager::init()
{
    //initRadio();
}

qint64 DataManager::GetCurrentUnixTime()
{
    qint64 iTime = 0;
#if 0
    std::time_t rawtime = std::time(0);
    struct tm rawtm;
    // memset(&rawtime, 0, sizeof(tm));
    auto timeInfo = localtime_r(&rawtime, &rawtm);
    if (!timeInfo)
        return false;

    iTime = <ZINT64>(std::mktime(timeInfo));
#endif

    iTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
    return iTime;
}


void DataManager::addVirusInfo(int virType,QString virName,QString virPic,
                                 QString virNum,int virLevel,QString virSize,
                                 QString virLocal,int virTime,int virStatus)
{

    //qint64 time = GetCurrentUnixTime();

    QString preSql = QString("INSERT INTO virus_info(virus_type,virus_name,pic,virus_num,virus_level,size,localtion,op_time,process_state) VALUES(%1, '%2', '%3', %4, '%5', '%6', '%7', %8, %9)")
        .arg(virType).arg(virName).arg(virPic).arg(virNum).arg(virLevel).arg(virSize)
            .arg(virLocal).arg(virTime).arg(virStatus);

    Err_struct srt_err;

    DBHelper* dbhelper = nullptr;
    Err_struct srtErr;
    DBConn dbconn;
    dbhelper = dbconn.getDBConn();
    if (nullptr == dbhelper) return;
    dbhelper->execute_sql(preSql, srt_err);
    qDebug() <<"addVirusInfo insert data success:"<<preSql;
}

void DataManager::updateVirusItemValue(int id,QString key,QString newValue)
{
    if (key =="" || newValue == "" ) return;

    //if (getPPtIdFromRadioSession(sessionId) == pptId) return;

    QString preSql = QString("UPDATE virus_info SET %1 = '%2' WHERE virus_num= %3 ").arg(key).arg(newValue).arg(id);

    qDebug()<<preSql;
    Err_struct srt_err;

    DBHelper* dbhelper = nullptr;
    Err_struct srtErr;
    DBConn dbconn;
    dbhelper = dbconn.getDBConn();
    if (nullptr == dbhelper) return;
    dbhelper->execute_sql(preSql, srt_err);
}

void DataManager::delVirus(int virNum)
{
    QString preSql = QString("DELETE FROM virus_info WHERE virus_num = %1 ").arg(virNum);

    Err_struct srt_err;

    DBHelper* dbhelper = nullptr;
    Err_struct srtErr;
    DBConn dbconn;
    dbhelper = dbconn.getDBConn();
    if (nullptr == dbhelper) return;
    dbhelper->execute_sql(preSql, srt_err);

    qDebug() <<"delVirus del  success:"<<preSql;
}

void DataManager::clearRadioSession()
{
    QString preSql = QString("DELETE FROM radio_session ");

    Err_struct srt_err;

    DBHelper* dbhelper = nullptr;
    Err_struct srtErr;
    DBConn dbconn;
    dbhelper = dbconn.getDBConn();
    if (nullptr == dbhelper) return;
    dbhelper->execute_sql(preSql, srt_err);
}

std::vector<Virus_Detail*> DataManager::queryAllVir()
{
    QString preSql = QString("Select virus_type,virus_name,pic,virus_num,virus_level,size,localtion,op_time,process_state FROM virus_info ");
    QList<QSqlRecord> lstQueryRecord;
    Err_struct srt_err;

    qDebug() << preSql;
    DBHelper* dbhelper = nullptr;
    Err_struct srtErr;
    DBConn dbconn;
    std::vector<Virus_Detail*> virInfos;
    dbhelper = dbconn.getDBConn();
    if (nullptr == dbhelper) return virInfos;
    dbhelper->query(preSql, lstQueryRecord, srt_err);

    for (const auto &record: lstQueryRecord) {

        Virus_Detail *tmpObj= new Virus_Detail;
        tmpObj->virType = record.value("virus_type").toInt();
        tmpObj->virName = record.value("virus_name").toString();
        tmpObj->virPic = record.value("pic").toString();

        tmpObj->virNum = record.value("virus_num").toString();
        tmpObj->virLevel = record.value("virus_level").toInt();
        tmpObj->virSize = record.value("size").toString();
        tmpObj->virLocal = record.value("localtion").toString();
        tmpObj->virTime = record.value("op_time").toInt();
        tmpObj->virStatus = record.value("process_state").toInt();

        virInfos.push_back(tmpObj);
    }
    //qDebug() << "当前查询结果:" << result.c_str() << endl;

    return virInfos;
}

std::vector<Virus_Detail*> DataManager::queryVirByVirCondition(int virType,int virLevel,int virStatus,QString name) {
    if(virType == 0 &&virLevel ==0 &&virStatus ==0 &&name =="" ) {
        return queryAllVir();
    }
    bool hasCondition = false;

    QString preSql = QString("Select virus_type,virus_name,pic,virus_num,virus_level,size,localtion,op_time,process_state FROM virus_info where  ");
    if (virType != 0) {
        preSql += " virus_type = '" + QString::number(virType) + "' ";
        hasCondition = true;
    }
    if (virLevel != 0) {
        if (hasCondition) {
                preSql += " AND ";
        }
        preSql += " virus_level = '" + QString::number(virLevel) + "' ";
        hasCondition = true;
    }

    if (virStatus != 0) {
        if (hasCondition) {
            preSql += " AND ";
        }
        preSql += " process_state = '" + QString::number(virStatus) + "' ";
        hasCondition = true;
    }
    if (name != "") {
        if (hasCondition) {
            preSql += " AND ";
        }
        preSql += " virus_name = '" + name + "' ";
    }

    qDebug() << "条件查询:" << preSql << endl;

    QList<QSqlRecord> lstQueryRecord;
    Err_struct srt_err;

    qDebug() << preSql;
    DBHelper* dbhelper = nullptr;
    Err_struct srtErr;
    DBConn dbconn;
    std::vector<Virus_Detail*> virInfos;
    dbhelper = dbconn.getDBConn();
    if (nullptr == dbhelper) return virInfos;
    dbhelper->query(preSql, lstQueryRecord, srt_err);

    for (const auto &record: lstQueryRecord) {

        Virus_Detail *tmpObj= new Virus_Detail;
        tmpObj->virType = record.value("virus_type").toInt();
        tmpObj->virName = record.value("virus_name").toString();
        tmpObj->virPic = record.value("pic").toString();

        tmpObj->virNum = record.value("virus_num").toString();
        tmpObj->virLevel = record.value("virus_level").toInt();
        tmpObj->virSize = record.value("size").toString();
        tmpObj->virLocal = record.value("localtion").toString();
        tmpObj->virTime = record.value("op_time").toInt();
        tmpObj->virStatus = record.value("process_state").toInt();

        virInfos.push_back(tmpObj);
    }
    //qDebug() << "当前查询结果:" << result.c_str() << endl;

    return virInfos;
}
