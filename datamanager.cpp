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
    //lstSql.append("CREATE TABLE IF NOT EXISTS radio_action(id INTEGER PRIMARY KEY AUTOINCREMENT, begin_time INTEGER, end_time INTEGER, radio_name TEXT, radio_action TEXT, radio_rate TEXT, radio_account TEXT, radio_record_name TEXT, radio_upload TEXT '0')");
    //lstSql.append("CREATE TABLE IF NOT EXISTS radio(id INTEGER PRIMARY KEY AUTOINCREMENT, is_listener INT DEFAULT 0, location INT DEFAULT 0, recv_send_same INT DEFAULT 0, couple_state INT DEFAULT 0, name TEXT DEFAULT '', rate TEXT DEFAULT '', recv_account TEXT DEFAULT '', recv_ip TEXT DEFAULT '', recv_port TEXT DEFAULT '', send_account TEXT DEFAULT '', send_ip TEXT DEFAULT '', send_port TEXT DEFAULT '')");
    lstSql.append("CREATE TABLE IF NOT EXISTS virus_info(id INTEGER DEFAULT 1 ,virus_type INTEGER, "
                  "virus_name TEXT DEFAULT '',pic TEXT DEFAULT '',virus_num INTEGER PRIMARY KEY, virus_level INTEGER DEFAULT 0,"
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


void DataManager::addRadioSession(int sessionId,int pptId,std::string client_req_type,std::string client_sip_host)
{

    qint64 time = GetCurrentUnixTime();

    QString preSql = QString("INSERT INTO radio_session(client_sip_host, session_id, ppt_id, client_req_type, op_time, opt) VALUES('%1', %2, %3, '%4', %5, '%6')")
        .arg(client_sip_host.c_str()).arg(sessionId).arg(pptId).arg(client_req_type.c_str()).arg(time).arg("");

    Err_struct srt_err;

    DBHelper* dbhelper = nullptr;
    Err_struct srtErr;
    DBConn dbconn;
    dbhelper = dbconn.getDBConn();
    if (nullptr == dbhelper) return;
    dbhelper->execute_sql(preSql, srt_err);
}

void DataManager::updateRadioSession(int sessionId,int pptId)
{
    if (sessionId <= 0 || pptId <=0 ) return;

    //if (getPPtIdFromRadioSession(sessionId) == pptId) return;

    QString preSql = QString("UPDATE radio_session SET ppt_id = %1 WHERE session_id = %2 ").arg(pptId).arg(sessionId);

    Err_struct srt_err;

    DBHelper* dbhelper = nullptr;
    Err_struct srtErr;
    DBConn dbconn;
    dbhelper = dbconn.getDBConn();
    if (nullptr == dbhelper) return;
    dbhelper->execute_sql(preSql, srt_err);
}

void DataManager::delRadioSession(int sessionId)
{
    QString preSql = QString("DELETE FROM radio_session WHERE session_id = %1 ").arg(sessionId);

    Err_struct srt_err;

    DBHelper* dbhelper = nullptr;
    Err_struct srtErr;
    DBConn dbconn;
    dbhelper = dbconn.getDBConn();
    if (nullptr == dbhelper) return;
    dbhelper->execute_sql(preSql, srt_err);
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

std::string DataManager::queryAllRadioSession()
{
    QString preSql = QString("Select ppt_id,client_sip_host,client_req_type FROM radio_session ");
    QList<QSqlRecord> lstQueryRecord;
    Err_struct srt_err;

    qDebug() << preSql;
    DBHelper* dbhelper = nullptr;
    Err_struct srtErr;
    DBConn dbconn;
    dbhelper = dbconn.getDBConn();
    if (nullptr == dbhelper) return nullptr;
    dbhelper->query(preSql, lstQueryRecord, srt_err);

    std::string result = "\nfid:000.000\n";

    for (const auto &record: lstQueryRecord) {
        result += record.value("ppt_id").toString().toStdString() + ","
            + record.value("client_sip_host").toString().toStdString() + ","
            + record.value("client_req_type").toString().toStdString() + "\n";
    }
    qDebug() << "当前查询结果:" << result.c_str() << endl;

    return result;
}

int DataManager::getPPtIdFromRadioSession(int sessionId)
{
    if (sessionId <= 0) return -1;

    QString preSql = QString("Select ppt_id FROM radio_session WHERE session_id = %1 ").arg(sessionId);

    Err_struct srt_err;

    qDebug() << preSql;
    DBHelper* dbhelper = nullptr;
    Err_struct srtErr;
    DBConn dbconn;
    dbhelper = dbconn.getDBConn();
    if (nullptr == dbhelper) return -2;

    QList<QSqlRecord> lstQueryRecord;
    dbhelper->query(preSql, lstQueryRecord, srt_err);

    if (lstQueryRecord.size() > 0)
    {
        return lstQueryRecord[0].value("ppt_id").toInt();
    }

    return -3;
}
