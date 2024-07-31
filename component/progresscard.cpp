//
// Created by hua on 2024/7/31.
//

#include "progresscard.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
ProgressCard::ProgressCard(QWidget *parent) : QWidget(parent){
    QVBoxLayout *layout = new QVBoxLayout();
    setLayout(layout);
    this->setObjectName("card");
    this->setStyleSheet(R"(
        QWidget#card {
            border: 1px solid #dddfe5;
            background-color: #fff;
            border-radius: 5px;
            color: #606266;
            padding: 2px;
        }
        QProgressBar {
            border: none;
        }
        QPushButton {
            height: 25px;
            background-color: #fff;
            color: #606266;
            border-radius: 5px;
            border: 1px solid #dddfe5;
        }
        QPushButton:hover {
            background-color: #fbfdff;
            border: 1px solid #c1c4cb;
        }
    )");

    bar = new QProgressBar();

    layout->addWidget(bar);

    QHBoxLayout *infoLayout = new QHBoxLayout();
    QWidget *infoWidget = new QWidget();
    infoWidget->setLayout(infoLayout);

    downInfo = new QLabel();

    pauseBtn = new QPushButton("暂停");
    pauseBtn->setFixedWidth(50);
    infoLayout->addWidget(downInfo);
    infoLayout->addWidget(pauseBtn);
    layout->addWidget(infoWidget);
}
