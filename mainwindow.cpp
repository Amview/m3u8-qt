#include "utils.h"
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
#include "utils.h"
#include "m3u8.h"
#include <httplib.h>
#include <iostream>
#include <QProgressBar>
#include <QThread>
#include <QThreadPool>
#include <QEventLoop>
#include <QMessageBox>
#include <QStandardPaths>
#include "component/pathselectedit.h"
extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
}
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    QVBoxLayout *mainLay = new QVBoxLayout();
    mainLay->setContentsMargins(5, 5, 5, 5);
    QWidget *mainWidget = new QWidget();
    mainWidget->setLayout(mainLay);
    setCentralWidget(mainWidget);

    bar = new QProgressBar();
    bar->hide();

    QHBoxLayout *inputLay = new QHBoxLayout();
    QWidget *inputWidget = new QWidget();
    inputWidget->setLayout(inputLay);

    QFormLayout *settingLay = new QFormLayout();
    settingLay->setFormAlignment(Qt::AlignLeft);
    QWidget *settingWidget = new QWidget();
    settingWidget->setLayout(settingLay);

    fileNameEdit = new QLineEdit();
    fileNameEdit->setStyleSheet(R"(
        width: 400px;
        height: 25px;
        padding-left: 5px;
        border-radius: 5px;
        color: #606266;
        background-color: #fff;
    )");
    fileNameEdit->setText(QString::number(Utils::getCurrentTimestamp()));
    settingLay->addRow("文件名称：", fileNameEdit);
    pathEdit = new PathSelectEdit("/Volumes/optane/download");
    pathEdit->setReadOnly(true);
    pathEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    settingLay->addRow("下载位置：", pathEdit);
    QRadioButton *fs_option = new QRadioButton("ts");
    fs_option->setChecked(true);
    QRadioButton *mp4_option = new QRadioButton("mp4");
    QHBoxLayout *typeLayout = new QHBoxLayout();
    typeLayout->setContentsMargins(0,0,0,0);
    QWidget *typeWidget = new QWidget();
    typeLayout->addWidget(fs_option);
    typeLayout->addWidget(mp4_option);
    typeWidget->setLayout(typeLayout);
    settingLay->addRow("文件格式：", typeWidget);

    urlEdit = new QTextEdit();
    urlEdit->setMaximumHeight(60);
    // 设置焦点策略为 Qt::NoFocus，这意味着文本编辑器不会自动获得焦点
    urlEdit->setFocusPolicy(Qt::ClickFocus);
    urlEdit->setText("https://bfikuncdn.com/20240714/TQoQPOhr/index.m3u8");
    urlEdit->setStyleSheet(R"(
        width: 350px;
        padding: 2px;
    )");
    urlEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // urlEdit->setText("https://devstreaming-cdn.apple.com/videos/streaming/examples/img_bipbop_adv_example_fmp4/master.m3u8");
    downBtn = new QPushButton("下载");
    downBtn->setObjectName("downBtn");
    playBtn = new QPushButton("播放");
    playBtn->setObjectName("playBtn");
    inputLay->addWidget(urlEdit);

    downInfo = new QLabel("");

    mainLay->addWidget(inputWidget);
    mainLay->addWidget(settingWidget, 1);
    mainLay->addStretch(1);
    mainLay->addWidget(bar);
    mainLay->addWidget(downInfo);
    mainLay->addWidget(playBtn);
    mainLay->addWidget(downBtn);

    connect(downBtn, &QPushButton::clicked, this, &MainWindow::download);
    connect(this, &MainWindow::downloadProcessChanged, this, [this](int i){
        this->bar->setValue(i);
        QString s = "正在下载：" + QString::number(i) + "/" + QString::number(this->bar->maximum());
        this->downInfo->setText(s);
    });
    connect(this, &MainWindow::downloadFinish, this, [this](){
        this->downInfo->setText("正在合并文件...");
        Utils::meargeFile(this->pathEdit->text().toStdString(), this->fileNameEdit->text().toStdString() + ".ts");
        this->downInfo->setText("下载完成...");
        QMessageBox::information(this, "", "下载完成");
    });
}

void MainWindow::download()
{
    this->bar->show();
    this->bar->setValue(0);
    this->downInfo->setText("");
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
            bar->setMaximum(segmentList.size());
            bar->setMinimum(0);
            for (int i = 0; i < segmentList.size(); ++i) {
                cout << "开始下载：" << i << endl;
                std::ostringstream formattedNumber;
                formattedNumber << std::setw(3) << std::setfill('0') << i;
                Utils::downloadTsFile(this->pathEdit->text().toStdString() + "/" + formattedNumber.str() + ".ts.temp", segmentList[i]);
                emit downloadProcessChanged(i + 1);
                // if (i == 10) {
                //     break;
                // }
            }
            emit downloadFinish();
        }
    });
    th.detach();
}

MainWindow::~MainWindow() {}




