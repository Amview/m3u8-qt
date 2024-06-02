#include "QtCore/qeventloop.h"
#include "QtGui/qevent.h"
#include "QtWidgets/qlabel.h"
#include "QtWidgets/qsplitter.h"
#include "buttoncellwidget.h"
#include "filedownload.h"
#include "mainwindow.h"
#include "QHeaderView"
#include "request.h"
#include "setdialog.h"
#include <future>
#include <QMessageBox>

void MainWindow::initData() {
    myMap["PROGRAM-ID"] = "标签";
    myMap["BANDWIDTH"] = "带宽";
    myMap["RESOLUTION"] = "分辨率";
}

void MainWindow::initUi() {

    setWindowFlag(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setStyleSheet("background-color: rgb(255, 255, 255);"
                        "border-bottom: solid 1px gray;"
                        "border-radius: 10px;padding:0;margin:0"); // 10px 是圆角的半径，可以根据需要调整

    QPalette palette;
    //设置主窗口背景颜色
    palette.setColor(QPalette::Window,QColor(255, 255, 255));
    this->setPalette(palette);

    // 主布局
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(0, 0, 0, 0);
    QWidget *mainWidget = new QWidget();
    mainWidget->setStyleSheet("margin:0");
    mainWidget->setLayout(mainLayout);
    // 标题栏
    QHBoxLayout *barLay = new QHBoxLayout();
    barLay->setSpacing(8);
    barLay->setContentsMargins(8, 8, 8, 8);
    barLay->setAlignment(Qt::AlignLeft);
    QWidget *barWidget = new QWidget();
    barWidget->update();
    barWidget->setLayout(barLay);
    // 主体布局
    QVBoxLayout *bodyLayout = new QVBoxLayout();
    QWidget *bodyWidget = new QWidget();
    bodyWidget->setLayout(bodyLayout);
    // 搜索框
    QHBoxLayout *searchLay = new QHBoxLayout();
    searchLay->setAlignment(Qt::AlignTop);
    QWidget *searchWidget = new QWidget();
    searchWidget->setLayout(searchLay);
    // 分栏
    QSplitter *splitter = new QSplitter(Qt::Orientation::Horizontal, this);
    // 信息
    infoLayout = new QFormLayout();
    QWidget *infoWidget = new QWidget();
    infoWidget->setLayout(infoLayout);
    infoWidget->setMinimumWidth(200);
    infoWidget->setMinimumHeight(500);
    // 表格
    table = new QTableWidget();
    // 设置表格所有单元格的文本水平居中和垂直居中
    table->setStyleSheet("QTableWidgetItem { text-align: center; }");
    table->resizeColumnsToContents();

    submit = new QPushButton();
    submit->setText("下载");
    submit->setStyleSheet("background-color: rgb(67, 151, 247);width:30px;"
                          "color: white;border-radius:5px;padding: 5px 8px 5px 8px;");

    gridLayout = new QGridLayout(this);
    QWidget *gridWidget = new QWidget();
    gridWidget->setLayout(gridLayout);

    listWidget = new QListWidget();
    listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tbn_min = new QPushButton();
    tbn_min->setStyleSheet("height:12px;width:12px;border-radius: 6px;background-color: #ed6a5d;");
    tbn_min->setText("");
    tbn_max = new QPushButton();
    tbn_max->setStyleSheet("height:12px;width:12px;border-radius: 6px;background-color: #f4bf4f;");
    tbn_max->setText("");
    tbn_close = new QPushButton();
    tbn_close->setStyleSheet("height:12px;width:12px;border-radius: 6px;background-color: #61c654;");
    tbn_close->setText("");

    download = new QPushButton("下载");
    download->setStyleSheet("background-color: rgb(67, 151, 247);width:30px;"
                          "color: white;border-radius:5px;padding: 5px 8px 5px 8px;");

    // 安装拖动事件处理器
    // barLay->parentWidget()->installEventFilter(this); // 确保父窗口安装了事件过滤器
    // 实现事件过滤器或重写鼠标事件以支持拖动

    search = new QLineEdit();
    // search->setStyleSheet("background-color: yellow;");

    search->setPlaceholderText("搜索");
    search->setFocus();
    search->setText("https://v.cdnlz21.com/20240516/332_8de22974/index.m3u8");
    // search->setStyleSheet("background-color: rgb(236, 236, 236);");
    // search->setFixedWidth(600);
    // search->clearFocus();
    // background-color: rgb(236, 236, 236);
    search->setStyleSheet(
        "QLineEdit {"
        "background-color: #F5F5F5;height:30px;"
        "color: gray;border-radius:5px;padding: 5px 8px 5px 8px;"
        "}"
        "QLineEdit:focus {"
        "   border: 2px solid #87CEFA;" // 获得焦点时边框颜色
        "}"
        );


    textBrowre = new QTextBrowser();

    mainLayout->addWidget(barWidget);
    mainLayout->addWidget(bodyWidget);
    mainLayout->addStretch(1);

    barLay->addWidget(tbn_min);
    barLay->addWidget(tbn_max);
    barLay->addWidget(tbn_close);
    barLay->addStretch(1);

    bodyLayout->addWidget(searchWidget);
    bodyLayout->addStretch(1);
    bodyLayout->addWidget(splitter);
    bodyLayout->addWidget(download);

    searchLay->addWidget(search);
    // searchLay->addWidget(submit);

    splitter->addWidget(infoWidget);
    splitter->addWidget(listWidget);
    setCentralWidget(mainWidget);

}

void MainWindow::initConnect() {
    // 连接按钮的 clicked 信号到槽函数
    // QObject::connect(submit, SIGNAL(clicked(bool)), this, SLOT(setValue()));
    QObject::connect(this, &MainWindow::pressEnter, [&](){
        QString url = search->text();
        m3u8 = new M3u8(url);
        bool isBack = m3u8->checkIsBack();
        if (isBack) {
            QStringList list = QString::fromUtf8(m3u8->data).split("\n");
            disPlayInfo(list);
            QString url1 = m3u8->baseUrl + "/" + m3u8->playUrls[0];
            m3u8 = new M3u8(url1);
            qDebug() << "url1" << url1;
        }
        // qDebug() << m3u8->data;
        QStringList dataList = QString::fromUtf8(m3u8->data).split("\n");
        this->dataList = dataList;
        table->setRowCount(m3u8->countUrls());
        table->setColumnCount(2);
        table->setHorizontalHeaderLabels({"地址", "时长"});
        // 设置所有列的段落伸展模式为Stretch，使其填充表格
        // for (int i = 0; i < table->columnCount(); ++i) {
        //     table->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
        // }
        int rowCount = 0;
        QTableWidgetItem *widgetItem;
        for (int i = 0; i < dataList.size(); ++i) {
            QString item = dataList[i];
            if (item.trimmed().startsWith("#EXTINF")) {
                QStringList itemInfoList = item.split(":");
                QListWidgetItem *widgetItem = new QListWidgetItem();
                QString item = dataList[i+1];
                if (!item.isEmpty()) {
                    widgetItem->setText(item);
                    ++rowCount;
                }
                listWidget->addItem(widgetItem);
            }
        }
    });
    QObject::connect(download, &QPushButton::clicked, [this](){
        // FileDownload fileDownload;
        // for (int i = 0; i < 2; ++i) {
        //     QString fullPath = this->m3u8->baseUrl + "/" + this->m3u8->playUrls[i];
        //     qDebug() << "下载地址" << fullPath;
        //     fileDownload.download(fullPath);
        // }

        SetDialog setDialog(this);
        setDialog.exec();
    });

    QObject::connect(tbn_close, &QPushButton::clicked, [this](){
        close();
    });
    QObject::connect(tbn_max, &QPushButton::clicked, [this](){
        if (isMaximized()) {
            showNormal();
        } else {
            showMaximized();
        }
    });
    QObject::connect(tbn_min, &QPushButton::clicked, [this](){
        showMinimized();
    });
}

void MainWindow::disPlayInfo(QStringList &list) {
    for (int i = 0; i < list.size(); ++i) {
        QString item = list[i];
        QStringList infoList = item.split(":");
        if (infoList.length() == 2) {
            QStringList infoList1 = infoList[1].split(",");
            for (int i = 0; i < infoList1.size(); ++i) {
                QString property = infoList1[i];
                // qDebug() << property;
                QStringList properties = property.split("=");
                if (properties.length() == 2) {
                    QString s = myMap[properties[0]];
                    if (!s.isEmpty()) {
                        infoLayout->addRow((s), new QLabel(properties[1]));
                    } else {
                        infoLayout->addRow((properties[0]), new QLabel(properties[1]));
                    }
                    // qDebug() << s;
                }
            }
        }
    }
}

