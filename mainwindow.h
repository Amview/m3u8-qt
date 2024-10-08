#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "QtWidgets/qtextedit.h"
#include <QMainWindow>
#include <QProgressBar>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QThread>
#include <QLabel>
#include <iostream>
#include "component/pathselectedit.h"
#include "component/customlineedit.h"
#include "component/customtextedit.h"
#include "component/progresscard.h"
#include "framelesswindow/framelesswindow.h"
using namespace std;

class MainWindow : public CFramelessWindow
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
signals:
    void downloadProcessChanged(int i);
    void downloadFinish();

public slots:
    void showMessage(const string& text) {
        QMessageBox box;
        box.setText(QString::fromStdString(text));
        box.exec();
//        QMessageBox::information(nullptr, "", "请输入正确url");
    };

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
