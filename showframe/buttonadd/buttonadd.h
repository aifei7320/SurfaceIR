/*************************************************************************
    > File Name: showframe/buttonadd/buttonadd.h
    > Author: zxf
    > Mail: zhengxiaofeng333@163.com 
    > Created Time: 2017年01月20日 星期五 17时30分17秒
 ************************************************************************/

#include <iostream>
#include <unistd.h>
using namespace std;

#ifndef _BUTTONADD_H_
#define _BUTTONADD_H_

#include <QPen>
#include <QDebug>
#include <QWidget>
#include <QPainter>
#include <QPushButton>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainterPath>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect> 


class ButtonAdd : public QPushButton
{
    Q_OBJECT
public:
    ButtonAdd(QWidget *parent=0);

protected:
    void paintEvent(QPaintEvent *e);
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
private:
    QColor penColor;
    QColor brushColor;
};

#endif
