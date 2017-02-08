/*************************************************************************
    > File Name: showframe/network/network.cpp
    > Author: zxf
    > Mail: zhengxiaofeng333@163.com 
    > Created Time: 2017年02月06日 星期一 13时14分22秒
 ************************************************************************/

#include <iostream>
#include "network.h"
#include <unistd.h>
using namespace std;



NetworkThread::NetworkThread(QString ip, quint16 port): QThread()
{
    udpSocket = new QUdpSocket;
    udpSocket->bind(QHostAddress(ip), port);

    tcpSocket = new QTcpSocket;       
    tcpSocket->connectToHost(ip, port);
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(connectEstablished()));
}

void NetworkThread::connectEstablished()
{
    
}

void NetworkThread::run()
{
    while(1){

    }
}
