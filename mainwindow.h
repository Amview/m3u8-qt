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
#include "component/customlineedit.h"
#include "component/customtextedit.h"
#include "component/progresscard.h"
using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    // 下载状态
    enum DownloadState {
        DOWNLOAD_RUNNING,
        DOWNLOAD_PAUSED
    };


public:
    CustomTextEdit *urlEdit;
    PathSelectEdit *pathEdit;
    CustomLineEdit *fileNameEdit;
    QPushButton *downBtn;
    QPushButton *playBtn;
    ProgressCard *card;
    QLabel *downInfo;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void download();
    void download1();
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
