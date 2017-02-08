/*************************************************************************
    > File Name: /home/hero/project/SurfaceIR/showframe/showframe.cpp
    > Author: zxf
    > Mail: zhengxiaofeng333@163.com 
    > Created Time: 2017年01月20日 星期五 17时30分07秒
 ************************************************************************/

#include <iostream>
#include <unistd.h>
using namespace std;

#include "showframe.h"

ShowFrame::ShowFrame(QWidget *parent) : QLabel(parent),
    isConnected(false), moving(false), isRecording(false),
    flash(false)
{

    setStyleSheet("QLabel{background-color:darkCyan}");

    confSocket = new QTcpSocket(this);
    dataSocket = new QUdpSocket(this);

    frameTimer = new QTimer;
    tipTimer = new QTimer;
    
    mainLayout = new QGridLayout;
    mainLayout->setContentsMargins(5, 0, 5, 0);
    mainLayout->setSpacing(10);
    //mainLayout->setSizeConstraint(QLayout::SetMaximumSize);
    setScaledContents(true);
    setMouseTracking(true);

    colorButton = new ToolButton;
    colorButton->setMaximumWidth(200);
    colorButton->setText(QString::fromUtf8("设置色彩"));

    sourceChangeButton = new ToolButton;
    sourceChangeButton->setMaximumWidth(200);
    sourceChangeButton->setText(QString::fromUtf8("切换视频源"));

    recordButton = new ToolButton;
    recordButton->setMaximumWidth(200);
    recordButton->setText(QString::fromUtf8("录像"));

    tempChangeButton = new  ToolButton;
    tempChangeButton->setMaximumWidth(200);
    tempChangeButton->setText(QString::fromUtf8("温度转换"));

    saveButton = new ToolButton;
    saveButton->setMaximumWidth(200);
    saveButton->setText(QString::fromUtf8("保存图片"));

    psbAdd = new ButtonAdd;
    
    mainLayout->addWidget(psbAdd, 0, 0, 5, 5, Qt::AlignCenter);
    mainLayout->addWidget(colorButton, 5, 0);
    mainLayout->addWidget(recordButton, 5, 1);
    mainLayout->addWidget(sourceChangeButton, 5, 2);
    mainLayout->addWidget(tempChangeButton, 5, 3);
    mainLayout->addWidget(saveButton, 5, 4);

    connect(frameTimer, SIGNAL(timeout()), this, SLOT(displayFrame()));
    connect(psbAdd, SIGNAL(clicked()), this, SLOT(on_psbAdd_clicked()));
    connect(confSocket, SIGNAL(readyRead()), this, SLOT(readDevConf()));
    connect(dataSocket, SIGNAL(readyRead()), this, SLOT(getImageFrame()));
    connect(colorButton, SIGNAL(clicked()), this, SLOT(on_colorButton_clicked()));
    connect(recordButton, SIGNAL(clicked()), this, SLOT(on_recordButton_clicked()));
    connect(tempChangeButton, SIGNAL(clicked()), this, SLOT(on_tempChangeButton_clicked()));
    connect(sourceChangeButton, SIGNAL(clicked()), this, SLOT(on_sourceChangeButton_clicked()));

    setFrameShape(QFrame::Panel);
    setLayout(mainLayout);
}

void ShowFrame::setID(const quint8 id)
{
    myID = id; 
}

void ShowFrame::initToolButton()
{

}

void ShowFrame::resizeEvent(QResizeEvent *e)
{

}

void ShowFrame::enterEvent(QEvent *e)
{
    if (isConnected){
        tipLabel = new QLabel;
        qDebug()<<"new QLabel";
        tipLabel->setWindowFlags(Qt::FramelessWindowHint); 
        connect(tipTimer, SIGNAL(timeout()), this, SLOT(delTipLabel()));
    }
}

void ShowFrame::leaveEvent(QEvent *e)
{

    if (isConnected){
        qDebug()<<"del QLabel";
        disconnect(tipTimer, SIGNAL(timeout()), this, SLOT(delTipLabel()));
        tipLabel->deleteLater();
    }
}

void ShowFrame::mouseMoveEvent(QMouseEvent *e)
{
    QWidget::mouseMoveEvent(e);
    if (isConnected){
        if (e->buttons() & Qt::LeftButton){
            endPoint = e->pos();
            moving = true;
            update();
        }
    }
}


void ShowFrame::mousePressEvent(QMouseEvent *e)
{
    QWidget::mousePressEvent(e);
    if (isConnected && e->button() == Qt::LeftButton){
        if (e->button() == Qt::LeftButton){
            startPoint = e->pos();
            qDebug()<<"press point"<<startPoint;
        }

    }
}

bool ShowFrame::event(QEvent *e)
{
    if (e->type() == QEvent::HoverEnter && isConnected && !moving)
    {
        
        int h = height();
        int w = width();

        int imgx = currentPoint.x() * mymat.cols / w;
        int imgy = currentPoint.y() * mymat.rows / h;

        quint8 b = mymat.at<cv::Vec3b>(imgx, imgy)[0];
        quint8 g = mymat.at<cv::Vec3b>(imgx, imgy)[1];
        quint8 r = mymat.at<cv::Vec3b>(imgx, imgy)[2];

        QHoverEvent *hoverEvent = static_cast<QHoverEvent*>(e);
        qDebug()<<"event point"<<hoverEvent->pos();
        tipLabel->move(mapToGlobal(hoverEvent->pos() += QPoint(15, 0) ));
        tipLabel->setText(QString("r:\t") + QString::number(r) + "\n" +QString("g:\t") + QString::number(g) + "\n" + QString("b:\t") + QString::number(b) );
        //模拟刷新显示
        tipLabel->hide();
        tipLabel->show();

    }
    return QLabel::event(e);
}

void ShowFrame::mouseReleaseEvent(QMouseEvent *e)
{
    QWidget::mouseReleaseEvent(e);
    if (isConnected){
        if (e->button() == Qt::LeftButton){
            if (moving){
                endPoint = e->pos();
                rectContainer.append(QRect(startPoint, endPoint));
                update();
            }
            currentPoint = e->pos();
            if (!moving)//画框时不显示对应点温度
                QCoreApplication::postEvent(this, new QHoverEvent(QEvent::HoverEnter, currentPoint, startPoint));
            if (tipTimer->isActive())//如果两次点击
                tipTimer->stop();
            tipTimer->start(2000);
            moving = false;
        }
    }
}

void ShowFrame::paintEvent(QPaintEvent *e)
{
    QLabel::paintEvent(e);
    if (isConnected){
        QPainter painter(this);
        QPen pen;
        pen.setWidth(2);
        pen.setColor(Qt::red);
        pen.setJoinStyle(Qt::RoundJoin);
        pen.setCapStyle(Qt::RoundCap);
        painter.setPen(pen);
        if (moving)
            painter.drawRect(QRect(startPoint, endPoint));
        foreach(QRect rect, rectContainer){
            painter.drawRect(rect);
        }
    }
}

void ShowFrame::mouseDoubleClickEvent(QMouseEvent *e)
{
    QWidget::mouseDoubleClickEvent(e);
    if (e->button() == Qt::RightButton){
        rectContainer.clear();
        startPoint = QPoint();//这个点必须清零，不然会有残留矩形
        endPoint = QPoint();//这个点必须清零，不然会有残留矩形
        update();
    }
    if (e->button() == Qt::LeftButton){
        if(isMaximized()){
            setWindowFlags(windowFlags() & (~Qt::Dialog));
           showNormal(); 
                m_bFullScr = false;
        } else {
            setWindowFlags(windowFlags() | Qt::Dialog);
            if(!isMaximized()){
                this->showMaximized();
                m_bFullScr = true;
            }
        }
        
    }

}

void ShowFrame::display(QImage &image)
{

}


void ShowFrame::on_psbAdd_clicked()
{
    ConfigWindow *cw = new ConfigWindow;
    connect(cw, SIGNAL(Conform(QString)), this, SLOT(setDeviceIP(const QString)));
    cw->exec();
    //if(!m_pThrd){
    //    m_pThrd = new TE_Thread(this);
    //    if(m_pThrd->Initialize()){
    //        connect(m_pThrd, SIGNAL(SignalShowImg(ushort*, float *, float, ushort, ushort)), this, SLOT(SlotImgShow(ushort*, float *, float, ushort, ushort)) );
    //        m_pThrd->start();
    //    }
    //    else{
    //        delete m_pThrd;
    //        m_pThrd = NULL;
    //        cout << "Thread not generated" << endl;
    //    }
    //}
}

void ShowFrame::setDeviceIP(const QString IP)
{
    isConnected = true;
    psbAdd->setHidden(true);
    deviceIP = IP;
    confSocket->connectToHost(QHostAddress(deviceIP), 8800);
    connect(confSocket, SIGNAL(connected()), this, SLOT(connectionEstablish()));
    dataSocket->bind(QHostAddress(deviceIP), 8801);
    QPixmap pixmap(width(), height());
#ifdef WIN32
    if (!pixmap.load(QString("d:/work/SurfaceIR/temp/%1.jpg").arg(myID)) )
#else
    if (!pixmap.load(QString("/home/hero/Pictures/%1.jpg").arg(myID)) )
#endif
        qDebug()<<"load failed";
    setPixmap(pixmap);
    mymat=cv::imread("/home/hero/Pictures/1.jpg");
    frameTimer->start(1000);
}

void ShowFrame::displayFrame()
{
    if (isConnected){
        if (isRecording){
            if(flash){
                setStyleSheet("QLabel{border: 2px solid red;}");
                flash = false;
            }
            else{
                setStyleSheet("QLabel{border: 2px solid white;}");
                flash = true; 
            }
        } else {
            if(flash){
                setStyleSheet("QLabel{border: 2px solid green;}");
                flash = false;
            }
            else{
                setStyleSheet("QLabel{border: 2px solid white;}");
                flash = true; 
            }
        }
    }
    //Mat matAIE(_height, _width, CV_8UC1);
    //Mat mat16(_height, _width, CV_16U, pRecvImage), mat8UC1, mat8ColorMap, matOut;
    //if(!m_bAGC)
    //    mat16.convertTo(mat8UC1, CV_8UC1, m_fContrast / 256.f, m_iBrightness);
    //else
    //    mat16.convertTo(mat8UC1, CV_8UC1, 1/256., 0.);

    ////Mat matAIE;
    //if(m_bAIE){
    //    AIE(mat8UC1, matAIE, (double)m_iAIERange / 100.0);
    //}
    //else{
    //    matAIE = mat8UC1.clone();
    //}

    //int nWidth, nHeight;
    //if(m_bFullScr){
    //    nHeight = m_pFullScr->geometry().height();
    //    nWidth = (int)(nHeight / 0.75 + 0.5);
    //}
    //else{
    //    nWidth = ui->Display->geometry().width(), nHeight = ui->Display->geometry().height();
    //}

    //// AIE -> Color -> resize
    //Mat mat8UC3(matAIE.size(), CV_8UC3);
    //Mat in[] = {matAIE, matAIE, matAIE};
    //merge(in, 3, mat8UC3);

    ////switch(m_iColorMap){
    ////    case I3ColorMap::BlackHot:{
    ////                                  LUT(mat8UC3, m_lutBlackHot, mat8ColorMap);
    ////                                  break;
    ////                              }
    ////    case I3ColorMap::Iron:{
    ////                              LUT(mat8UC3, m_lutIron, mat8ColorMap);
    ////                              break;
    ////                          }
    ////    case I3ColorMap::Purple:{
    ////                                LUT(mat8UC3, m_lutPurple, mat8ColorMap);
    ////                                break;
    ////                            }
    ////    case I3ColorMap::PurpleYellow:{
    ////                                      LUT(mat8UC3, m_lutPurpleYellow, mat8ColorMap);
    ////                                      break;
    ////                                  }
    ////    case I3ColorMap::Rainbow:{
    ////                                 LUT(mat8UC3, m_lutRainbow, mat8ColorMap);
    ////                                 break;
    ////                             }
    ////    case I3ColorMap::WhiteHot:{
    ////                                  mat8ColorMap = mat8UC3.clone();
    ////                                  break;
    ////                              }
    ////}

    //// Alarm
    ////Mat matAlarm(mat8ColorMap.size(), CV_8UC3);
    ////if(m_bAlarm){
    ////    SetAlarm(mat8ColorMap, &matAlarm, _pTemp, m_fAlarm);
    ////}
    ////else{
    ////    matAlarm = mat8ColorMap.clone();
    ////}

    //cv::resize(matAlarm, matOut, Size(nWidth, nHeight));

    //QPixmap image = cvMatToQPixmap(matOut);
    ////DrawInfo(&image, pRecvImage, _centerTemp, nWidth, nHeight);

    //// Display
    //if(m_bFullScr){
    //    m_pFullScr->setPixmap(image);
    //}
    //else{
    //    ui->Display->setPixmap(image);
    //}

    //delete pRecvImage;
    //if(_pTemp)
    //    delete _pTemp;
}

void ShowFrame::on_colorButton_clicked()
{

}

void ShowFrame::on_recordButton_clicked()
{
    isRecording = true;

}

void ShowFrame::on_sourceChangeButton_clicked()
{

}

void ShowFrame::on_tempChangeButton_clicked()
{

}

void ShowFrame::connectionEstablish()
{

}

void ShowFrame::delTipLabel()
{
    tipTimer->stop();
    tipLabel->hide();
}

//inline QPixmap ShowFrame::cvMatToQPixmap( const cv::Mat &inMat )
//{
//    return QPixmap::fromImage( cvMatToQImage( inMat ) );
//}
//
//inline QImage  ShowFrame::cvMatToQImage( const cv::Mat &inMat )
//{
//    switch ( inMat.type() )
//    {
//        // 8-bit, 4 channel
//        case CV_8UC4:
//            {
//                QImage image( inMat.data,
//                        inMat.cols, inMat.rows,
//                        static_cast<int>(inMat.step),
//                        QImage::Format_ARGB32 );
//
//                return image;
//            }
//
//            // 8-bit, 3 channel
//        case CV_8UC3:
//            {
//                QImage image( inMat.data,
//                        inMat.cols, inMat.rows,
//                        static_cast<int>(inMat.step),
//                        QImage::Format_RGB888 );
//
//                return image.rgbSwapped();
//            }
//
//            // 8-bit, 1 channel
//        case CV_8UC1:
//            {
//                static QVector<QRgb>  sColorTable( 256 );
//
//                // only create our color table the first time
//                if ( sColorTable.isEmpty() )
//                {
//                    for ( int i = 0; i < 256; ++i )
//                    {
//                        sColorTable[i] = qRgb( i, i, i );
//                    }
//                }
//
//                QImage image( inMat.data,
//                        inMat.cols, inMat.rows,
//                        static_cast<int>(inMat.step),
//                        QImage::Format_Indexed8 );
//
//                image.setColorTable( sColorTable );
//
//                return image;
//            }
//
//        default:
//            qWarning() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
//            break;
//    }
//
//    return QImage();
//}
