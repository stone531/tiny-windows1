#ifndef MYSQLHELPER_H
#define MYSQLHELPER_H
#include <QSqlRecord>
#include "dbhelper.h"
class MysqlHelper:public DBHelper
{
public:
    MysqlHelper();
    MysqlHelper(DB_Instance dbinst);
    ~MysqlHelper();
    //QSqlDatabase db_curr;
    QSqlDatabase open_db(QString szConnName,QString szDatabasename,QString szHostName,QString szUserName,QString szPassword);//打开数据库连接，参数：数据库连接名、连接数据库路径、主机名、用户名、密码
    QSqlDatabase open_db(DB_Instance db,Err_struct &srt_err);//打开数据库连接，参数：数据库参数信息结构体、错误信息
    void close_db(QString szConnName);//关闭数据库连接，参数：数据库连接名
    bool query(QString szSql,QList<QSqlRecord> &lstQueryRecord,Err_struct &srt_err);//数据库查询，参数：sql语句、记录集、错误信息
    int execute_sql(QString szSql,Err_struct &srt_err);//执行sql语句，参数：sql语句、错误信息，返回：影响行数
    bool execute_sql_tran(QList<QString> lstSql,Err_struct &srt_err);//执行多条sql语句，实现数据库事务，参数：多条sql语句、错误信息
    bool execute_sql_tran(QString szSql,QList<HS> lstHsParams,Err_struct &srt_err);//执行多条sql语句，实现数据库事务，参数：sql语句,多条sql语句参数的哈希表，类似C#中的hashtable
    int get_rows_num(QString szSql,Err_struct &srt_err);//执行sql语句，获得记录集行数，参数：sql语句、错误信息，返回：记录行数
    QVariant get_max(QString szSql,Err_struct &srt_err);//获得最大值，参数：sql语句、错误信息，返回：最大值
    QVariant get_min(QString szSql,Err_struct &srt_err);//获得最小值，参数：sql语句、错误信息，返回：最小值
    QList<QString> get_connects(Err_struct &srt_err);
private:
    DB_Instance dbInstance;
};
#endif // MYSQLHELPER_H
