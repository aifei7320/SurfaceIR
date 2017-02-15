#ifndef _RECORDTHREAD_H_
#define _RECORDTHREAD_H_

#include <QThread>
#include "../showframe.h"
#include <QPixmap>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class ShowFrame;

class RecordThread : public QThread
{
    Q_OBJECT
public:
    explicit RecordThread(QObject *parent = 0);
    void run();
    volatile bool Recording;
    QImage m_imgRecord;
    Mat videoMat;
    void stop();

private:
    ShowFrame *m_pParentWnd;
    int m_iDispWidth, m_iDispHeight;
    int count;
    volatile bool stoped;
    void QPixmapToIplImg(QImage &_src, IplImage &_dst);
};

#endif // RECORDTHREAD_H
