#include "recordthread.h"
#include <QTime>
#include <iostream>


RecordThread::RecordThread(QObject *parent) :
    QThread(parent)
{
    m_pParentWnd = new ShowFrame;     
    m_iDispWidth = 512;
    m_iDispHeight = 384;
    Recording = true;
    stoped = false;
    count = 500;
}

void RecordThread::run()
{
    QString strPath = "/home/hero/VID_" + QTime::currentTime().toString() + ".avi";
    int fps = 30;
    int sleepTime = 1. / (double)fps * 1000000;
    CvVideoWriter *writer = cvCreateVideoWriter(strPath.toStdString().c_str(), CV_FOURCC('X', 'V', 'I', 'D'), fps, cvSize(m_iDispWidth, m_iDispHeight));
    if(!writer){
        std::cout << "cannot create writer" << std::endl;
        Recording = false;
        return;
    }
    Recording = true;
    IplImage iplImg;
    while(!stoped){
            m_pParentWnd->mutex.tryLock(10);
            iplImg = IplImage(videoMat); 
            m_pParentWnd->mutex.unlock();
            qDebug()<<"write to file"<< count;
            cvWriteFrame(writer, &iplImg);
            usleep(sleepTime);
    }
    Recording = false;
    cvReleaseVideoWriter(&writer);
    qDebug()<<"thread stoped";
}

void RecordThread::stop()
{
    stoped = true;
    qDebug()<<"stop thread"<<Recording;
}

void RecordThread::QPixmapToIplImg(QImage &_src, IplImage &_dst)
{
    int    nChannels = 3;
    int    depth = IPL_DEPTH_8U;

    _dst.depth = depth;
    _dst.nChannels = nChannels;
    _dst.width = _src.width();
    _dst.height = _src.height();
    _dst.ID = 0;
    _dst.colorModel[0] = 'R';
    _dst.colorModel[1] = 'G';
    _dst.colorModel[2] = 'B';
    _dst.colorModel[3] = 0;
    _dst.channelSeq[0] = 'B';
    _dst.channelSeq[1] = 'G';
    _dst.channelSeq[2] = 'R';
    _dst.channelSeq[3] = 0;
    _dst.origin = 0;
    _dst.dataOrder = IPL_DATA_ORDER_PIXEL;
    _dst.align = 4;
    _dst.roi = NULL;
    _dst.maskROI = NULL;
    _dst.imageId = NULL;
    _dst.tileInfo = NULL;
    int size = _src.height()*_src.width() * 3 * sizeof(char);
    _dst.imageSize = size;
    _dst.widthStep = _src.width() * 3;
    _dst.BorderMode[0] = 0;
    _dst.BorderMode[1] = 0;
    _dst.BorderMode[2] = 0;
    _dst.BorderMode[3] = 0;

    _dst.BorderConst[0] = 0;
    _dst.BorderConst[1] = 0;
    _dst.BorderConst[2] = 0;
    _dst.BorderConst[3] = 0;

    memcpy(_dst.imageData, (unsigned char*)(_src.bits()), _src.width()*_src.height()*nChannels);
}


