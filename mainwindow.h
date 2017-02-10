/*************************************************************************
    > File Name: /home/hero/project/SurfaceIR/mainwindow.h
    > Author: zxf
    > Mail: zhengxiaofeng333@163.com 
    > Created Time: 2017年01月20日 星期五 17时30分57秒
 ************************************************************************/

#include <iostream>
#include <unistd.h>
using namespace std;

#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QLabel>
#include <QWidget>
#include <QKeyEvent>
#include <QPushButton>
#include <QGridLayout>
#include <QResizeEvent>
#include "showframe/showframe.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent = 0);
    bool createShowFrame();     

protected:
    void resizeEvent(QResizeEvent *e);
    void keyPressEvent(QKeyEvent *e);
    
private:
    ShowFrame *sfLeftTop;
    ShowFrame *sfRightTop;
    ShowFrame *sfLeftBottom;
    ShowFrame *sfRightBottom;

    QGridLayout *mainLayout;
    bool change;

private slots:
    void on_sfLeftTop_clicked();
    void on_sfRightTop_clicked();
    void on_sfLeftBottom_clicked();
    void on_sfRightBottom_clicked();
};

#endif
