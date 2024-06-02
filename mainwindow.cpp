#include "mainwindow.h"
#include "QVBoxLayout"
#include "QLineEdit"
#include "QPushButton"
#include "QHBoxLayout"
#include "QtCore/qcoreevent.h"
#include "iostream"
#include "QJsonDocument"
#include "QtNetwork/QNetworkAccessManager"
#include "QtNetwork/QNetworkReply"
#include "qpainter.h"
#include <QMouseEvent>
#include <QListWidget>
#include <QSplitter>
#include <QFormLayout>
#include <QLabel>

#include "m3u8.h"
// using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initData();
    initUi();
    initConnect();
    // reply = Q_NULLPTR;
}

MainWindow::~MainWindow() {

}


void MainWindow::setValue() {
    QString url = search->text();
    m3u8 = new M3u8(url);

}

