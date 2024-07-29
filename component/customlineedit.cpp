//
// Created by hua on 2024/7/29.
//

#include "customlineedit.h"

CustomLineEdit::CustomLineEdit(QWidget *parent) : QLineEdit(parent) {
    this->initUi();
}

void CustomLineEdit::initUi() {
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    this->setMinimumHeight(25);
    this->setStyleSheet(R"(
        QLineEdit {
            border: 1px solid #dddfe5;
            background-color: #fff;
            padding-left: 5px;
            border-radius: 5px;
            color: #606266;
        }
        QLineEdit:hover {
            background-color: #fbfdff;
            border: 1px solid #c1c4cb;
        }
        QLineEdit:focus {
            border: 1px solid #5b5bf1;
        }
    )");
}
