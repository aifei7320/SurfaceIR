/*************************************************************************
  > File Name: showframe/camconfig/ircamconfig/ircamconfig.h
  > Author: zxf
  > Mail: zhengxiaofeng333@163.com 
  > Created Time: 2017年02月10日 星期五 10时08分04秒
 ************************************************************************/

#ifndef _IRCAMCONFIG_H_
#define _IRCAMCONFIG_H_

#include <QList>
#include <QLabel>
#include <QDebug>
#include <QWidget>
#include <QSlider>
#include <QRegExp>
#include <QLineEdit>
#include <QGroupBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QRegExpValidator>

class IRCamConfig : public QLabel
{
    Q_OBJECT
public:
    IRCamConfig(QWidget *parent=0);
    ~IRCamConfig();
private:
    QSlider *brightnessSlider;
    QSlider *contrastSlider;
    QSlider *aieSlider;

    QLabel *brightnessLabel;
    QLabel *contrastLabel;
    QLabel *aieLabel;

    QLineEdit *brightnessEdit;
    QLineEdit *contrastEdit;
    QLineEdit *aieEdit;

    QRadioButton *autoGainRButton;
    QRadioButton *manulGainRButton;

    QList<QPushButton*> buttonList;
    QGroupBox *colorGroupBox;

    QPushButton *conformButton;

    QVBoxLayout *mainLayout;

    enum color{BLACKHOT=0, BLUERED, IRON, MEDICAL, PURPLE, PURPLEYELLOW, DARKBLUE, CYAN, RAINBOW};
private slots:
    void updateBrightnessEdit(int);
    void updateContrastEdit(int);
    void updateAIEEdit(int);

    void updateBrightnessSlider(QString);
    void updateContrastSlider(QString);
    void updateAIESlider(QString);
};

#endif
