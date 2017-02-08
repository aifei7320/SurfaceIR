/*************************************************************************
    > File Name: showframe/toolbutton/toolbutton.h
    > Author: zxf
    > Mail: zhengxiaofeng333@163.com 
    > Created Time: 2017年01月22日 星期日 17时09分41秒
 ************************************************************************/

#ifndef _TOOLBUTTON_H_
#define _TOOLBUTTON_H_


#include <QPen>
#include <QEvent>
#include <QDebug>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>
#include <QPaintEvent>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

class ToolButton : public QPushButton
{
    Q_OBJECT
public:
    ToolButton(QWidget *parent = 0);

protected:
    void enterEvent(QEvent *e);
    void mouseReleaseEvent(QEvent *e);
    void leaveEvent(QEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);

};

#endif
