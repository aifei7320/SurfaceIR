/*************************************************************************
    > File Name: /home/hero/project/SurfaceIR/showframe/camconfig/camconfig.cpp
    > Author: zxf
    > Mail: zhengxiaofeng333@163.com 
    > Created Time: 2017年02月10日 星期五 09时56分43秒
 ************************************************************************/

#include <iostream>
#include <unistd.h>
#include "camconfig.h"
using namespace std;

CamConfig::CamConfig(QWidget *parent) : QTabWidget(parent)
{

    setAutoFillBackground(true);
    ircam = new IRCamConfig(this);
    ircam->setObjectName("ircamconfig");

    norcam = new NormalCamConfig(this);
    norcam->setObjectName("normalcamconfig");

    addTab(ircam, "红外相机设置");
    addTab(norcam, "普通相机设置");

    setStyleSheet("QWidget#ircamconfig{background-color:darkcyan}"
                    "QWidget#normalcamconfig{background-color:darkcyan }");

    connect(ircam, SIGNAL(configChanged(const int, const int, const float, const float)), this, SIGNAL(irConfigChanged(const int, 
                    const int, const float, const float)));
    setCurrentIndex(0);
}

CamConfig::~CamConfig()
{
    cout<<"cam config destructor"<<endl;
    delete ircam;
    delete norcam;
}
