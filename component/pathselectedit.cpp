#include "pathselectedit.h"

PathSelectEdit::PathSelectEdit(QWidget *parent) : QLineEdit(parent){
    initUi();
}

PathSelectEdit::PathSelectEdit(const QString &s, QWidget *parent)
    : QLineEdit(s, parent) {
    initUi();
};

void PathSelectEdit::initUi() {
    this->setStyleSheet(R"(
        PathSelectEdit {
            background-color: #f4f4f5;
            width: 400px;
            height: 25px;
            padding-left: 5px;
            border-radius: 5px;
            color: #606266;
        }
    )");
}
