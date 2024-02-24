#ifndef DBHELPER_H
#define DBHELPER_H
#define HS QHash<QString,QVariant>
#include <QString>
#include <QSqlDatabase>
#include <QVariant>
#include <QHash>
#include <QList>
#include <QStringList>

//错误代码（枚举）
enum DBErrorCode
{
    db_normal=0,
    open_error=-1,
    close_error=-2,
    query_error=-3,
    execute_error=-4,
    db_busy=-5
};
//sqlite数据库参数信息
typedef struct
{
    QString szConnName;
    QString szFileName;
    QString szPassword;
}Sqlite_struct;
//mysql数据库参数信息
typedef struct
{
    QString szConnName;
    QString szHostName;
    QString szUserName;
    QString szPassword;
    QString szDatabaseName;
}Mysql_struct;
//错误信息
typedef struct
{
    DBErrorCode ErrCode;
    QString ErrMsg;
}Err_struct;
//通用数据库参数信息结构体
typedef struct
{
    Mysql_struct srt_mysql;
    Sqlite_struct srt_sqlite;
}DB_Instance;

class DBHelper
{
public:
    DBHelper() {};
    ~DBHelper() {};
    virtual QSqlDatabase open_db(DB_Instance db,Err_struct &srt_err)=0;
    virtual void close_db(QString szConnName)=0;
    virtual bool query(QString szSql,QList<QSqlRecord> &lstQueryRecord,Err_struct &srt_err)=0;
    virtual int execute_sql(QString szSql,Err_struct &srt_err)=0;
    virtual  bool execute_sql_tran(QList<QString> lstSql,Err_struct &srt_err)=0;
    virtual   bool execute_sql_tran(QString szSql,QList<HS> lstHsParams,Err_struct &srt_err)=0;//注意此处QHash必须指明<>里面的类型，如果没有，就会提示'QHash' is not a type
    virtual int get_rows_num(QString szSql,Err_struct &srt_err)=0;
    virtual QVariant get_max(QString szSql,Err_struct &srt_err)=0;
    virtual QVariant get_min(QString szSql,Err_struct &srt_err)=0;
    virtual QList<QString> get_connects(Err_struct &srt_err)=0;
};

#endif // DBHELPER_H

