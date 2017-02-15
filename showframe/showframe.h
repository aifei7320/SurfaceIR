/*************************************************************************
    > File Name: /home/hero/project/SurfaceIR/showframe/showframe.h
    > Author: zxf
    > Mail: zhengxiaofeng333@163.com 
    > Created Time: 2017年01月20日 星期五 17时29分59秒
 ************************************************************************/

#include <iostream>
#include <unistd.h>
using namespace std;

#ifndef _SHOWFRAME_H_
#define _SHOWFRAME_H_

#include <QMap>
#include "cv.hpp"
#include <QMutex>
#include <QTimer>
#include <QImage>
#include <QFrame>
#include <QLabel>
#include <QDebug>
#include <QPoint>
#include <QImage>
#include <QPixmap>
#include <QWidget>
#include <QVector>
#include <QPalette>
#include "opencv.hpp"
#include "highgui.h"
#include <QTcpSocket>
#include <QTcpServer>
#include <QUdpSocket>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPaintEvent>
#include <QHoverEvent>
#include <QResizeEvent>
#include <QHostAddress>
#include <QCoreApplication>
#include "network/network.h"
#include <QVariantAnimation>
#include "i3system_imgproc.h"
#include <QPropertyAnimation>
#include "tethread/colormap.h"
#include "tethread/te_thread.h"
#include "buttonadd/buttonadd.h"
#include "camconfig/camconfig.h"
#include "toolbutton/toolbutton.h"
#include <QGraphicsColorizeEffect>
#include "opencv2/imgproc/imgproc.hpp"
#include "recordthread/recordthread.h"
#include "connectionconfigwindow/connectionconfigwindow.h"

#include "i3system_TE.h"

class RecordThread;


class ShowFrame :  public QLabel
{
    Q_OBJECT
public:
    ShowFrame(QWidget *parent=0);
    ~ShowFrame();
    void setID(const quint8 id);
protected:
    bool event(QEvent *e);
    void enterEvent(QEvent * e);
    void leaveEvent(QEvent * e);
    void paintEvent(QPaintEvent *e);
    void resizeEvent(QResizeEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *e);

    //NetworkThread *networkThread;
    ButtonAdd *psbAdd; //添加设备按钮


private:
    void initToolButton();
    QPixmap cvMatToQPixmap( const cv::Mat &inMat );
    QImage  cvMatToQImage( const cv::Mat &inMat );

public:
    QMutex mutex;

private:
    QHBoxLayout *toolBtnLayout;
    QGridLayout *mainLayout;//主布局

    bool isConnected;//能够接收到图像数据后，才能使能画框功能
    bool moving;//只有在左键按下，并移动了，才能开始画矩形
    bool isRecording;//正在录像，更改Frame颜色。
    bool flash;//边框闪烁

    quint8 myID;//上层界面指定本模块的编号，以便识别自己是几号

    QPoint startPoint;//矩形框起始点
    QPoint endPoint;//矩形框终止点
    QPoint currentPoint;//旋停

    QVector<QRect> rectContainer;//矩形
    QString deviceIP;//设备ip地址
    QColor frameColor;//暂时没用
    QTimer *frameTimer;//定义边框闪烁
    QTimer *tipTimer;//提示显示时间定时器

    CamConfig *cc;//相机设置窗口

    RecordThread *recordThread;

    ToolButton *recordButton;//录像按钮
    ToolButton *colorButton;//相机设置按钮
    ToolButton *sourceChangeButton;//切换相机
    ToolButton *tempChangeButton;//切换温度制式
    ToolButton *saveButton;//拍照
    ToolButton *playAndStopButton;//开始和停止显示

    QLabel *tipLabel;//tip
    qreal currentPointTemperature;//记录当前鼠标点击处温度
    bool showTipLabel;//是否显示tip提示
    quint16 *tempImage;//红外相机的原始数据是short型
    TE_Thread *m_pThrd;//红外相机现成

    QTcpServer *dataServer;
    QUdpSocket *confSocket;
    QTcpSocket *dataSocket;
    
    bool m_bFullScr;//是否全屏

    cv::Mat mymat;

    bool m_bAGC, m_bAIE;
    bool m_bAlarm;
    float m_fAlarm;
    int m_iColorMap;
    
    float m_fContrast;
    int m_iBrightness;
    float m_fAIERange;
    bool isplaying;
    enum{
        WhiteHot = 0,
        BlackHot,
        Iron,
        BlueRed,
        Medical,
        Purple,
        PurpleYellow,
        DarkBlue,
        Cyan,
        Rainbow,
        Autumn,
        Bone,
        Jet,
        Winter,
        Ocean,
        Summer,
        Spring,
        Cool,
        HSV,
        Hot,
    };

private slots:
    void on_recordButton_clicked();
    void on_colorButton_clicked();
    void on_sourceChangeButton_clicked();
    void on_tempChangeButton_clicked();
    void display(QImage &image);//更新图像数据
    void on_playAndStopButton_clicked();//开始和停止
    void on_psbAdd_clicked();//添加设备按钮
    void setDeviceIP(const QString);
    void connectionEstablish();
    void connectionStoped();
    void displayFrame();
    void delTipLabel();
    void getImageFrame();
    void colorMapChange(const int index, int brightness, float contrast, float aie);
    void showImage(ushort *pRecvImage, float *_pTemp, float _centerTemp, ushort _width, ushort _height);
};

#endif
