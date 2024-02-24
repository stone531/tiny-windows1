#include "dbconn.h"
#include <QCoreApplication>
#include <QDebug>

//#include "login/logindelegate.h"

qint64  DBConn::m_dwConnectCount = 1;
qint64  DBConn::m_dwRecordConnectCount = 1;
QMutex  DBConn::m_oMutex;
QMutex  DBConn::m_oRecordMutex;
DBConn::DBConn()
{
}

DBConn::DBConn(QString dbType)
{
    szDbType = dbType;
}

DBHelper *DBConn::getDBConn()
{
    DB_Instance dbInst;
    if (QString::compare(DB_TYPE, "sqlite")==0)
    {
       if (m_dwConnectCount >= INT_MAX) m_dwConnectCount = 0;
       dbInst.srt_sqlite.szConnName = QString("tiny-windows");
        dbInst.srt_sqlite.szFileName = QCoreApplication::applicationDirPath() + "/" + "tiny-windows.db";
        sqlitehelper = SqliteHelper(dbInst);
        return &sqlitehelper;
    }
    else
    {
        return &sqlitehelper;
    }
}

DBHelper *DBConn::getDBConnEx()
{

    return nullptr;
}

