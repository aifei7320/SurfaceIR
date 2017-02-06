/*************************************************************************
    > File Name: showframe/configwindow/configwindow.cpp
    > Author: zxf
    > Mail: zhengxiaofeng333@163.com 
    > Created Time: 2017年01月20日 星期五 17时35分53秒
 ************************************************************************/

#include <iostream>
#include <unistd.h>
using namespace std;

#include "configwindow.h"
ConfigWindow::ConfigWindow(QWidget *parent) : QDialog(parent)
{
    deviceIPLabel = new QLabel;
    deviceIPLabel->setText(QString::fromUtf8("设备IP:"));

    QRegExp re("((?:(?:25[0-5]|2[0-4]\\d|((1\\d{2})|([1-9]?\\d)))\\.){3}(?:25[0-5]|2[0-4]\\d|((1\\d{2})|([1-9]?\\d))))");
    QRegExpValidator *reValidator = new QRegExpValidator(re);    
    leDeviceIP = new QLineEdit;
    leDeviceIP->setValidator(reValidator);

    phbConform = new QPushButton;
    phbConform->setText("Ok");

    vblMain = new QVBoxLayout;

    vblMain->addWidget(deviceIPLabel);
    vblMain->addWidget(leDeviceIP);
    vblMain->addSpacing(3);
    vblMain->addWidget(phbConform);

    connect(phbConform, SIGNAL(clicked()), this, SLOT(on_phbConform_clicked()));
    setLayout(vblMain);
}

void ConfigWindow::on_phbConform_clicked()
{
    emit Conform(leDeviceIP->text());
    deleteLater();
}
