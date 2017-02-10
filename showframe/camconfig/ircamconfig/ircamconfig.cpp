/*************************************************************************
    > File Name: /home/hero/project/SurfaceIR/showframe/camconfig/ircamconfig/ircamconfig.cpp
    > Author: zxf
    > Mail: zhengxiaofeng333@163.com 
    > Created Time: 2017年02月10日 星期五 10时09分30秒
 ************************************************************************/

#include <iostream>
#include <unistd.h>
#include "ircamconfig.h"
using namespace std;

IRCamConfig::IRCamConfig(QWidget *parent) : QLabel(parent)
{

    QHBoxLayout *contrastLayout = new QHBoxLayout;

    contrastSlider = new QSlider;
    contrastSlider->setRange(0, 1000);
    contrastSlider->setValue(100);
    contrastSlider->setOrientation(Qt::Horizontal);

    contrastLabel = new QLabel(QString::fromUtf8("锐度:"));

    contrastEdit = new QLineEdit("1");
    contrastEdit->setValidator(new QRegExpValidator(QRegExp("(?:\\d\\.\\d\\d)|10")));

    contrastLayout->addWidget(contrastLabel, Qt::AlignRight);
    contrastLayout->addWidget(contrastEdit);
    contrastLayout->addWidget(contrastSlider);
    contrastLayout->setStretch(0, 1);
    contrastLayout->setStretch(1, 1);
    contrastLayout->setStretch(2, 4);

    QHBoxLayout *brightnessLayout = new QHBoxLayout;

    brightnessSlider = new QSlider;
    brightnessSlider->setRange(-128, 128);
    brightnessSlider->setValue(0);
    brightnessSlider->setOrientation(Qt::Horizontal);

    brightnessLabel = new QLabel(QString::fromUtf8("亮度:"));
    
    brightnessEdit = new QLineEdit("0");
    brightnessEdit->setValidator(new QIntValidator(-128, 128));
    brightnessLayout->addWidget(brightnessLabel, Qt::AlignRight);
    brightnessLayout->addWidget(brightnessEdit);
    brightnessLayout->addWidget(brightnessSlider);
    brightnessLayout->setStretch(0, 1);
    brightnessLayout->setStretch(1, 1);
    brightnessLayout->setStretch(2, 4);

    QHBoxLayout *aieLayout = new QHBoxLayout;
    aieSlider = new QSlider;
    aieSlider->setRange(100, 1000);
    aieSlider->setValue(100);
    aieSlider->setOrientation(Qt::Horizontal);

    aieLabel = new QLabel(QString::fromUtf8("AIE:"));
    aieEdit = new QLineEdit("1");
    aieEdit->setValidator(new QRegExpValidator(QRegExp("(?:[1-9]\\.\\d\\d)|10")));
    aieLayout->addWidget(aieLabel, Qt::AlignRight);
    aieLayout->addWidget(aieEdit);
    aieLayout->addWidget(aieSlider);
    aieLayout->setStretch(0, 1);
    aieLayout->setStretch(1, 1);
    aieLayout->setStretch(2, 4);

    colorGroupBox = new QGroupBox(QString::fromUtf8("颜色映射"));
    QGridLayout *colorGridLayout = new QGridLayout;

    for (int i = 0; i < 9; ++i){
        buttonList.append(new QPushButton);
        colorGridLayout->addWidget(buttonList[i], i / 3, i % 3);
        buttonList[i]->setMinimumSize(50, 50);
    }
    colorGroupBox->setLayout(colorGridLayout);

    conformButton = new QPushButton(QString::fromUtf8("确认设置"));
    conformButton->setObjectName("conformButton");


    mainLayout = new QVBoxLayout;

    mainLayout->addWidget(colorGroupBox);
    mainLayout->addLayout(brightnessLayout);
    mainLayout->addLayout(contrastLayout);
    mainLayout->addLayout(aieLayout);
    mainLayout->addWidget(conformButton);

    connect(brightnessSlider, SIGNAL(valueChanged(int)), this, SLOT(updateBrightnessEdit(int)));
    connect(contrastSlider, SIGNAL(valueChanged(int)), this, SLOT(updateContrastEdit(int)));
    connect(aieSlider, SIGNAL(valueChanged(int)), this, SLOT(updateAIEEdit(int)));

    connect(brightnessEdit, SIGNAL(textChanged(QString)), this, SLOT(updateBrightnessSlider(QString)));
    connect(contrastEdit, SIGNAL(textChanged(QString)), this, SLOT(updateContrastSlider(QString)));
    connect(aieEdit, SIGNAL(textChanged(QString)), this, SLOT(updateAIESlider(QString)));
    
    setStyleSheet("QPushButton#conformButton{ background-color:darkcyan}");
    setLayout(mainLayout);
}

IRCamConfig::~IRCamConfig()
{
    delete conformButton;
    delete mainLayout;
    delete colorGroupBox;

    delete brightnessLabel;
    delete brightnessEdit;
    delete brightnessSlider;

    delete contrastLabel;
    delete contrastEdit;
    delete contrastSlider;

    delete aieLabel;
    delete aieEdit;
    delete aieSlider;

    buttonList.clear();
    cout<<"ir destruct"<<endl;
}

void IRCamConfig::updateBrightnessEdit(int value)
{
    brightnessEdit->setText(QString::number(value));
}

void IRCamConfig::updateContrastEdit(int value)
{
    contrastEdit->setText(QString::number(value / 100.0, 'g', 3));
}


void IRCamConfig::updateAIEEdit(int value)
{
    aieEdit->setText(QString::number(value / 100.0, 'g', 3));
}


void IRCamConfig::updateAIESlider(QString string)
{
    aieSlider->setValue(string.toDouble() * 100);
}

void IRCamConfig::updateBrightnessSlider(QString string)
{
    brightnessSlider->setValue(string.toInt() );
}

void IRCamConfig::updateContrastSlider(QString string)
{
    contrastSlider->setValue(string.toDouble() * 100);
}

