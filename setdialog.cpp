#include "setdialog.h"
#include "QtWidgets/qlabel.h"
#include "QtWidgets/qlineedit.h"

SetDialog::SetDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle(tr("设置"));
    resize(500, 500);
    setFixedSize(500, 500);
    infoLayout = new QGridLayout();
    QWidget *infoWidget = new QWidget();
    infoWidget->setLayout(infoLayout);
    // infoLayout->setContentsMargins(0, 0, 0, 0);
    // infoWidget->setMinimumHeight(500);
    infoWidget->setStyleSheet("border: solid 1px black;");


    QLineEdit *line = new QLineEdit();
    // infoLayout->addRow("下载地址", line);
    // infoLayout->addRow("下载地址", new QLabel("11"));
    infoLayout->addWidget(new QLabel("下载路径："), 0, 0, 1, 1, Qt::AlignTop);
    infoLayout->addWidget(line, 0, 1, 1, 1);
    setLayout(infoLayout);
}

SetDialog::~SetDialog()  {

}
