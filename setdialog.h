#ifndef SETDIALOG_H
#define SETDIALOG_H

#include "QtWidgets/qformlayout.h"
#include <QDialog>
#include <QObject>
class SetDialog : public QDialog
{
    Q_OBJECT
public:
    SetDialog(QWidget *parent = nullptr);

    QGridLayout *infoLayout;
    ~SetDialog();
};

#endif // SETDIALOG_H
