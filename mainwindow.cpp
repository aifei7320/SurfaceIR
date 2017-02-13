/*************************************************************************
    > File Name: /home/hero/project/SurfaceIR/mainwindow.cpp
    > Author: zxf
    > Mail: zhengxiaofeng333@163.com 
    > Created Time: 2017年01月20日 星期五 17时31分02秒
 ************************************************************************/

#include <iostream>
#include <unistd.h>
using namespace std;

#include <mainwindow.h>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent),
    change(false)
{
    mainLayout = new QGridLayout;
    //mainLayout->setMargin(2);
    mainLayout->setContentsMargins(2, 2, 2, 2);
    //mainLayout->setSpacing(2);
    
    sfLeftTop = new ShowFrame;
    sfLeftBottom = new ShowFrame;
    sfRightTop = new ShowFrame;
    sfRightBottom = new ShowFrame;

    sfLeftTop->setID(1);
    sfRightTop->setID(2);
    sfLeftBottom->setID(3);
    sfRightBottom->setID(4);


    sfLeftTop->setMinimumSize(width() / 2, height() / 2);
    sfLeftBottom->setMinimumSize(width() / 2, height() / 2);
    sfRightTop->setMinimumSize(width() / 2, height() / 2);
    sfRightBottom->setMinimumSize(width() / 2, height() / 2);

    mainLayout->addWidget(sfLeftTop, 0, 0, Qt::AlignCenter);
    mainLayout->addWidget(sfRightTop, 0, 1, Qt::AlignCenter);
    mainLayout->addWidget(sfLeftBottom, 1, 0, Qt::AlignCenter);
    mainLayout->addWidget(sfRightBottom, 1, 1, Qt::AlignCenter);


    setLayout(mainLayout);

    //setWindowFlags(Qt::FramelessWindowHint);
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
    if (!change){
        sfLeftTop->setMinimumSize(width() / 2, height() / 2);
        sfLeftBottom->setMinimumSize(width() / 2, height() / 2);
        sfRightTop->setMinimumSize(width() / 2, height() / 2);
        sfRightBottom->setMinimumSize(width() / 2, height() / 2);
        change = true;
    }
    else
        change = false;
    qDebug()<< "resize event"; 
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->modifiers() == Qt::ControlModifier && e->key() == Qt::Key_Q)
        qApp->exit(0);
    if (e->modifiers() == Qt::ControlModifier && e->key() == Qt::Key_F){
        if(isMaximized()){
            change = true;
            sfLeftTop->setMinimumSize(1022 / 2, 766 / 2);
            sfLeftBottom->setMinimumSize(1022 / 2, 766 / 2);
            sfRightTop->setMinimumSize(1022 / 2, 766 / 2);
            sfRightBottom->setMinimumSize(1022 / 2, 766 / 2);
            showNormal();
            setFixedSize(1024, 768);
            qDebug()<<size();
        }
        else{
            change = false;
            setFixedSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
            showMaximized();
        }
    }
    QWidget::keyPressEvent(e);
}

void MainWindow::on_sfLeftTop_clicked()
{
}

void MainWindow::on_sfLeftBottom_clicked()
{
}

void MainWindow::on_sfRightTop_clicked()
{
}

void MainWindow::on_sfRightBottom_clicked()
{
}
