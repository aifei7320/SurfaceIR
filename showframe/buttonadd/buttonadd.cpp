/*************************************************************************
    > File Name: showframe/buttonadd/buttonadd.cpp
    > Author: zxf
    > Mail: zhengxiaofeng333@163.com 
    > Created Time: 2017年01月20日 星期五 17时30分23秒
 ************************************************************************/

#include <iostream>
#include <unistd.h>
using namespace std;

#include "buttonadd.h"

ButtonAdd::ButtonAdd(QWidget *parent) : QPushButton(parent),
    penColor(QColor(255, 255, 255, 100)), brushColor(QColor(255, 255, 255, 100))
{

    setStyleSheet("QPushButton{ background-color:red;}");
    setAutoFillBackground(true);
    setMinimumSize(80, 80);
}

void ButtonAdd::paintEvent(QPaintEvent *e)
{
    quint16 h, w, xishu, halfPenWidth;
    h = height();
    w = width();
    xishu = 10;
    halfPenWidth = 2;
    //QPushButton::paintEvent(e);
    QPainter painter(this);
    QPen pen;
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setColor(penColor);
    pen.setWidth(4);
    painter.setPen(pen);
    painter.setBrush(brushColor);

    QPainterPath path;
    path.moveTo(w / 2 - xishu,  halfPenWidth);
    path.lineTo(w / 2 + xishu,  halfPenWidth);
    path.lineTo(w / 2 + xishu, h / 2 - xishu);
    path.lineTo(w - halfPenWidth, h / 2 - xishu);
    path.lineTo(w - halfPenWidth, h / 2 + xishu);
    path.lineTo(w / 2 + xishu, h / 2 + xishu);
    path.lineTo(w / 2 + xishu, h - halfPenWidth);
    path.lineTo(w / 2 - xishu, h - halfPenWidth);
    path.lineTo(w / 2 - xishu, h / 2 + xishu);
    path.lineTo(halfPenWidth, h / 2 + xishu);
    path.lineTo(halfPenWidth, h / 2 - xishu);
    path.lineTo(w / 2 - xishu, h / 2 - xishu);
    path.lineTo(w / 2 - xishu, halfPenWidth);
    painter.drawPath(path);    
    

    //painter.drawLine(0, h / 2 - xishu, w / 2 - xishu, h / 2 - xishu);
    //painter.drawLine(0, h / 2 + xishu, w / 2 - xishu, h / 2 + xishu);

    //painter.drawLine(w / 2 - xishu, halfPenWidth, w / 2 + xishu, halfPenWidth);
    //painter.drawLine(w / 2 - xishu, h - halfPenWidth, w / 2 + xishu, h - halfPenWidth);

    //painter.drawLine(w / 2 + xishu, h / 2 - xishu, w, h / 2 - xishu);
    //painter.drawLine(w / 2 + xishu, h / 2 + xishu, w, h / 2 + xishu);

    //painter.drawLine(w / 2 - xishu, 0, w / 2 - xishu, h / 2 - xishu);
    //painter.drawLine(w / 2 + xishu, 0, w / 2 + xishu, h / 2 - xishu);

    //painter.drawLine(w / 2 + xishu, h / 2 + xishu, w / 2 + xishu, h);
    //painter.drawLine(w / 2 - xishu, h / 2 + xishu, w / 2 - xishu, h);

    //painter.drawLine(halfPenWidth, h / 2 - xishu, halfPenWidth, h / 2 + xishu);
    //painter.drawLine(w - halfPenWidth, h / 2 - xishu, w - halfPenWidth, h / 2 + xishu);
}

void ButtonAdd::enterEvent(QEvent *e)
{
    QPushButton::enterEvent(e);
    penColor = QColor(255, 255, 255, 200);
    brushColor = QColor(255, 255, 255, 200);  
}

void ButtonAdd::leaveEvent(QEvent *e)
{
    QPushButton::leaveEvent(e);
    penColor = QColor(255, 255, 255, 100);
    brushColor = QColor(255, 255, 255, 100);
}

void ButtonAdd::mousePressEvent(QMouseEvent *e)
{
    QPushButton::mousePressEvent(e);
    penColor = QColor(255, 255, 255, 255);
    brushColor = QColor(255, 255, 255, 255);
    update();
}

void ButtonAdd::mouseReleaseEvent(QMouseEvent *e)
{
    QPushButton::mouseReleaseEvent(e);
    penColor = QColor(255, 255, 255, 200);
    brushColor = QColor(255, 255, 255, 200);  
    update();
}
