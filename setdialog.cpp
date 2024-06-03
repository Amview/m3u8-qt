#include "setdialog.h"
#include "QtCore/qjsondocument.h"
#include "QtWidgets/qlabel.h"
#include "QtWidgets/qlineedit.h"
#include "QFile"
#include "QJsonObject"

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

    QLineEdit *downloadPathEdit = new QLineEdit();
    // infoLayout->addRow("下载地址", line);
    // infoLayout->addRow("下载地址", new QLabel("11"));
    downloadPathEdit->setStyleSheet(
        "QLineEdit {"
        "background-color: #F5F5F5;height:30px;"
        "color: gray;border-radius:5px;padding: 5px 8px 5px 8px;"
        "}"
        "QLineEdit:focus {"
        "   border: 2px solid #87CEFA;" // 获得焦点时边框颜色
        "}"
        );
    QLabel *l = new QLabel("下载路径：");
    l->setStyleSheet("height:30px;");
    infoLayout->addWidget(l, 0, 0, 1, 1, Qt::AlignTop | Qt::AlignVCenter);
    infoLayout->addWidget(downloadPathEdit, 0, 1, 1, 1, Qt::AlignTop | Qt::AlignVCenter);
    setLayout(infoLayout);

    QFile setF("settings.json");
    setF.open(QIODevice::ReadWrite | QIODevice::Text);
    qDebug() << setF.isOpen();
    if (setF.isOpen()) {
        qDebug() << setF.size();
        if(setF.size() != 0) {
            QByteArray dataArray = setF.readAll();
            qDebug() << dataArray;
            QJsonParseError jsonError;
            QJsonDocument document = QJsonDocument::fromJson(dataArray, &jsonError);
            if (!document.isNull() && (QJsonParseError::NoError == jsonError.error)) {
                if (document.isObject()) {
                    QJsonObject obj = document.object();
                    QJsonValue value = obj.take("downloadPath");
                    downloadPathEdit->setText(value.toString());
                    qDebug() << obj;
                }
            }
        }
    }
    setF.close();
}

SetDialog::~SetDialog()  {

}
