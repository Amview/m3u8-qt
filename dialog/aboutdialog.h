#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include "qboxlayout.h"
#include <QDialog>

class AboutDialog : public QDialog
{
public:

    QVBoxLayout *vlayout;
    AboutDialog(QWidget *parent = nullptr);
};

#endif // ABOUTDIALOG_H
