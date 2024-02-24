#ifndef DATAMANAGER_H
#define DATAMANAGER_H
#include <QCoreApplication>

#include <QMutex>
#include <mutex>

class DataManager
{
public:
    static DataManager*GetInstance()
    {
        if (nullptr == m_pDataManager)
        {
            static QMutex myOSMutex;
            myOSMutex.lock();
            if (nullptr == m_pDataManager)
            {
                m_pDataManager = new DataManager;

                //m_pDataManager->initDbInst();
                m_pDataManager->dbInit();
                //m_pDataManager->dbInitEx();
                if (nullptr == m_pDataManager)
                {
                    myOSMutex.unlock();
                    return nullptr;
                }
            }
            myOSMutex.unlock();
        }

        return m_pDataManager;
    }

    void initDbInst()
    {
//        dbInst.srt_sqlite.szConnName = "diantai";
//        dbInst.srt_sqlite.szFileName = QCoreApplication::applicationDirPath() + "/" + "diantai.db";
//        sqliteHelper = SqliteHelper(dbInst);
    }


    bool dbInit();
    bool dbInitEx();
    void init();
    //static bool comparatorPhone(const PhoneDb *v1, const PhoneDb *v2);

    qint64 GetCurrentUnixTime();

    //radiosession
    void addRadioSession(int sessionId, int pptId, std::string client_req_type, std::string client_sip_host);
    void delRadioSession(int sessionId);
    void clearRadioSession();
    std::string queryAllRadioSession();
    void updateRadioSession(int sessionId,int pptId);
    int getPPtIdFromRadioSession(int sessionId);

    //calllog

private:
    DataManager();
    ~DataManager();
    //DB_Instance dbInst;
    static DataManager * m_pDataManager;

public:
    std::mutex m_mutex;
    std::mutex m_osDataBaseMutex;

public:
    int getDeleteDbByDay()
    {
        //QString strDelSpace = CSharedPreferencesUtils::GetInstance()->getStringValueForKey(ClientDefine::RECORD_DELETE_SPACE, QString::number(ClientDefine::RECORD_SPACE_DELETE_DEFAULT));
        //m_dwDeleteDbByDay = ServiceConfiguration::GetInstance()->record_delete_space();
        //m_dwDeleteDbByDay = strDelSpace.toInt();
        //LOGD << "getDeleteDbByDay:" << m_dwDeleteDbByDay;

        if (m_dwDeleteDbByDay > 60) m_dwDeleteDbByDay = 60;
        if (m_dwDeleteDbByDay < 1)  m_dwDeleteDbByDay = 1;
        return m_dwDeleteDbByDay;
    }

    QString getMaintenanceTime()
    {
        return m_strMaintenanceTime;
    }

private:
    int m_dwDeleteDbByDay;
    QString m_strMaintenanceTime;

};
#endif // DATAMANAGER_H
