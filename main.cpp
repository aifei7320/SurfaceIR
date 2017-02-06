/*************************************************************************
    > File Name: main.cpp
    > Author: zxf
    > Mail: zhengxiaofeng333@163.com 
    > Created Time: 2017年01月20日 星期五 17时29分48秒
 ************************************************************************/

#include <iostream>
#include <unistd.h>
using namespace std;

#include <QApplication>
#include "mainwindow.h"
#include <QIcon>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setWindowIcon(QIcon(":/desktop/shelly.ico"));
    MainWindow mw;
    mw.resize(1024, 768);
    mw.move(100, 100);
    mw.show();

    app.exec();
}
