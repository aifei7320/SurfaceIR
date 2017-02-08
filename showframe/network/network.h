/*************************************************************************
    > File Name: /home/hero/project/SurfaceIR/network/network.h
    > Author: zxf
    > Mail: zhengxiaofeng333@163.com 
    > Created Time: 2017年01月20日 星期五 17时29分19秒
 ************************************************************************/

#ifndef _NETWORK_H_
#define _NETWORK_H_

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QDataStream>
#include <QHostAddress>

class NetworkThread : public QThread
{
    Q_OBJECT
public:
    NetworkThread(QString remoteIP, quint16 port);

signals:
    void sendFrame(QImage &image);
protected:
    void run();
private:
    QTcpSocket *tcpSocket;
    QUdpSocket *udpSocket;
private slots:
    void connectEstablished();
};

#endif
