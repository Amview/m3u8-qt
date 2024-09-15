#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setStyleSheet(R"(
        MainWindow {
            background-color: #fbfbfb;
        }
        QWidget{
            color:#606266;
        }
        QPushButton#downBtn{
            height: 25px;
            background-color: #0f83ff;
            color: white;
            border-radius: 5px;
        }
        QPushButton#downBtn:disabled {
            background-color: #dcdcdc;
        }
        QPushButton#downBtn:hover {
            background-color: #7c7cf3;
        }
        QPushButton#playBtn {
            height: 25px;
            background-color: #fff;
            color: #606266;
            border-radius: 5px;
            border: 1px solid #dddfe5;
        }
        QPushButton#playBtn:hover {
            background-color: #fbfdff;
            border: 1px solid #c1c4cb;
        }
    )");
    w.setMinimumSize(500, 500);
    w.setWindowTitle("m3u8下载器");
    w.show();
    return a.exec();
}
