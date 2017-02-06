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
        } else {
            setWindowFlags(windowFlags() | Qt::Dialog);
            if(!isMaximized()){
                this->showMaximized();
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
}

void ShowFrame::setDeviceIP(const QString IP)
{
    isConnected = true;
    psbAdd->setHidden(true);
    deviceIP = IP;
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

void ShowFrame::delTipLabel()
{
    tipTimer->stop();
    tipLabel->hide();
}
