//
// Created by hua on 2024/7/31.
//

#ifndef M3U8_PROGRESSCARD_H
#define M3U8_PROGRESSCARD_H
#include <QWidget>
#include <QProgressBar>
#include <QLabel>
#include <QPushButton>

class ProgressCard : public QWidget {

public:
    QProgressBar *bar;
    QLabel *downInfo;
    QPushButton *pauseBtn;
    explicit ProgressCard(QWidget *parent = nullptr);
};


#endif //M3U8_PROGRESSCARD_H
