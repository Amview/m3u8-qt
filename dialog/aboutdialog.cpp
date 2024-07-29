#include "aboutdialog.h"
#include "qlabel.h"
#include "qpushbutton.h"
#include "qdesktopservices.h"

AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle(tr("关于"));
    resize(500, 500);
    setFixedSize(500, 300);

    vlayout = new QVBoxLayout();
    vlayout->setAlignment(Qt::AlignCenter | Qt::AlignTop);

    QLabel *logoLab = new QLabel;
    QPixmap pixmap(":/img/logo.png");
    logoLab->setPixmap(pixmap);
    vlayout->addWidget(logoLab);

    QLabel *githubLab = new QLabel;
    QPixmap originalPixmap(":/img/github.png");
    QPixmap scaledPixmap = originalPixmap.scaled(30, 30,
                                                 Qt::KeepAspectRatio, Qt::SmoothTransformation);
    githubLab->setPixmap(scaledPixmap);

    QPushButton *githubBtn = new QPushButton();
    githubBtn->setIconSize(QSize(45, 45)); // 设置图标大小为48x48像素
    githubBtn->setIcon(QIcon(":/img/github.png"));
    githubBtn->setCursor(Qt::PointingHandCursor); // 在按钮初始化或适当的地方设置
    githubBtn->setStyleSheet("QPushButton:hover {"
                                "icon: url(:/img/github-hover.png); /* 鼠标悬停时的图标 */"
                                "cursor：pointer；"
                             "}");
    vlayout->addWidget(githubBtn, 1, Qt::AlignHCenter | Qt::AlignTop);
    // connect(githubLab, &QLabel::)
    setLayout(vlayout);

    connect(githubBtn, &QPushButton::clicked, [](){
        QUrl url("https://github.com/Amview/m3u8-qt");
        QDesktopServices::openUrl(url);
    });
}
