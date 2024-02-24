#include "DataBase/mysqlhelper.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>
#include <QList>
MysqlHelper::MysqlHelper()
{
}
MysqlHelper::MysqlHelper(DB_Instance dbInst)
{
      dbInstance=dbInst;
}
MysqlHelper::~MysqlHelper()
{
}

//打开数据库连接，参数：数据库连接名、连接数据库路径 、主机名、用户名、密码
QSqlDatabase MysqlHelper::open_db(QString szConnName,QString szDatabasename,QString szHostName,QString szUserName,QString szPassword)
{
    QSqlDatabase db_curr;
    db_curr=QSqlDatabase::addDatabase("QMYSQL", szConnName);
    db_curr.setDatabaseName(szDatabasename);
    db_curr.setHostName(szHostName);
    db_curr.setUserName(szUserName);
    db_curr.setPassword(szPassword);
    bool bSuccess=db_curr.open();
    if(!bSuccess)
    {
        return QSqlDatabase();
    }
    return db_curr;
}
//打开数据库连接，参数：数据库参数信息结构体、错误信息
QSqlDatabase MysqlHelper::open_db(DB_Instance db,Err_struct &srt_err)
{
    QSqlDatabase db_curr;
    srt_err.ErrCode=db_normal;
    srt_err.ErrMsg="";
    Mysql_struct dbinfo=db.srt_mysql;
    if(!QSqlDatabase::contains(dbinfo.szConnName))
    {
        db_curr=QSqlDatabase::addDatabase("QMYSQL", dbinfo.szConnName);
    }
    else
    {
        db_curr=QSqlDatabase::database(dbinfo.szConnName,true);
    }
    db_curr.setDatabaseName(dbinfo.szDatabaseName);
    db_curr.setHostName(dbinfo.szHostName);
    db_curr.setUserName(dbinfo.szUserName);
    db_curr.setPassword(dbinfo.szPassword);
    bool bSuccess=db_curr.open();
    if(!bSuccess)
    {
        srt_err.ErrCode=open_error;
        srt_err.ErrMsg=db_curr.lastError().text();
        return QSqlDatabase();
    }
    return db_curr;
}
//关闭数据库连接，参数：数据库连接名
void MysqlHelper::close_db(QString szConnName)
{
    QSqlDatabase::removeDatabase(szConnName);
}
//数据库查询，参数：sql语句、记录集、错误信息
bool MysqlHelper::query(QString szSql,QList<QSqlRecord> &lstQueryRecord,Err_struct &srt_err)
{
    bool bSuccess=false;
    srt_err.ErrCode=db_normal;
    srt_err.ErrMsg="";
   try
    {
        QSqlDatabase db_curr=open_db(dbInstance,srt_err);
        if(srt_err.ErrCode!=db_normal)
        {
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
        db_curr.close();
    }
    catch(QString exception)
    {
         throw "Throw Error:"+exception;
    }
    close_db(dbInstance.srt_mysql.szConnName);
    return bSuccess;
}
//执行sql语句，参数：sql语句、错误信息，返回：影响行数
int MysqlHelper::execute_sql(QString szSql,Err_struct &srt_err)
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
    close_db(dbInstance.srt_mysql.szConnName);
    return nResult;
}
//执行多条sql语句，实现数据库事务，参数：多条sql语句、错误信息
bool MysqlHelper::execute_sql_tran(QList<QString> lstSql,Err_struct &srt_err)
{
    bool bSuccess=false;
    srt_err.ErrCode=db_normal;
    srt_err.ErrMsg="";
    try
    {
        QSqlDatabase db_curr=open_db(dbInstance,srt_err);
        if(srt_err.ErrCode!=db_normal)
        {
            return bSuccess;
        }
        bSuccess=true;
        QSqlQuery query(db_curr);
        db_curr.transaction();
        for(int i=0;i<lstSql.count();i++)
        {
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
    close_db(dbInstance.srt_mysql.szConnName);
    return bSuccess;
}

//执行多条sql语句，实现数据库事务，参数：sql语句,多条sql语句参数的哈希表，类似C#中的hashtable
 bool MysqlHelper::execute_sql_tran(QString szSql,QList<HS> lstHsParams,Err_struct &srt_err)
{
     bool bSuccess=false;
     srt_err.ErrCode=db_normal;
     srt_err.ErrMsg="";
     try
     {
         QSqlDatabase db_curr=open_db(dbInstance,srt_err);
         if(srt_err.ErrCode!=db_normal)
         {
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
     close_db(dbInstance.srt_mysql.szConnName);
     return bSuccess;
 }

//执行sql语句，获得记录集行数，参数：sql语句、错误信息，返回：记录行数
int MysqlHelper::get_rows_num(QString szSql,Err_struct &srt_err)
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
            //nResult= query.size();//sqlite数据库不支持size()
            nResult=0;
            while(query.next())
            {
                nResult++;
            }
        }
    }
    catch(QString exception)
    {
         throw "Throw Error:"+exception;
    }
    close_db(dbInstance.srt_mysql.szConnName);
    return nResult;
}
//获得最大值，参数：sql语句(max)、错误信息，返回：最大值
QVariant MysqlHelper::get_max(QString szSql,Err_struct &srt_err)
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
    close_db(dbInstance.srt_mysql.szConnName);
    return qv;
}
//获得最小值，参数：sql语句(min)、错误信息，返回：最小值
QVariant MysqlHelper::get_min(QString szSql,Err_struct &srt_err)
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
    close_db(dbInstance.srt_mysql.szConnName);
    return qv;
}

QList<QString> MysqlHelper::get_connects(Err_struct &srt_err)
{
    DB_Instance dbInst;
    dbInst=dbInstance;
    dbInst.srt_mysql.szConnName="mysql_test2013";
    QSqlDatabase db_curr=open_db(dbInst,srt_err);
    if(srt_err.ErrCode!=db_normal)
    {
        return QStringList();
    }
    return db_curr.connectionNames();
}
