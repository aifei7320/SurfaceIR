#include "te_thread.h"
#include <QtCore>
#include <unistd.h>
#include <iostream>

TE_Thread::TE_Thread(QObject *parent) :
    QThread(parent)
{
    m_bIsStopped = true;
    m_bExitThread = true;
    m_bPause = false;
    m_iRecvNum = 0;
    //pParentWnd = (MainWindow *)parent;
    m_pTE = NULL;
}

bool TE_Thread::Initialize()
{
    // Scan connected TE.
    SCANINFO *pScan = new SCANINFO[MAX_USB_NUM];
    ScanTE(pScan);
    int hnd_dev = -1;
    for(int i = 0; i < MAX_USB_NUM; i++){
        if(pScan[i].bDevCon){
            hnd_dev = i;
            break;
        }
    }
    delete pScan;
    if(hnd_dev == -1){
        std::cout << "Device not connected" << std::endl;
        return false;
    }

    m_pTE = OpenTE_A(hnd_dev);
    if(!m_pTE){
        std::cout << "Open Failed" << std::endl;
        return false;
    }
    else{
        m_iImgWidth = m_pTE->GetImageWidth(), m_iImgHeight = m_pTE->GetImageHeight();
        TE_SETTING setting;
        m_pTE->GetSetting(&setting);
        //pParentWnd->SetSetting(setting);
        return true;
    }
}

void TE_Thread::run(){
    m_bExitThread = false;
    m_bIsStopped = false;
    int imgSize = m_iImgWidth * m_iImgHeight;
    while(!m_bIsStopped){
        while(m_bPause){
            usleep(10000);
        }
        ushort *pusImgData = new unsigned short[m_iImgWidth * m_iImgHeight];
        int res = m_pTE->RecvImage(pusImgData, true);
        if(res == 1){
            // Center Temp
            ushort usTemp = pusImgData[m_iImgWidth / 2 * m_iImgHeight / 2];
            float fTemp = ((float)(usTemp - 5000)) / 100.f;

            // Entire Temp
            float *pTemp = NULL;
            //if(pParentWnd->isAlarmOn()){
            //    pTemp = new float[imgSize];
            //    ushort *pusTemp = new ushort[imgSize];
            //    m_pTE->CalcTemp(pusTemp);
            //    for(int i=0; i<imgSize; i++){
            //        pTemp[i] = ((float)(pusTemp[i] - 5000)) / 100.f;
            //    }
            //    delete pusTemp;
            //}

            emit SignalShowImg(pusImgData, pTemp, fTemp, m_iImgWidth, m_iImgHeight);
            usleep(10000);
        }
    }
    m_pTE->CloseTE();
    m_pTE = NULL;
    m_bExitThread = true;
}

void TE_Thread::SaveSetting(bool _bAlarm, ushort _alarmTemp, bool _bAGC, bool _bHot, bool _bCold, bool _bAIE, ushort _AIERange, ushort _brightness, ushort _contrast, bool _center, ushort _colormap)
{
    if(m_pTE){
        m_bPause = true;
        i3::TE_SETTING setting;
        setting.AGC = _bAGC;
        setting.AIE = _bAIE;
        setting.alarm = _bAlarm;
        setting.alarmTemp = _alarmTemp;
        setting.traceHot = _bHot;
        setting.traceCold = _bCold;
        setting.AIE_Factor = _AIERange;
        setting.brightness = _brightness;
        setting.contrast = _contrast;
        setting.center = _center;
        setting.colorMap = _colormap;
        bool res = m_pTE->SaveSetting(&setting);
        m_bPause = false;
        if(!res)
            std::cout << "send fail" << std::endl;
    }
}

void TE_Thread::UpdateDead()
{
    if(m_pTE){
        m_bPause = true;
        usleep(100000);
        m_pTE->UpdateDead();
        m_bPause = false;
    }
}

void TE_Thread::SetStd(float _in)
{
     if(m_pTE){
         m_pTE->SetStd(_in);
     }
}

void TE_Thread::Reset()
{
    if(m_pTE){
        m_pTE->ResetMainBoard();
    }
}

void TE_Thread::ShutterCalib()
{
    if(m_pTE){
        if(!m_pTE->ShutterCalibrationOn()){
            usleep(1);
        }
    }
}
