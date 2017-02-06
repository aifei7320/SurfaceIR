#include "basicwidget.h"
class BasicWidgetPrivate
{
    Q_DECLARE_PUBLIC(BasicWidget)
public:
    explicit BasicWidgetPrivate(BasicWidget *parent);
    QMargins  shadowMargins;
    QColor shadowColor;
private:
    BasicWidget *q_ptr;
};
BasicWidgetPrivate::BasicWidgetPrivate(BasicWidget *parent):q_ptr(parent)
    {
       shadowMargins=QMargins(0,0,0,0);
       shadowColor=QColor(0,0,0,50);
    }
BasicWidget::BasicWidget(QWidget *parent) : QWidget(parent),d_ptr(new BasicWidgetPrivate(this))
    {

    }

BasicWidget::~BasicWidget()
    {
        deleteLater();
        delete d_ptr;
    }
void BasicWidget::paintEvent(QPaintEvent *)
    {
        Q_D(BasicWidget);
        QStyleOption option;
        option.init(this);
        QPainter painter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
        QColor color=d->shadowColor;
        int  margin=0;
        margin=qMax(d->shadowMargins.left(),d->shadowMargins.top());
        margin=qMax(margin,d->shadowMargins.right());
        margin=qMax(margin,d->shadowMargins.bottom());
        for(int i=0; i<margin; i++)
            {
                QPainterPath path;
                path.setFillRule(Qt::WindingFill);
                path.addRect(d->shadowMargins.left()-i, d->shadowMargins.top()-i, this->width()-(d->shadowMargins.right()-i)*2,
                             this->height()-(d->shadowMargins.bottom()-i)*2);
                color.setAlpha(150 - qSqrt(i)*50);
                painter.setPen(color);
                painter.drawPath(path);
            }
    }
void BasicWidget::setShadowsMargins(qreal left,qreal top,qreal right,qreal buttom )
    {
       Q_D(BasicWidget);
       d->shadowMargins=QMargins(left,top,right,buttom);
    }
void BasicWidget::setShadowsMargins(QMargins shadowMargins)
    {
        Q_D(BasicWidget);
        d->shadowMargins=shadowMargins;
    }
QMargins BasicWidget::shadowMargins()
    {
        Q_D(BasicWidget);
        return d->shadowMargins;
    }
void BasicWidget::setShadowsColor(QColor shadowColor)
    {
        Q_D(BasicWidget);
        d->shadowColor=shadowColor;
        update();
    }
QColor BasicWidget::shadowColor()
    {
        Q_D(BasicWidget);
        return d->shadowColor;
    }
