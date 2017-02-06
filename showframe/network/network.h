/*************************************************************************
    > File Name: /home/hero/project/SurfaceIR/network/network.h
    > Author: zxf
    > Mail: zhengxiaofeng333@163.com 
    > Created Time: 2017年01月20日 星期五 17时29分19秒
 ************************************************************************/

#include <iostream>
#include <unistd.h>
using namespace std;

#ifndef _NETWORK_H_
#define _NETWORK_H_

#include <QThread>
#include <QTcpSocket>
#include <QDataStream>

class Network :  public QThread
{
    Q_OBJECT
public:
    Network(QString remoteIP, quint16 port);

private:
    QTcpSocket *socket;
};

#endif
