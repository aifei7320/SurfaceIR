/*************************************************************************
    > File Name: /home/hero/project/SurfaceIR/showframe/toolbutton/toolbutton.cpp
    > Author: zxf
    > Mail: zhengxiaofeng333@163.com 
    > Created Time: 2017年01月22日 星期日 17时22分03秒
 ************************************************************************/

#include "toolbutton.h"


ToolButton::ToolButton(QWidget *parent) : QPushButton(parent)
{
    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
    setGraphicsEffect(eff);
    QPropertyAnimation *a = new QPropertyAnimation(eff,"opacity");
    a->setDuration(5000);
    a->setStartValue(1);
    a->setEndValue(0);
    a->setEasingCurve(QEasingCurve::InBack);
    a->start();
}

void ToolButton::enterEvent(QEvent *e)
{
    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
    setGraphicsEffect(eff);
    QPropertyAnimation *a = new QPropertyAnimation(eff,"opacity");
    a->setDuration(100);
    a->setStartValue(0);
    a->setEndValue(0.5);
    a->setEasingCurve(QEasingCurve::InBack);
    a->start();

}

void ToolButton::leaveEvent(QEvent *e)
{
    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
    setGraphicsEffect(eff);
    QPropertyAnimation *a = new QPropertyAnimation(eff,"opacity");
    a->setDuration(5000);
    a->setStartValue(0.5);
    a->setEndValue(0);
    a->setEasingCurve(QEasingCurve::InBack);
    a->start();
}

void ToolButton::mouseReleaseEvent(QEvent *e)
{
    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
    setGraphicsEffect(eff);
    QPropertyAnimation *a = new QPropertyAnimation(eff,"opacity");
    a->setDuration(100);
    a->setStartValue(1);
    a->setEndValue(0.5);
    a->setEasingCurve(QEasingCurve::InBack);
    a->start();
}

void ToolButton::mousePressEvent(QMouseEvent *e)
{
    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
    setGraphicsEffect(eff);
    QPropertyAnimation *a = new QPropertyAnimation(eff,"opacity");
    a->setDuration(100);
    a->setStartValue(0.5);
    a->setEndValue(1);
    a->setEasingCurve(QEasingCurve::InBack);
    a->start();
}


void ToolButton::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QPen pen;
    pen.setColor(QColor(0, 255, 0, 50));
    pen.setWidth(2);
    painter.save();
    painter.setPen(pen);
    painter.setBrush(QColor(0, 255, 0, 50));
    painter.drawEllipse(0, 0, width(), height());
    painter.restore();
    pen.setColor(Qt::black);
    painter.setFont(QFont("AR PL UKai CN"));
    painter.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter, text());
}
