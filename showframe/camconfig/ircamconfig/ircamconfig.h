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
#include "i3system_TE.h"
#include <QIntValidator>
#include <QDoubleValidator>
#include <QRegExpValidator>
#include "i3system_imgproc.h"

class IRCamConfig : public QLabel
{
    Q_OBJECT
public:
    IRCamConfig(QWidget *parent=0);
    ~IRCamConfig();

signals:
    void conformChanges(double &aie, double &contrast, int &brightness, int &colorMap);
    void configChanged(const int colorMap, const int brightness, const float contrast, const float aie);

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

    int currentBrightness;
    float currentContrast, currentAIE;
    int currentColorMap;

    enum{
    WhiteHot = 0,
    BlackHot,
    Iron,
    BlueRed,
    Medical,
    Purple,
    PurpleYellow,
    DarkBlue,
    Cyan,
    Rainbow,
    Autumn,
    Bone,
    Jet,
    Winter,
    Ocean,
    Summer,
    Spring,
    Cool,
    HSV,
    Hot,
    };

private slots:
    void updateBrightnessEdit(int);
    void updateContrastEdit(int);
    void updateAIEEdit(int);

    void updateBrightnessSlider(QString);
    void updateContrastSlider(QString);
    void updateAIESlider(QString);

    void on_conformButton_clicked();
    void on_colorMapButton_clicked();
};

#endif
