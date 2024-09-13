#include "tools/utils.h"
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "mainwindow.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QComboBox>
#include <QSizePolicy>
#include <QLabel>
#include <thread>
#include <future>
#include <QTextEdit>
#include <QRadioButton>
#include <QLineEdit>
#include <QFileDialog>
#include "tools/utils.h"
#include "tools/m3u8.h"
#include <httplib.h>
#include <iostream>
#include <QProgressBar>
#include <QThread>
#include <QThreadPool>
#include <QEventLoop>
#include <QDesktopServices>
#include <mutex>
#include <condition_variable>
#include <QMessageBox>
#include <QStandardPaths>
#include "tools/threadpool.h"
#include "component/progresscard.h"
#include "component/pathselectedit.h"
#include "component/customtextedit.h"
//extern "C" {
//#include <libavformat/avformat.h>
//#include <libavcodec/avcodec.h>
//#include <libswscale/swscale.h>
//}
using namespace std;
mutex mtx;
condition_variable cv;
bool ready = true;
MainWindow::MainWindow(QWidget *parent)
    : CFramelessWindow(parent)
{
    QVBoxLayout *mainLay = new QVBoxLayout();
    mainLay->setContentsMargins(10, 0, 10, 10);
    QWidget *mainWidget = new QWidget();
    mainWidget->setLayout(mainLay);
    setCentralWidget(mainWidget);

#if defined(Q_OS_MACOS)
    QHBoxLayout *titleLayout = new QHBoxLayout();
    titleLayout->setContentsMargins(0, 5, 0, 0);
    QWidget *titleWidget = new QWidget();
    titleWidget->setLayout(titleLayout);
    QPushButton *githubBtn = new QPushButton();
    githubBtn->setFixedSize(20, 20);
    githubBtn->setIconSize(QSize(20, 20));
    githubBtn->setToolTip("https://github.com/Amview");
    githubBtn->setCursor(Qt::PointingHandCursor);
    githubBtn->setIcon(QIcon(":/img/github2.png"));
    githubBtn->setStyleSheet("border: none");
    titleLayout->addStretch(1);
    titleLayout->addWidget(githubBtn);
    connect(githubBtn, &QPushButton::clicked, []() {
        QDesktopServices::openUrl(QUrl(QString::fromStdString("https://github.com/Amview/m3u8-qt")));
    });
    mainLay->addWidget(titleWidget);
#endif

    urlEdit = new CustomTextEdit();
    urlEdit->setMaximumHeight(60);
    // 设置焦点策略为 Qt::NoFocus，这意味着文本编辑器不会自动获得焦点
    urlEdit->setFocusPolicy(Qt::ClickFocus);
    urlEdit->setText("https://bfikuncdn.com/20240714/TQoQPOhr/index.m3u8");
    urlEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // 设置
    QHBoxLayout *namel = new QHBoxLayout();
    namel->setContentsMargins(0,0,0,0);
    QWidget *nameWidget = new QWidget();
    nameWidget->setLayout(namel);
    // 文件名
    fileNameEdit = new CustomLineEdit();
    fileNameEdit->setText(QString::number(Utils::getCurrentTimestamp()));
    QLabel *nameLabel = new QLabel("文件名称：");
    nameLabel->setFixedWidth(80);
    namel->addWidget(nameLabel);
    namel->addWidget(fileNameEdit);

    QHBoxLayout *dLayout = new QHBoxLayout();
    dLayout->setContentsMargins(0,0,0,0);
    QWidget *dWidget = new QWidget();
    dWidget->setLayout(dLayout);

    // 下载位置
    pathEdit = new PathSelectEdit("/Volumes/DATA/download");
    pathEdit->setReadOnly(true);
    QLabel *pathLabel = new QLabel("下载位置：");
    pathLabel->setFixedWidth(80);
    dLayout->addWidget(pathLabel);
    dLayout->addWidget(pathEdit);

//    settingLay->addRow("下载位置：", pathEdit);
// 文件格式
//    QRadioButton *fs_option = new QRadioButton("ts");
//    fs_option->setChecked(true);
//    QRadioButton *mp4_option = new QRadioButton("mp4");
//    QHBoxLayout *typeLayout = new QHBoxLayout();
//    typeLayout->setContentsMargins(0,0,0,0);
//    QWidget *typeWidget = new QWidget();
//    typeLayout->addWidget(fs_option);
//    typeLayout->addWidget(mp4_option);
//    typeWidget->setLayout(typeLayout);
//    settingLay->addRow("文件格式：", typeWidget);

    card = new ProgressCard();
    card->hide();
    // urlEdit->setText("https://devstreaming-cdn.apple.com/videos/streami®ng/examples/img_bipbop_adv_example_fmp4/master.m3u8");
    downBtn = new QPushButton("下载");
    downBtn->setObjectName("downBtn");
    mainLay->addWidget(urlEdit);
    mainLay->addWidget(nameWidget);
    mainLay->addWidget(dWidget);
    mainLay->addStretch(1);
    mainLay->addWidget(card);
    mainLay->addWidget(downBtn);

    connect(card->pauseBtn, &QPushButton::clicked, [this]() {
       ready = !ready;
       if (!ready) {
           this->card->downInfo->setText("暂停");
           this->card->pauseBtn->setText("开始");
       } else {
           this->card->pauseBtn->setText("暂停");
       }
       cv.notify_all();
    });
    connect(downBtn, &QPushButton::clicked, this, &MainWindow::download1);
    connect(this, &MainWindow::downloadProcessChanged, this, [this](int i){
        this->card->bar->setValue(i);
        QString s = "正在下载：" + QString::number(i) + "/" + QString::number(this->card->bar->maximum());
        this->card->downInfo->setText(s);
    });
    connect(this, &MainWindow::downloadFinish, this, [this](){
        this->card->downInfo->setText("正在合并文件...");
        Utils::mergeFile(this->pathEdit->text().toStdString(), this->fileNameEdit->text().toStdString() + ".ts");
        this->card->downInfo->setText("下载完成...");
        QMessageBox::information(this, "", "下载完成");
    });
}

void MainWindow::download() {
    card->show();
    future<vector<string>> f = async(std::launch::async, [this](){
        M3u8 m3u8;
        std::vector<string> segmentList;
        string url = this->urlEdit->toPlainText().toStdString();
        std::vector<string> urlInfos = m3u8.readM3u8(url);
        Utils::printVector(urlInfos);
        if (m3u8.checkIsPlaySource(urlInfos)) {
            std::vector<string> playSourceList = m3u8.analysePlayList(urlInfos, Utils::analyseUrl(url));
            if (!playSourceList.empty()) {
                segmentList = m3u8.analysePlayList(playSourceList[0]);
            }
        } else {
            segmentList = m3u8.analysePlayList(urlInfos, Utils::analyseUrl(url));
        }
        return segmentList;
    });
    auto status = f.wait_for(chrono::seconds(10));

    if (status == future_status::timeout) {
        this->card->downInfo->setText("连接超时...");
        cout << "连接超时";
        return;
    } else if (status == future_status::ready) {
        this->card->downInfo->setText("请求成功...");
        vector<string> segmentList = f.get();
        if (!segmentList.empty()) {
            std::thread th([this, &segmentList]() {
                this->card->bar->setMaximum(2);
                this->card->bar->setMinimum(0);

                unique_lock<mutex> lock(mtx);
                for (int i = 0; i < segmentList.size(); ++i) {
                    cout << "开始下载：" << i << endl;
                    cv.wait(lock, [](){
                        return ready;
                    });
                    std::ostringstream formattedNumber;
                    formattedNumber << std::setw(3) << std::setfill('0') << i;
                    Utils::downloadTsFile(this->pathEdit->text().toStdString() + "/" + formattedNumber.str() + ".ts.temp", segmentList[i]);
                    emit downloadProcessChanged(i + 1);
                    if (i == 2) {
                        break;
                    }
                }
            });
//            th.join();
        }
    }
}

void MainWindow::download1()
{
    this->card->show();
    this->card->downInfo->setText("下载中...");
    std::thread th([this, &th](){
        M3u8 m3u8;
        string url = this->urlEdit->toPlainText().toStdString();
        std::vector<string> urlInfos = m3u8.readM3u8(url);
        std::vector<string> segmentList;
        if (m3u8.checkIsPlaySource(urlInfos)) {
            std::vector<string> playSourceList = m3u8.analysePlayList(urlInfos, Utils::analyseUrl(url));
            if (!playSourceList.empty()) {
                segmentList = m3u8.analysePlayList(playSourceList[0]);
            }
        } else {
            segmentList = m3u8.analysePlayList(urlInfos, Utils::analyseUrl(url));
        }
        if (!segmentList.empty()) {
            this->card->bar->setMaximum(segmentList.size());
            this->card->bar->setMinimum(0);
            unique_lock<mutex> lock(mtx);
            for (int i = 0; i < segmentList.size(); ++i) {
                cout << "开始下载：" << i << endl;
                std::ostringstream formattedNumber;
                formattedNumber << std::setw(3) << std::setfill('0') << i;
                Utils::downloadTsFile(this->pathEdit->text().toStdString() + "/" +
                    formattedNumber.str() + ".ts.temp", segmentList[i]);
                cv.wait(lock, [](){
                    return ready;
                });
                emit downloadProcessChanged(i + 1);
            }
            emit downloadFinish();
        }
    });
    th.detach();
}

MainWindow::~MainWindow() {}




