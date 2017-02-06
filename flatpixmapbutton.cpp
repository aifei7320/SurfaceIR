#include "flatpixmapbutton.h"
class FlatPixmapButtonPrivate
{
    Q_DECLARE_PUBLIC(FlatPixmapButton)
public:
    explicit FlatPixmapButtonPrivate(FlatPixmapButton *parent);
    QPixmap currentPixmap;
    QList<QPixmap> pixmapList;
    QList<QPixmap> dynamicPixmapList;
    QCursor preCursor;
    bool isCursor;
    bool isLevitate;
    QTimer *timer;
    int currentAnimalIndex;
    QPoint relativePos;
    qreal pixmapOpacity;
    bool isSetMask;
    qreal narmalOpacity;
    qreal hoverOpacity;
    qreal pressedOpacity;
    qreal disableOpacity;
private:
    FlatPixmapButton *q_ptr;
};
FlatPixmapButtonPrivate::FlatPixmapButtonPrivate(FlatPixmapButton *parent):q_ptr(parent)
    {
        narmalOpacity=0.8;
        hoverOpacity=0.8;
        pressedOpacity=0.8;
        disableOpacity=0.8;
        isCursor=true;
        currentAnimalIndex=0;
        isLevitate=true;
        isSetMask=true;
        pixmapOpacity=0.8;
        timer=new QTimer(q_ptr);
        pixmapList.reserve(400);
        pixmapList<<QPixmap()<<QPixmap()<<QPixmap()<<QPixmap();
        QObject::connect(timer,SIGNAL(timeout()),q_ptr,SLOT(updateAnimal()));
        q_ptr->setMinimumSize(QSize(30,30));
        //       加阴影
        //        QGraphicsDropShadowEffect *effect=new QGraphicsDropShadowEffect(q_ptr);
        //        effect->setOffset(-5, 5);
        //        effect->setColor(Qt::gray);
        //        effect->setBlurRadius(8);
        //        q_ptr->setGraphicsEffect(effect);
    }
FlatPixmapButton::FlatPixmapButton(QWidget *parent) : BasicWidget(parent),d_ptr(new FlatPixmapButtonPrivate(this))
    {
        setAttribute(Qt::WA_TranslucentBackground);
    }
FlatPixmapButton::FlatPixmapButton(const QString &iconName,int copiesNumber, SplitDirection direction,QWidget *parent): BasicWidget(parent),d_ptr(new FlatPixmapButtonPrivate(this))
    {
        setAttribute(Qt::WA_TranslucentBackground);
        setAllStatuePixmap(iconName,copiesNumber,direction);
    }
FlatPixmapButton::FlatPixmapButton(const QPixmap &iconPixmap,int copiesNumber,SplitDirection direction, QWidget *parent) : BasicWidget(parent),d_ptr(new FlatPixmapButtonPrivate(this))
    {
        setAttribute(Qt::WA_TranslucentBackground);
        setAllStatuePixmap(iconPixmap,copiesNumber,direction);
    }
FlatPixmapButton::FlatPixmapButton(const QStringList &iconNameList,QWidget *parent) : BasicWidget(parent),d_ptr(new FlatPixmapButtonPrivate(this))
    {
        setAttribute(Qt::WA_TranslucentBackground);
        setAllStatuePixmap(iconNameList);
    }
FlatPixmapButton::FlatPixmapButton(const QList<QPixmap> &pixmapList,QWidget *parent) : BasicWidget(parent),d_ptr(new FlatPixmapButtonPrivate(this))
    {
        setAttribute(Qt::WA_TranslucentBackground);
        setAllStatuePixmap(pixmapList);
    }

FlatPixmapButton::~FlatPixmapButton()
    {
        deleteLater();
        d_ptr->timer->stop ();
        d_ptr->timer->deleteLater ();
        delete d_ptr;
    }
void FlatPixmapButton::setCursorEnable(bool enalbe)
    {
        Q_D(FlatPixmapButton);
        d->isCursor=enalbe;
    }
void FlatPixmapButton::setNarmalStatuePixmap(const QPixmap &pixmapNormal)
    {
        Q_D(FlatPixmapButton);
        d->pixmapList.replace(0,pixmapNormal);
    }
void FlatPixmapButton::setHoverStatuePixmap(const QPixmap &pixmapHover)
    {
        Q_D(FlatPixmapButton);
        d->pixmapList.replace(1,pixmapHover);
    }
void FlatPixmapButton::setPressedStatuePixmap(const QPixmap &pixmapPressed)
    {
        Q_D(FlatPixmapButton);
        d->pixmapList.replace(2,pixmapPressed);
    }
void FlatPixmapButton::setDisableStatuePixmap(const QPixmap &pixmapDisable)
    {
        Q_D(FlatPixmapButton);
        d->pixmapList.replace(3,pixmapDisable);
    }
void FlatPixmapButton::setAllStatuePixmap(const QStringList &iconNameList)
    {
        Q_D(FlatPixmapButton);
        for(int i=0;i<iconNameList.size()&&i<4;i++)
            {
                QPixmap pixmap=QPixmap(iconNameList.at(i));
                if(pixmap.isNull())
                    {
                        if(i==0)
                            {

                            }
                        else if(i==3)
                            {
                                if(!d->pixmapList.at(0).isNull())
                                    {
                                        QImage image=d->pixmapList.at(0).toImage();
                                        QImage image2 = image.convertToFormat(QImage::Format_Indexed8);
                                        image2.setColorCount(256);
                                        for(int i = 0; i < 256; i++)
                                            {
                                                if(i<190)
                                                    image2.setColor(i,qRgb(190, 190, 190));
                                                else if(i>210)
                                                    image2.setColor(i,qRgb(255, 255, 255));
                                                else image2.setColor(i,qRgb(i, i, i));
                                            }
                                        image2.setAlphaChannel(d->pixmapList.at(0).toImage().alphaChannel());
                                        d->pixmapList.replace(3,QPixmap::fromImage(image2));
                                    }
                            }
                        else
                            {
                                pixmap=d->pixmapList.at(i-1);
                            }
                    }
                d->pixmapList.replace(i,pixmap);
            }
        if(iconNameList.size()<=3)
            {
                if(!d->pixmapList.at(0).isNull())
                    {
                        if(d->pixmapList.at(1).isNull()) d->pixmapList.replace(1,d->pixmapList.at(0));
                        if(d->pixmapList.at(2).isNull()) d->pixmapList.replace(2,d->pixmapList.at(0));
                        QImage image=d->pixmapList.at(0).toImage();
                        QImage image2 = image.convertToFormat(QImage::Format_Indexed8);
                        image2.setColorCount(256);
                        for(int i = 0; i < 256; i++)
                            {
                                if(i<190)
                                    image2.setColor(i,qRgb(190, 190, 190));
                                else if(i>210)
                                    image2.setColor(i,qRgb(255, 255, 255));
                                else image2.setColor(i,qRgb(i, i, i));
                            }
                        image2.setAlphaChannel(d->pixmapList.at(0).toImage().alphaChannel());
                        d->pixmapList.replace(3,QPixmap::fromImage(image2));
                    }
            }

    }
void FlatPixmapButton::setAllStatuePixmap(const QPixmap &pixmap,int copiesNumber,SplitDirection direction)
    {
        Q_D(FlatPixmapButton);
        if(!pixmap.isNull())
            {
                switch (direction) {
                    case VerticalSplitDirection:{
                            for(int i=0; i != copiesNumber; i++)
                                {
                                    d->pixmapList.replace(i,pixmap.copy(0,i*(pixmap.height()/copiesNumber), pixmap.width(), pixmap.height()/copiesNumber));
                                }
                            if(d->pixmapList.size())
                                {
                                    d->currentPixmap = d->pixmapList.at(0);
                                }
                            break;}
                    case HorizontalSplitDirection:{
                            for(int i=0; i != copiesNumber; i++)
                                {
                                    d->pixmapList.replace(i,pixmap.copy(i*(pixmap.width()/copiesNumber), 0, pixmap.width()/copiesNumber, pixmap.height()));
                                }
                            if(d->pixmapList.size())
                                d->currentPixmap = d->pixmapList.at(0);
                            break;}
                    default:
                        break;
                    }
                if(copiesNumber<=3)
                    {
                        if(!d->pixmapList.at(0).isNull())
                            {
                                if(d->pixmapList.at(1).isNull()) d->pixmapList.replace(1,d->pixmapList.at(0));
                                if(d->pixmapList.at(2).isNull()) d->pixmapList.replace(2,d->pixmapList.at(0));
                                QImage image=d->pixmapList.at(0).toImage();
                                QImage image2 = image.convertToFormat(QImage::Format_Indexed8);
                                image2.setColorCount(256);
                                for(int i = 0; i < 256; i++)
                                    {
                                        if(i<190)
                                            image2.setColor(i,qRgb(190, 190, 190));
                                        else if(i>210)
                                            image2.setColor(i,qRgb(255, 255, 255));
                                        else image2.setColor(i,qRgb(i, i, i));
                                    }
                                image2.setAlphaChannel(d->pixmapList.at(0).toImage().alphaChannel());
                                d->pixmapList.replace(3,QPixmap::fromImage(image2));
                            }
                    }
            }
    }
void FlatPixmapButton::setAllStatuePixmap(const QList<QPixmap> &pixmapList)
    {
        Q_D(FlatPixmapButton);
        for(int i=0;i<pixmapList.size()&&i<4;i++)
            {
                d->pixmapList.replace(i,pixmapList.at(i));
            }
        if(pixmapList.size()<=3)
            {
                if(!d->pixmapList.at(0).isNull())
                    {
                        if(d->pixmapList.at(1).isNull()) d->pixmapList.replace(1,d->pixmapList.at(0));
                        if(d->pixmapList.at(2).isNull()) d->pixmapList.replace(2,d->pixmapList.at(0));
                        QImage image=d->pixmapList.at(0).toImage();
                        QImage image2 = image.convertToFormat(QImage::Format_Indexed8);
                        image2.setColorCount(256);
                        for(int i = 0; i < 256; i++)
                            {
                                if(i<190)
                                    image2.setColor(i,qRgb(190, 190, 190));
                                else if(i>210)
                                    image2.setColor(i,qRgb(255, 255, 255));
                                else image2.setColor(i,qRgb(i, i, i));
                            }
                        image2.setAlphaChannel(d->pixmapList.at(0).toImage().alphaChannel());
                        d->pixmapList.replace(3,QPixmap::fromImage(image2));
                    }
            }
    }
void FlatPixmapButton::setAllStatuePixmap(const QString &iconName,int copiesNumber, SplitDirection direction)
    {
        Q_D(FlatPixmapButton);
        QPixmap pixmap(iconName);
        if(!pixmap.isNull())
            {
                switch (direction) {
                    case VerticalSplitDirection:{
                            for(int i=0; i != copiesNumber&&i<4; i++)
                                {
                                    d->pixmapList.replace(i,pixmap.copy(0,i*(pixmap.height()/copiesNumber), pixmap.width(), pixmap.height()/copiesNumber));
                                }
                            if(d->pixmapList.size())
                                d->currentPixmap = d->pixmapList.at(0);
                            break;}
                    case HorizontalSplitDirection:{
                            for(int i=0; i != copiesNumber&&i<4; i++)
                                {
                                    d->pixmapList.replace(i,pixmap.copy(i*(pixmap.width()/copiesNumber), 0, pixmap.width()/copiesNumber, pixmap.height()));
                                }
                            if(d->pixmapList.size())
                                d->currentPixmap = d->pixmapList.at(0);
                            break;}
                    default:
                        break;
                    }
                if(copiesNumber<=3)
                    {
                        if(!d->pixmapList.at(0).isNull())
                            {
                                if(d->pixmapList.at(1).isNull()) d->pixmapList.replace(1,d->pixmapList.at(0));
                                if(d->pixmapList.at(2).isNull()) d->pixmapList.replace(2,d->pixmapList.at(0));
                                QImage image=d->pixmapList.at(0).toImage();
                                QImage image2 = image.convertToFormat(QImage::Format_Indexed8);
                                image2.setColorCount(256);
                                for(int i = 0; i < 256; i++)
                                    {
                                        if(i<190)
                                            image2.setColor(i,qRgb(190, 190, 190));
                                        else if(i>210)
                                            image2.setColor(i,qRgb(255, 255, 255));
                                        else image2.setColor(i,qRgb(i, i, i));
                                    }
                                image2.setAlphaChannel(d->pixmapList.at(0).toImage().alphaChannel());
                                d->pixmapList.replace(3,QPixmap::fromImage(image2));
                            }
                    }
            }
    }
void FlatPixmapButton::setButtonStatus(ButtonStatue status)
    {
        Q_D(FlatPixmapButton);
        if(isEnabled())
            {
                switch (status) {
                    case ButtonFirstStatue:{
                            if(d->pixmapList.size())
                                d->currentPixmap = d->pixmapList.at(0);
                            d->pixmapOpacity=d->narmalOpacity;
                            break;}
                    case ButtonEnterStatue:{
                            if(d->pixmapList.size()>1)
                                d->currentPixmap = d->pixmapList.at(1);
                            d->pixmapOpacity=d->hoverOpacity;
                            break;}
                    case ButtonLeaveStatue:{
                            if(d->pixmapList.size())
                                d->currentPixmap = d->pixmapList.at(0);
                            d->pixmapOpacity=d->narmalOpacity;
                            break;}
                    case ButtonPressedStatue:{
                            if(d->pixmapList.size()>2)
                                d->currentPixmap = d->pixmapList.at(2);
                            d->pixmapOpacity=d->pressedOpacity;
                            break;}
                    case ButtonDynamicStatue:{
                            if(d->currentAnimalIndex>=0&&d->currentAnimalIndex<d->dynamicPixmapList.size())
                                d->currentPixmap=d->dynamicPixmapList.at(d->currentAnimalIndex);
                            d->pixmapOpacity=d->hoverOpacity;
                            break;}
                    default:
                        break;
                    }
            }
        else{
                if(d->pixmapList.size()>3)
                    d->currentPixmap = d->pixmapList.at(3);
                d->pixmapOpacity=d->disableOpacity;
            }
        update();
    }
void FlatPixmapButton::paintEvent(QPaintEvent *)
    {
        Q_D(FlatPixmapButton);
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setOpacity(d->pixmapOpacity);
        if(!d->currentPixmap.isNull())
            painter.drawPixmap(rect(), d->currentPixmap.scaled(width(),height()));
    }
void FlatPixmapButton::enterEvent(QEvent *)
    {
        Q_D(FlatPixmapButton);
        if(d->isCursor)
            {
                d->preCursor = cursor();
                setCursor(Qt::OpenHandCursor);
            }
        if(d->timer->isActive()==false)
            {
                d->currentAnimalIndex=0;
                d->timer->start(100);
            }
        setButtonStatus(ButtonEnterStatue);
        emit sendEnter();
    }
void FlatPixmapButton::leaveEvent(QEvent *)
    {
        Q_D(FlatPixmapButton);
        if(d->isCursor)
            {
                setCursor(d->preCursor);
            }
        if(d->timer->isActive())
            {
                d->timer->stop();
            }
        setButtonStatus(ButtonLeaveStatue);
        emit sendLeave();
    }
void FlatPixmapButton::mousePressEvent(QMouseEvent *e)
    {
        Q_D(FlatPixmapButton);
        if (e->button() != Qt::LeftButton) {
                e->ignore();
                return;
            }
        d->relativePos =pos()-e->globalPos();
        setButtonStatus(ButtonPressedStatue);
       // e->ignore();
    }
void FlatPixmapButton::mouseReleaseEvent(QMouseEvent *e)
    {
        if (e->button() != Qt::LeftButton) {
                e->ignore();
                return;
            }
        if(isEnabled())
            emit sendClicked();
        else e->ignore();
        setButtonStatus(ButtonEnterStatue);
      //  e->ignore();
    }
void FlatPixmapButton::changeEvent(QEvent *e)
    {
        if(e->type() == QEvent::EnabledChange)
            {
                if(isEnabled()==false) setButtonStatus(ButtonDisableStatue);
                else setButtonStatus(ButtonFirstStatue);
            }
    }
void FlatPixmapButton::mouseMoveEvent(QMouseEvent *event)
    {
        Q_D(FlatPixmapButton);
        if(d->isLevitate)
            {
                move(event->globalPos()+d->relativePos);
            }
       // else event->ignore();
    }
void FlatPixmapButton::resizeEvent(QResizeEvent *event)
    {
        Q_D(FlatPixmapButton);
        if((d->pixmapList.size()&&d->pixmapList.at(0).isNull()==false)&&d->isSetMask)
            setMask(d->pixmapList.at(0).scaled(event->size().width(),event->size().height()).mask());
    }
void FlatPixmapButton::updateAnimal()
    {
        Q_D(FlatPixmapButton);
        setButtonStatus(ButtonDynamicStatue);
        d->currentAnimalIndex++;
        if(d->currentAnimalIndex>=d->dynamicPixmapList.size()) d->timer->stop();
    }
void FlatPixmapButton::setAnimalPixmapList(const QString &animalPixmapName,int copiesNumber,SplitDirection direction)
    {
        Q_D(FlatPixmapButton);
        QPixmap pixmap(animalPixmapName);
        d->dynamicPixmapList.clear();
        if(pixmap.isNull()==false)
            for(int i=0;i<copiesNumber;i++)
                {
                    switch (direction) {
                        case VerticalSplitDirection:{
                                d->dynamicPixmapList.append(pixmap.copy(0,i*(pixmap.height()/copiesNumber), pixmap.width(), pixmap.height()/copiesNumber));
                                break;}
                        case HorizontalSplitDirection:{
                                d->dynamicPixmapList.append(pixmap.copy(i*(pixmap.width()/copiesNumber), 0, pixmap.width()/copiesNumber, pixmap.height()));
                                break;}
                        default:
                            break;
                        }
                }
    }
void FlatPixmapButton::setAnimalPixmapList(const QStringList &animalPixmapNameList)
    {
        Q_D(FlatPixmapButton);
        d->dynamicPixmapList.clear();
        for(int i=0;i<animalPixmapNameList.size();i++)
            {
                QPixmap pixmap(animalPixmapNameList.at(i));
                d->dynamicPixmapList.append(pixmap);
            }
    }
void FlatPixmapButton::setAnimalPixmapList(const QPixmap &pixmap,int copiesNumber,SplitDirection direction)
    {
        Q_D(FlatPixmapButton);
        d->dynamicPixmapList.clear();
        if(pixmap.isNull()==false)
            for(int i=0;i<copiesNumber;i++)
                {
                    switch (direction) {
                        case VerticalSplitDirection:{
                                d->dynamicPixmapList.append(pixmap.copy(0,i*(pixmap.height()/copiesNumber), pixmap.width(), pixmap.height()/copiesNumber));
                                break;}
                        case HorizontalSplitDirection:{
                                d->dynamicPixmapList.append(pixmap.copy(i*(pixmap.width()/copiesNumber), 0, pixmap.width()/copiesNumber, pixmap.height()));
                                break;}
                        default:
                            break;
                        }
                }
    }
void FlatPixmapButton::setAnimalPixmapList(const QList<QPixmap> &animalPixmapList)
    {
        Q_D(FlatPixmapButton);
        d->dynamicPixmapList.clear();
        d->dynamicPixmapList=animalPixmapList;
    }
void FlatPixmapButton::setLevitateEnable(bool enable,bool globalMoveable)
    {
        Q_D(FlatPixmapButton);
        d->isLevitate=enable;
        if(globalMoveable)
            {
                setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
            }
    }
void FlatPixmapButton::setPixmapOpacity(qreal narmalOpacity,qreal hoverOpacity,qreal pressedOpacity,qreal disableOpacity)
    {
        Q_D(FlatPixmapButton);
        d->narmalOpacity=narmalOpacity;
        d->hoverOpacity=hoverOpacity;
        d->pressedOpacity=pressedOpacity;
        d->disableOpacity=disableOpacity;
        setButtonStatus(ButtonFirstStatue);
    }
QList<qreal> FlatPixmapButton::pixmapOpacity()
    {
        Q_D(FlatPixmapButton);
        QList<qreal> list;
        list<<d->narmalOpacity<<d->hoverOpacity<<d->pressedOpacity<<d->disableOpacity;
        return list;
    }
void FlatPixmapButton::setMaskEnable(bool enable)
    {
        Q_D(FlatPixmapButton);
        d->isSetMask=enable;
        if(enable) resize(size());
    }
