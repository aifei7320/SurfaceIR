/*************************************************************************
    > File Name: showframe/camconfig/camconfig.h
    > Author: zxf
    > Mail: zhengxiaofeng333@163.com 
    > Created Time: 2017年02月10日 星期五 09时55分17秒
 ************************************************************************/

#ifndef _CAMCONFIG_H_
#define _CAMCONFIG_H_

#include <QTabWidget>
#include <QObject>
#include "ircamconfig/ircamconfig.h"
#include "normalcamconfig/normalcamconfig.h"

class CamConfig : public QTabWidget
{
public:
    explicit CamConfig(QWidget *parent=0);
    ~CamConfig();
private:
    IRCamConfig *ircam;
    NormalCamConfig *norcam;
};

#endif 
