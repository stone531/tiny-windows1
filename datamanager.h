#ifndef DATAMANAGER_H
#define DATAMANAGER_H
#include <QCoreApplication>

#include <QMutex>
#include <mutex>
#include <vector>
#include <common.h>

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
    void addVirusInfo(int virType,QString virName,QString virPic,
                      QString virNum,int virLevel,QString virSize,
                      QString virLocal,int virTime,int virStatus);
    void delVirus(int sessionId);
    void clearRadioSession();
    std::vector<Virus_Detail*> queryAllVir();
    void updateRadioSession(int sessionId,int pptId);
    //int getPPtIdFromRadioSession(int sessionId);
    std::vector<Virus_Detail*> queryVirByName(QString name);
    std::vector<Virus_Detail*> queryVirByVirStatus(int virStatus);
    std::vector<Virus_Detail*> queryVirByVirLevel(int virLevel);
    std::vector<Virus_Detail*> queryVirByVirType(int virType);
    std::vector<Virus_Detail*> queryVirByVirCondition(int virType,int virLevel,int virStatus,QString name);
;
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
