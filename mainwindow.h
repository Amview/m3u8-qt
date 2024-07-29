#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "QtWidgets/qtextedit.h"
#include <QMainWindow>
#include <QProgressBar>
#include <QLineEdit>
#include <QPushButton>
#include <QThread>
#include <QLabel>
#include <iostream>
#include "component/pathselectedit.h"
using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QTextEdit *urlEdit;
    PathSelectEdit *pathEdit;
    QLineEdit *fileNameEdit;
    QPushButton *downBtn;
    QPushButton *playBtn;
    QProgressBar *bar;
    QLabel *downInfo;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void download();
signals:
    void downloadProcessChanged(int i);
    void downloadFinish();

};

class UpdateProcess : public QThread {
    Q_OBJECT
public:
    QProgressBar* bar;
    int i;
    UpdateProcess(QProgressBar* bar, int i) {
        this->bar = bar;
        this->i = i;
    }
signals:
    void progress(int p);

protected:
    void run() {
        cout << 1 << endl;
        this->bar->setValue(i);
    }
};
#endif // MAINWINDOW_H
