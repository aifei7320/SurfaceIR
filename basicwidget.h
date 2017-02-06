#ifndef BASICWIDGET_H
#define BASICWIDGET_H
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#include <QWidget>
#include<QStyleOption>
#include<QPainter>
#include<QtMath>
#include<QMargins>
class BasicWidgetPrivate;
class BasicWidget : public QWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(BasicWidget)
public:
    explicit BasicWidget(QWidget *parent = 0);
    ~BasicWidget();
    void setShadowsMargins(qreal left,qreal top,qreal right,qreal buttom );
    void setShadowsMargins(QMargins shadowMargins);
    QMargins shadowMargins();
    void setShadowsColor(QColor shadowColor);
    QColor shadowColor();
protected:
    void paintEvent(QPaintEvent *event);
signals:

public slots:
private:
    BasicWidgetPrivate *d_ptr;
};

#endif // BASICWIDGET_H
