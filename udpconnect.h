
#ifndef UDPCONNECT_H
#define UDPCONNECT_H
#include <iostream>
#include <string>
#include <algorithm>
#include <QUdpSocket>
#include <QHostAddress>
#include "Config.h"
#include <queue>
#include <QQueue>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QBarSet>
#include <QBarSeries>
#include "CirQueue.h"
#include <QMetaType>
#include "waveform.h"
#include <QDateTime>
#include <QTime>
#include <QTimer>
#include <memory>

using namespace QtCharts;
using namespace std;

#define SEND_ORIGNAL_DATA               ((char)0x01)
#define SEND_NOT_UNWRAP_PHASE_DATA      ((char)0x02)
#define SEND_FILTED_PHASE_DATA          ((char)0x03)
#define SEND_UNFILT_PHASE_DATA          ((char)0x04)
#define SEND_PHASE_DATA                 ((char)0x05)

class UDPConnect :public QObject
{
    Q_OBJECT
public:
    UDPConnect() = default;
    UDPConnect(const Config *cfig, int& sendsize);
    UDPConnect(shared_ptr<GetConfig> gcfg, shared_ptr<CirQueue<float>> saveque);
    ~UDPConnect();
    long getHasSend(){
        return hasSend;
    }

    QHostAddress AddressIP; //IP地址
    QUdpSocket *socket = NULL;
    int port;//端口号
    int PeakNum;//峰值数
    int frequency;//采样率

    void changeFileNameOnce(QDateTime &systemDate, QTime &systemTime);//初次生成存储文件名
    int sendData(CirQueue<float>* que,char dataType); //下位机发送数据（上位机接收数据）
    void loadSeriesData(char dataType); //加载波形数据
    void initSeriesParam(QLineSeries *line1, QLineSeries *line2, QLineSeries *line3);//初始化波形图

    void saveData2Bin(float* data, bool &now); //存储到本地.bin文件
    void saveData2Bin(float *data); //弃用
    //int& setSENDSIZE(int &sendsize);

    QLineSeries *m_lineSeries_1;
    QLineSeries *m_lineSeries_2;
    QLineSeries *m_lineSeries_3;

    int selectFBG_1;
    int selectFBG_2;
    int selectFBG_3;

    float *QueData = NULL;
    //QByteArray *data = NULL;


    QVector<QPointF> points;

    char Head[8] = {(char)0xF1,(char)0xF2,(char)0xF3,(char)0xF4};

    long hasSend; //已发送数据数

    string saveFolder; //存储目录(文件夹)
    QString savePath;//弃用

    bool isSave; //是否存储数据
    bool isSend; //是否发送数据

    size_t waveLength; //显示波形的长度

    char DataType;

    QString *path;
    FILE **pFile=NULL;

    QTimer saveTimer;

    QTime systemTime;
    QDateTime systemDate;

    bool is_saveData = false;


private:
    shared_ptr<GetConfig> UDPgcfg;
    shared_ptr<CirQueue<float>> saveDataQue;
    QMutex writeLock;
    QString saveFilename1;
    QString saveFilename2;
    QString saveFilename3;
    QString *saveFilename;
    ofstream outfile1;
    ofstream outfile2;
    ofstream outfile3;
    shared_ptr<vector<ofstream>> outfile;
    int SENDSIZE;
    int filesize;
    bool hasNextFilename;
    unsigned long onceSaveNum;
    unsigned long saveNum;
    QTimer* udpTimer;


    void saveOriData(const unsigned long & num); //存储三通道数据
    void saveDemoduData(const unsigned long& num); //存储解调数据

public slots:
    void executeSendData(CirQueue<float>* que, char Type);//执行发送数据的slot
    void changeSelectFBG(int FBG1,int FBG2, int FBG3);//选FBG的序号

    void changeFileName();//改变文件名(发下一个文件时)
    void getFilename(); //产生下一个文件的文件名
    void executeData(); //弃用
    void stopSaveSlot();//停止保存
    void checkSaveSlot();//定时器触发存储队列数据

signals:
    void sendNextFile(); //发下一个文件的signal
};

#endif // UDPCONNECT_H
