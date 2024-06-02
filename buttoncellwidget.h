#ifndef BUTTONCELLWIDGET_H
#define BUTTONCELLWIDGET_H

#include "QtWidgets/qpushbutton.h"
#include "QtWidgets/qwidget.h"
class ButtonCellWidget : public QWidget
{
    Q_OBJECT
public:


    explicit ButtonCellWidget(QWidget *parent = nullptr) : QWidget(parent) {
        QPushButton *button = new QPushButton("点击我", this);
        // 连接按钮的clicked信号到槽函数
        // connect(button, &QPushButton::clicked, this, &ButtonCellWidget::onButtonClick);
        // 可以调整按钮的位置和大小，或者使用布局管理器来自动管理
    }


signals:
    void buttonClicked(int row, int column); // 自定义信号，用于通知按钮被点击

private slots:
    // void onButtonClick() {
    //     emit buttonClicked(row(), column()); // 发送按钮点击信号，并携带所在行列信息
    // }

};

#endif // BUTTONCELLWIDGET_H
