#pragma once
#define DB_TYPE   "sqlite"
#include <QString>
#include <QMutex>
#include "dbhelper.h"
#include "sqlitehelper.h"
#include "mysqlhelper.h"

class DBConn
{
public:
    DBConn();
    DBConn(QString dbType);
    DBHelper *getDBConn();
    DBHelper *getDBConnEx();
    SqliteHelper sqlitehelper;
    MysqlHelper mysqlhelper;

private:
    QString szDbType;
    static qint64  m_dwConnectCount;
    static QMutex  m_oMutex;
    static qint64  m_dwRecordConnectCount;
    static QMutex  m_oRecordMutex;
};


