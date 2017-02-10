/*************************************************************************
    > File Name: /home/hero/project/SurfaceIR/showframe/configwindow/configwindow.h
    > Author: zxf
    > Mail: zhengxiaofeng333@163.com 
    > Created Time: 2017年01月20日 星期五 17时36分00秒
 ************************************************************************/


#ifndef _CONNECTIONCONFIGWINDOW_H_
#define _CONNECTIONCONFIGWINDOW_H_

#include <iostream>
#include <unistd.h>

#include <QLabel>
#include <QRegExp>
#include <QDialog>
#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QRegExpValidator>

class ConnectionConfigWindow : public QDialog
{
    Q_OBJECT
public:
    ConnectionConfigWindow(QWidget *parent = 0);
signals:
    void Conform(QString);

private:
    QLabel *deviceIPLabel;
    QLineEdit *leDeviceIP;
    QVBoxLayout *vblMain;
    QPushButton *phbConform;
private slots:
    void on_phbConform_clicked();
};

#endif
