#ifndef TE_THREAD_H
#define TE_THREAD_H

#include <QThread>
#include "mainwindow.h"
#include "i3system_TE.h"

using namespace i3;

class MainWindow;

class TE_Thread : public QThread
{
    Q_OBJECT
public:
    explicit TE_Thread(QObject *parent = 0);
    bool Initialize();
    void run();
    inline void StopStream(){m_bIsStopped = true;}
    int GetImageWidth(){return m_iImgWidth;}
    int GetImageHeight(){return m_iImgHeight;}
    bool ExitThread(){return m_bExitThread;}
    void SaveSetting(bool _bAlram, ushort _alarmTemp, bool _bAGC, bool _bHot, bool _bCold, bool _bAIE, ushort _AIERange, ushort _brightness, ushort _contrast, bool _center, ushort _colormap);
    void UpdateDead();
    void SetStd(float _in);
    void Reset();
    void ShutterCalib();
    
protected:
    bool        m_bIsStopped;
    MainWindow *pParentWnd;

private:
    TE_A* m_pTE;
    int m_iRecvNum;
    int m_iImgWidth, m_iImgHeight;
    bool m_bExitThread;
    bool m_bPause;

signals:
    void SignalShowImg(ushort *precvImage, float *_pTemp, float _centerTemp, ushort _width, ushort _height);
    
public slots:
    
};

#endif // TE_THREAD_H
