#ifndef FlatPixmapButton_H
#define FlatPixmapButton_H

#include <QWidget>
#include<QEvent>
#include<QMouseEvent>
#include<QPixmap>
#include<QPainter>
#include<QLabel>
#include<QStyleOption>
#include<QGridLayout>
#include<QTimer>
#include<QGraphicsDropShadowEffect>
#include"basicwidget.h"
#include<QBitmap>
class FlatPixmapButtonPrivate;
class FlatPixmapButton : public BasicWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(FlatPixmapButton)
public:
    enum SplitDirection{
        HorizontalSplitDirection=0,
        VerticalSplitDirection
    };
    enum ButtonStatue{
        ButtonFirstStatue,
        ButtonScaledStatue,
        ButtonEnterStatue,
        ButtonLeaveStatue,
        ButtonPressedStatue,
        ButtonDisableStatue,
        ButtonDynamicStatue
    };
    explicit FlatPixmapButton(QWidget *parent = 0);
    explicit FlatPixmapButton(const QString &pixmapName,int copiesNumber, SplitDirection direction=HorizontalSplitDirection,QWidget *parent = 0);
    explicit FlatPixmapButton(const QPixmap &pixmap,int copiesNumber,SplitDirection direction=HorizontalSplitDirection, QWidget *parent = 0);
    explicit FlatPixmapButton(const QStringList &pixmapNameList,QWidget *parent = 0);
    explicit FlatPixmapButton(const QList<QPixmap> &pixmapList,QWidget *parent = 0);
    ~FlatPixmapButton();
    void setMaskEnable(bool enable);
    void setPixmapOpacity(qreal narmalOpacity,qreal hoverOpacity,qreal pressedOpacity,qreal disableOpacity);
    QList<qreal> pixmapOpacity();
    void setLevitateEnable(bool moveable,bool globalMoveable=false);
    void setButtonStatus(ButtonStatue status);
    void setNarmalStatuePixmap(const QPixmap &pixmapNormal);
    void setHoverStatuePixmap(const QPixmap &pixmapHover);
    void setPressedStatuePixmap(const QPixmap &pixmapPressed);
    void setDisableStatuePixmap(const QPixmap &pixmapDisable);
    void setAllStatuePixmap(const QString &iconName,int copiesNumber, SplitDirection direction=HorizontalSplitDirection);
    void setAllStatuePixmap(const QStringList &iconNameList);
    void setAllStatuePixmap(const QPixmap &iconPixmap,int copiesNumber,SplitDirection direction=HorizontalSplitDirection);
    void setAllStatuePixmap(const QList<QPixmap> &pixmapList);
    void setCursorEnable(bool enalbe);
    void setAnimalPixmapList(const QString &animalPixmapName,int copiesNumber,SplitDirection direction=HorizontalSplitDirection);
    void setAnimalPixmapList(const QStringList &animalPixmapNameList);
    void setAnimalPixmapList(const QPixmap &animalPixmap,int copiesNumber,SplitDirection direction=HorizontalSplitDirection);
    void setAnimalPixmapList(const QList<QPixmap> &animalPixmapList);
protected:
    void paintEvent(QPaintEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void changeEvent(QEvent *);
    void mouseMoveEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);
signals:
    void sendClicked();
    void sendEnter();
    void sendLeave();
private slots:
    void updateAnimal();
private:
    FlatPixmapButtonPrivate* d_ptr;
};

#endif // FlatPixmapButton_H
