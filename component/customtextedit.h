//
// Created by hua on 2024/7/29.
//

#ifndef M3U8_CUSTOMTEXTEDIT_H
#define M3U8_CUSTOMTEXTEDIT_H
#include <QTextEdit>

class CustomTextEdit : public QTextEdit {
public:
    CustomTextEdit(QWidget *parent = nullptr);
    void initUi();
};


#endif //M3U8_CUSTOMTEXTEDIT_H
