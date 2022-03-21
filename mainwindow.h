#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include <QTimer>
#include <QTime>
#include <QMetaType>
#include <QSound>
#include <QString>
#include "WavHead.h"
#include "demodulation.h"
#include "udpconnect.h"
#include "CirQueue.h"
#include "waveform.h"
#include "mainwidget.h"
#include "wzserialport.h"
#include "PeakSearch.h"
#include "plot.h"
#include "recvdata.h" //new add

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);//explicit 抑制构造函数定义的隐式转换
    ~MainWindow();

    /**
     * @brief nativeEvent
     * @param eventType const的QByteArray对象
     * @param message void的指针
     * @param result long的指针
     * @return
     */
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);

    WavHead head;
    QSound *sound = NULL; //存放.wav声音文件
    QString wavPath[10];
    int wavFre;
    int& setSENDSIZE(int);


private slots:
    void on_SearchPeak_Button_clicked();

    void on_WatchPeak_Button_clicked();

    void ResearchPeak();

    void ErrorWarnings();

    void ConfirmPeakResult();

    void sendPeakPosData();

    void on_Demodu_Button_clicked();


    void on_DemoduStop_Button_clicked();

    void on_Play_Button_clicked();

    void on_save_checkBox_clicked();

    void on_Sound_Button_clicked();

    void on_Eazystart_Button_clicked();

    void showSendText(int sendsize);

    void showText(QString text);

    void textbrowserShowSpeed(double );



private:
    Ui::MainWindow *ui;
    HWND hWnd;
    shared_ptr<Config> cfg;
    shared_ptr<GetConfig> getcfg;
    WzSerialPort *serialport;
    PeakSearch *peak;

    Plot *plt = NULL; //画图
    MainWidget *wgt = NULL; //波形显示窗口

    shared_ptr<RecvData> RVD;

    Demodulation *Demodu = NULL;
    Demodulation *Demodu_2=NULL;
    Demodulation *Demodu_3=NULL;

    QTimer *SendPeakPosTimer = NULL;
    int sendPeakChannel;
    UDPConnect *UDP = NULL;
    QThread *UdpThread;
    QThread *UdpThread1;
    QTime SystemTime;

    WaveForm *waveWidget = NULL;

    bool is_peakExist = false;
    wchar_t* c2w(const char* str);
    bool MinWignoreDevice = false; //是否debug模式

    unsigned short saveCounter = 0;
    bool CaculationPhase; //是否解调
    inline void isShowWindow(Demodulation*);

    //new add
    int SENDSIZE;
    shared_ptr<CirQueue<float>> CHDataQue; //循环队列指针 用于存放原始通道的数据 数据类型为float
    shared_ptr<CirQueue<float>> demoduDataQue; //循环队列指针 用于存放解调后的数据 数据类型为float
    shared_ptr<CirQueue<float>> WaveDataQue; //循环队列指针 用于存放波形显示的数据 数据类型为float

    void debugDemudu();
    void debugDemudu(bool);
    bool setShow();


signals:
    void sendPeakPosDone();
    void stopSave(); //new add
};

#endif // MAINWINDOW_H
