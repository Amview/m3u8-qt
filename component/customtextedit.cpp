//
// Created by hua on 2024/7/29.
//

#include "customtextedit.h"
CustomTextEdit::CustomTextEdit(QWidget *parent) : QTextEdit(parent) {
    this->initUi();
}

void CustomTextEdit::initUi() {
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    this->setMinimumHeight(25);
    this->setStyleSheet(R"(
        QTextEdit {
            border: 1px solid #dddfe5;
            background-color: #fff;
            border-radius: 5px;
            color: #606266;
            padding: 2px;
        }
        QTextEdit:hover {
            background-color: #fbfdff;
            border: 1px solid #c1c4cb;
        }
        QTextEdit:focus {
            border: 1px solid #5b5bf1;
        }
    )");
}