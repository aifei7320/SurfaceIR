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
#include "connectionconfigwindow/connectionconfigwindow.h"

#include "i3system_TE.h"


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
    QString deviceIP;
    QColor frameColor;
    QTimer *frameTimer;//定义边框闪烁
    QTimer *tipTimer;

    CamConfig *cc;

    ToolButton *recordButton;
    ToolButton *colorButton;
    ToolButton *sourceChangeButton;
    ToolButton *tempChangeButton;
    ToolButton *saveButton;
    ToolButton *playAndStopButton;

    QLabel *tipLabel;//tip
    qreal currentPointTemperature;
    bool showTipLabel;
    quint16 *tempImage;
    TE_Thread *m_pThrd;

    QTcpServer *dataServer;
    QUdpSocket *confSocket;
    QTcpSocket *dataSocket;
    
    bool m_bFullScr;

    cv::Mat mymat;

    bool m_bAGC, m_bAIE;
    bool m_bAlarm;
    float m_fAlarm;
    int m_iColorMap;
    
    float m_fContrast;
    int m_iBrightness;
    ushort m_iAIERange;
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
    void on_playAndStopButton_clicked();
    void on_psbAdd_clicked();//添加设备按钮
    void setDeviceIP(const QString);
    void connectionEstablish();
    void connectionStoped();
    void displayFrame();
    void delTipLabel();
    void getImageFrame();
    void colorMapChange(const int index);
    void showImage(ushort *pRecvImage, float *_pTemp, float _centerTemp, ushort _width, ushort _height);
};

#endif
