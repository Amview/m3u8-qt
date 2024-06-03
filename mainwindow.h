#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "QLineEdit"
#include "QPushButton"
#include <QMainWindow>
#include <QtNetwork/QNetworkAccessManager>
#include <QUrl>
#include <QtNetwork/QNetworkReply>
#include <QTextBrowser>
#include "QtGui/qevent.h"
#include "QtWidgets/qformlayout.h"
#include "QtWidgets/qlistwidget.h"
#include "m3u8.h"
#include "QTableWidget"
#include <QFile>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QUrl url;
    M3u8 *m3u8;
public:
    QLineEdit *search;
    QPushButton *settingsBtn;
    QPushButton *aboutBtn;
    QPushButton *submit;
    QTextBrowser *textBrowre;
    QTableWidget *table;
    QGridLayout *gridLayout;
    QFormLayout *infoLayout;
    QListWidget *listWidget;
    std::map<QString, QString> myMap;
    QPushButton *tbn_min;
    QPushButton *tbn_close;
    QPushButton *tbn_max;
    QPushButton *download;
    QPoint dragPosition; // 存储鼠标按下时相对于窗口左上角的偏移量
    std::vector<QPushButton*> tmpVector;
    std::uintptr_t addr_p1;

    QNetworkAccessManager manager;
    QNetworkReply *reply;
    QNetworkRequest request;

    QString baseUrl;
    QStringList dataList;
public:
    MainWindow(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void initData();
    void initUi();
    void initConnect();
    void disPlayInfo(QStringList &list);


    ~MainWindow();
signals:
    void pressEnter();
public slots:
    void setValue();
}

;
#endif // MAINWINDOW_H
