/*****SQL接口层******/
#include "DataBase/sqlitehelper.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>
#include <QList>
#include <QSqlQueryModel>
#include <QDebug>
//#define MULTIPROCESS
#ifdef MULTIPROCESS
#include "tcpsocketclient.h"
#endif

QString RomateIP="127.0.0.1";
//QString RomateIP="192.168.1.31";
SqliteHelper::SqliteHelper()
{
}

SqliteHelper::SqliteHelper(DB_Instance dbInst)
{
   dbInstance=dbInst;
}

SqliteHelper::~SqliteHelper()
{
}
//打开数据库连接，参数：数据库连接名、连接数据库路径
QSqlDatabase SqliteHelper::open_db(QString szConnName,QString szFileName)
{
    QSqlDatabase db_curr;
    db_curr=QSqlDatabase::addDatabase("QSQLITE", szConnName);
    db_curr.setDatabaseName(szFileName);
    bool bSuccess=db_curr.open();
    if(!bSuccess)
    {
        return QSqlDatabase();
    }
    return db_curr;
}
//打开数据库连接，参数：数据库参数信息结构体、错误信息
QSqlDatabase SqliteHelper::open_db(DB_Instance db,Err_struct &srt_err)
{
    QSqlDatabase db_curr;
    srt_err.ErrCode=db_normal;
    srt_err.ErrMsg="";
    Sqlite_struct dbinfo=db.srt_sqlite;
    if(!QSqlDatabase::contains(dbinfo.szConnName))
    {
        db_curr=QSqlDatabase::addDatabase("QSQLITE", dbinfo.szConnName);
    }
    else
    {
        db_curr=QSqlDatabase::database(dbinfo.szConnName,true);
    }
    db_curr.setDatabaseName(dbinfo.szFileName);
    bool bSuccess=db_curr.open();
    if(!bSuccess)
    {
        srt_err.ErrCode=open_error;
        srt_err.ErrMsg=db_curr.lastError().text();
        return QSqlDatabase();
    }

    qDebug() << "ErrCode:" << srt_err.ErrCode << " ErrMsg:" << srt_err.ErrMsg;
    return db_curr;
}
//关闭数据库连接，参数：数据库连接名
void SqliteHelper::close_db(QString szConnName)
{
    QSqlDatabase::removeDatabase(szConnName);
}
//数据库查询，参数：sql语句、记录集、错误信息
bool SqliteHelper::query(QString szSql,QList<QSqlRecord> &lstQueryRecord,Err_struct &srt_err)
{
#ifdef MULTIPROCESS
    TcpSocketClient tsc(RomateIP,1234);
    if(tsc.sendData(3)!=1)
    {
        srt_err.ErrCode=db_busy;
        srt_err.ErrMsg="sqlite busy";
        return false;
    }
#endif
    bool bSuccess=false;
    srt_err.ErrCode=db_normal;
    srt_err.ErrMsg="";
   try
    {
        QSqlDatabase db_curr=open_db(dbInstance,srt_err);
        if(srt_err.ErrCode!=db_normal)
        {
#ifdef MULTIPROCESS
    if(tsc.sendData(4)!=1)
    {
        srt_err.ErrCode=db_busy;
        srt_err.ErrMsg="sqlite busy";
        return false;
    }
#endif
            return bSuccess;
        }
        QSqlQuery query(db_curr);
        query.prepare(szSql);//分行写的时候注意空格不能少
        query.setForwardOnly(true);
        if(!query.exec())
        {
            srt_err.ErrCode=query_error;
            srt_err.ErrMsg=query.lastError().text();
            bSuccess=false;
        }
        else
        {
            QList<QSqlRecord> lstquery;
            while(query.next())
            {
                lstquery.append(query.record());
            }
            lstQueryRecord=lstquery;
            bSuccess=true;
        }
       query.clear();
       query.finish();
       db_curr.close();
       qDebug() << "db_curr close.";
    }
    catch(QString exception)
    {
        qDebug() << "query exception:" << exception;
        throw "Throw Error:"+exception;
    }
    close_db(dbInstance.srt_sqlite.szConnName);
#ifdef MULTIPROCESS
    if(tsc.sendData(4)!=1)
    {
        srt_err.ErrCode=db_busy;
        srt_err.ErrMsg="sqlite busy";
        return false;
    }
#endif
    qDebug() << "ErrCode:" << srt_err.ErrCode << " ErrMsg:" << srt_err.ErrMsg;
    return bSuccess;
}
//执行sql语句，参数：sql语句、错误信息，返回：影响行数
int SqliteHelper::execute_sql(QString szSql,Err_struct &srt_err)
{
    int nResult=-1;

#ifdef MULTIPROCESS
    TcpSocketClient tsc(RomateIP,1234);
    if(tsc.sendData(1)!=1)
    {
        srt_err.ErrCode=db_busy;
        srt_err.ErrMsg="sqlite busy";
        return nResult;
    }
#endif

    srt_err.ErrCode=db_normal;
    srt_err.ErrMsg="";
    try
    {
        QSqlDatabase db_curr=open_db(dbInstance,srt_err);
        if(srt_err.ErrCode!=db_normal)
        {
#ifdef MULTIPROCESS
    if(tsc.sendData(2)!=1)
    {
        srt_err.ErrCode=db_busy;
        srt_err.ErrMsg="sqlite busy";
        return nResult;
    }
#endif
            return nResult;
        }
        QSqlQuery query(db_curr);
        query.prepare(szSql);
        if(!query.exec())
        {
            srt_err.ErrCode=execute_error;
            srt_err.ErrMsg=query.lastError().text();
            nResult=-1;
        }
        else
        {
            nResult=query.numRowsAffected ();
        }
    }
    catch(QString exception)
    {
         throw "Throw Error:"+exception;
    }
    close_db(dbInstance.srt_sqlite.szConnName);
#ifdef MULTIPROCESS
    if(tsc.sendData(2)!=1)
    {
        srt_err.ErrCode=db_busy;
        srt_err.ErrMsg="sqlite busy";
        return -1;
    }
#endif

   qDebug() << "ErrCode:" << srt_err.ErrCode << " ErrMsg:" << srt_err.ErrMsg;
    return nResult;
}
//执行多条sql语句，实现数据库事务，参数：多条sql语句、错误信息
bool SqliteHelper::execute_sql_tran(QList<QString> lstSql,Err_struct &srt_err)
{
#ifdef MULTIPROCESS
    TcpSocketClient tsc(RomateIP,1234);
    if(tsc.sendData(1)!=1)
    {
        srt_err.ErrCode=db_busy;
        srt_err.ErrMsg="sqlite busy";
        return false;
    }
#endif
    bool bSuccess=false;
    srt_err.ErrCode=db_normal;
    srt_err.ErrMsg="";
    try
    {
        QSqlDatabase db_curr=open_db(dbInstance,srt_err);
        if(srt_err.ErrCode!=db_normal)
        {
#ifdef MULTIPROCESS
    if(tsc.sendData(2)!=1)
    {
        srt_err.ErrCode=db_busy;
        srt_err.ErrMsg="sqlite busy";
        return false;
    }
#endif
            qDebug() << "db not normal.";
            return bSuccess;
        }
        bSuccess=true;
        QSqlQuery query(db_curr);
        db_curr.transaction();
        for(int i=0;i<lstSql.count();i++)
        {
            qDebug() << "lstSql:" <<  lstSql[i];
            query.prepare(lstSql[i]);
            if(!query.exec())
            {
                srt_err.ErrCode=execute_error;
                srt_err.ErrMsg=query.lastError().text();
                bSuccess=false;
                break;
            }
        }
        if(bSuccess)
        {
            bSuccess=db_curr.commit();
        }
    }
    catch(QString exception)
    {
         throw "Throw Error:"+exception;
    }
    close_db(dbInstance.srt_sqlite.szConnName);
#ifdef MULTIPROCESS
    if(tsc.sendData(2)!=1)
    {
        srt_err.ErrCode=db_busy;
        srt_err.ErrMsg="sqlite busy";
        return false;
    }
#endif

    qDebug() << "ErrCode:" << srt_err.ErrCode << " ErrMsg:" << srt_err.ErrMsg;
    return bSuccess;
}

//执行多条sql语句，实现数据库事务，参数：sql语句,多条sql语句参数的哈希表，类似C#中的hashtable
 bool SqliteHelper::execute_sql_tran(QString szSql,QList<HS> lstHsParams,Err_struct &srt_err)
{
#ifdef MULTIPROCESS
    TcpSocketClient tsc(RomateIP,1234);
    if(tsc.sendData(1)!=1)
    {
        srt_err.ErrCode=db_busy;
        srt_err.ErrMsg="sqlite busy";
        return false;
    }
#endif
     bool bSuccess=false;
     srt_err.ErrCode=db_normal;
     srt_err.ErrMsg="";
     try
     {
         QSqlDatabase db_curr=open_db(dbInstance,srt_err);
         if(srt_err.ErrCode!=db_normal)
         {
#ifdef MULTIPROCESS
    if(tsc.sendData(2)!=1)
    {
        srt_err.ErrCode=db_busy;
        srt_err.ErrMsg="sqlite busy";
        return false;
    }
#endif
             return bSuccess;
         }
         bSuccess=true;
         QSqlQuery query(db_curr);
         db_curr.transaction();
         for(int i=0;i<lstHsParams.count();i++)
         {
             query.prepare(szSql);
             for(int j=0;j<lstHsParams[i].count();j++)
             {
                 query.bindValue(lstHsParams[i].keys()[j],lstHsParams[i].value(lstHsParams[i].keys()[j]));
             }
             if(!query.exec())
             {
                 srt_err.ErrCode=execute_error;
                 srt_err.ErrMsg=query.lastError().text();
                 bSuccess= false;
             }
         }
         if(bSuccess)
         {
             bSuccess=db_curr.commit();
         }
     }
     catch(QString exception)
     {
          throw "Throw Error:"+exception;
     }
     close_db(dbInstance.srt_sqlite.szConnName);
#ifdef MULTIPROCESS
    if(tsc.sendData(2)!=1)
    {
        srt_err.ErrCode=db_busy;
        srt_err.ErrMsg="sqlite busy";
        return false;
    }
#endif
     qDebug() << "ErrCode:" << srt_err.ErrCode << " ErrMsg:" << srt_err.ErrMsg;
     return bSuccess;
 }

//执行sql语句，获得记录集行数，参数：sql语句、错误信息，返回：记录行数
int SqliteHelper::get_rows_num(QString szSql,Err_struct &srt_err)
{
    int nResult=-1;
    srt_err.ErrCode=db_normal;
    srt_err.ErrMsg="";
    try
    {
        QSqlDatabase db_curr=open_db(dbInstance,srt_err);
        if(srt_err.ErrCode!=db_normal)
        {
            return nResult;
        }

        QSqlQuery query(db_curr);
        query.prepare(szSql);
        if(!query.exec())
        {
            srt_err.ErrCode=query_error;
            srt_err.ErrMsg=query.lastError().text();
            nResult= -1;
        }
        else
        {
//            if (query.isSelect())
//            {
//               nResult = query.size();
//               LOGD << "isSelect return true, nResult:" << nResult;
//            }
//            else
//            {
//               nResult = query.numRowsAffected();
//                LOGD << "isSelect return false, nResult:" << nResult;
//            }

//            if (-1 == nResult)
//            {
//                LOGD << "start query rownum.";
//                nResult = 0;
//                while(query.next())
//                {
//                    nResult++;
//                }

//                LOGD << "end query rownum===>" <<  nResult;
//            }

            qDebug() << "start query rownum.";
            QSqlQueryModel model ;
            model.setQuery(query);
            while (model.canFetchMore())
            {

                model.fetchMore();
            }

            int nRecordCount = model.rowCount();
            int nColumnCount = model.columnCount();
            qDebug() << "end query rownum===>" <<  nRecordCount << " nColumnCount:" << nColumnCount;
            nResult = nRecordCount;
        }
    }
    catch(QString exception)
    {
         throw "Throw Error:"+exception;
    }
    close_db(dbInstance.srt_sqlite.szConnName);
    //return nResult;

    return (nResult == -1) ? 0 : nResult;
}
//获得最大值，参数：sql语句(max)、错误信息，返回：最大值
QVariant SqliteHelper::get_max(QString szSql,Err_struct &srt_err)
{
    QVariant qv;
    srt_err.ErrCode=db_normal;
    srt_err.ErrMsg="";
   try
    {
        QSqlDatabase db_curr=open_db(dbInstance,srt_err);
        if(srt_err.ErrCode!=db_normal)
        {
            return QVariant();//QVariant支持空值的使用，用.isNull() == true
        }
        QSqlQuery query(db_curr);
        query.prepare(szSql);
        if(!query.exec())
        {
            srt_err.ErrCode=query_error;
            srt_err.ErrMsg=query.lastError().text();
            qv= QVariant();//QVariant支持空值的使用，用.isNull() == true
        }
        else
        {
            query.first();
            qv= query.value(0);
        }
    }
    catch(QString exception)
    {
         throw "Throw Error:"+exception;
    }
    close_db(dbInstance.srt_sqlite.szConnName);
    return qv;
}
//获得最小值，参数：sql语句(min)、错误信息，返回：最小值
QVariant SqliteHelper::get_min(QString szSql,Err_struct &srt_err)
{
    QVariant qv;
    srt_err.ErrCode=db_normal;
    srt_err.ErrMsg="";
   try
    {
        QSqlDatabase db_curr=open_db(dbInstance,srt_err);
        if(srt_err.ErrCode!=db_normal)
        {
            return QVariant();//QVariant支持空值的使用，用.isNull() == true
        }
        QSqlQuery query(db_curr);
        query.prepare(szSql);
        if(!query.exec())
        {
            srt_err.ErrCode=query_error;
            srt_err.ErrMsg=query.lastError().text();
            qv= QVariant();
        }
        else
        {
            query.first();
            qv= query.value(0);
        }
    }
    catch(QString exception)
    {
         throw "Throw Error:"+exception;
    }
    close_db(dbInstance.srt_sqlite.szConnName);
    return qv;
}

QList<QString> SqliteHelper::get_connects(Err_struct &srt_err)
{
    DB_Instance dbInst;
    dbInst=dbInstance;
    dbInst.srt_sqlite.szConnName="sqlite_test2013";
    QSqlDatabase db_curr=open_db(dbInst,srt_err);
    if(srt_err.ErrCode!=db_normal)
    {
        return QStringList();
    }
    return db_curr.connectionNames();
}
