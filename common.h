#ifndef COMMON_H
#define COMMON_H
#include "QDebug"
#include <QString>

enum VIRUS_TYPE {
    VIRUS_TYPE_ALL,
    VIRUS_TYPE_FISSURE,//裂缝
    VIRUS_TYPE_CONCRETE_SHEDDING,//混泥土脱落
    VIRUS_TYPE_WATER_SEEPAGE,//渗水
    VIRUS_TYPE_CORROSION_OF_REINFORCEMENT,//钢筋锈蚀
    VIRUS_TYPE_BRIDGE_DECK_PAVEMENT_IS_BROKEN,//桥面铺装破损
    VIRUS_TYPE_BRIDGE_FLOOR_DRAINAGE_BLOCKED,//桥面排水堵塞
    VIRUS_TYPE_EXPANSION_JOINT_FAILURE,//伸缩缝损坏
};

//病害级别
enum VIRUS_LEVEL {
    VIRUS_LEVEL_ALL,
    VIRUS_LEVEL_FIRST,//裂缝
    VIRUS_LEVEL_SECOND,//混泥土脱落
    VIRUS_LEVEL_THIRD,//渗水

};




/*
 *  ui->comboBox_3->addItem("请选择处理状态");
    ui->comboBox_3->addItem("未处理");
    ui->comboBox_3->addItem("处理中");
    ui->comboBox_3->addItem("已完成");
 */
//病害级别
enum VIRUS_STATUS {
    VIRUS_STATUS_ALL,
    VIRUS_STATUS_UNTREATED,
    VIRUS_STATUS_IN_PROCESS,
    VIRUS_STATUS_COMPLETE,

};

struct Virus_Detail
{
    //Virus_Detail() {}
    int     virType;
    QString virName;
    QString virPic;
    QString virNum;
    int     virLevel;
    QString virSize;
    QString virLocal;
    int     virTime;
    int     virStatus;
};


class CCommFunc {
private:
    CCommFunc();
    ~CCommFunc();
public:
    static QString  getVirusType(int type) {

        QString  typeName= "";
        VIRUS_TYPE vt = (VIRUS_TYPE)type;
        switch (vt) {
                case VIRUS_TYPE_FISSURE:
                    typeName= "裂缝";
                    break;
                case VIRUS_TYPE_CONCRETE_SHEDDING:
                    typeName= "混泥土脱落";
                    break;
                case VIRUS_TYPE_WATER_SEEPAGE:
                    typeName= "渗水";
                    break;
                case VIRUS_TYPE_CORROSION_OF_REINFORCEMENT:
                    typeName= "渗水";
                    break;
                case VIRUS_TYPE_BRIDGE_DECK_PAVEMENT_IS_BROKEN:
                    typeName= "钢筋锈蚀";
                    break;
                case VIRUS_TYPE_BRIDGE_FLOOR_DRAINAGE_BLOCKED:
                    typeName= "桥面铺装破损";
                    break;
                case VIRUS_TYPE_EXPANSION_JOINT_FAILURE:
                    typeName= "伸缩缝损坏";
                    break;
                default:
                    typeName= "裂缝";
                    break;
            }
        return typeName;
    };
    static QString  getVirusLevel(int type) {

        QString  typeLevelName= "";
        VIRUS_LEVEL vt = (VIRUS_LEVEL)type;
        switch (vt) {
                case VIRUS_LEVEL_FIRST:
                    typeLevelName= "一级";
                    break;
                case VIRUS_LEVEL_SECOND:
                    typeLevelName= "二级";
                    break;
                case VIRUS_LEVEL_THIRD:
                    typeLevelName= "三级";
                    break;
                default:
                    typeLevelName= "一级";
                    break;
            }
        return typeLevelName;
    };
    static QString  getVirusStatus(int type) {

        QString  typeLevelName= "";
        VIRUS_STATUS vt = (VIRUS_STATUS)type;
        switch (vt) {
                case VIRUS_STATUS_UNTREATED:
                    typeLevelName= "未处理";
                    break;
                case VIRUS_STATUS_IN_PROCESS:
                    typeLevelName= "处理中";
                    break;
                case VIRUS_STATUS_COMPLETE:
                    typeLevelName= "已完成";
                    break;
                default:
                    typeLevelName= "未处理";
                    break;
            }
        return typeLevelName;
    };
};


#endif // COMMON_H
