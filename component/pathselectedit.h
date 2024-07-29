#ifndef PATHSELECTEDIT_H
#define PATHSELECTEDIT_H

#include <QLineEdit>
#include <QFileDialog>
#include <QStandardPaths>
#include <QEnterEvent>

class PathSelectEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit PathSelectEdit(QWidget *parent = nullptr);
    explicit PathSelectEdit(const QString &, QWidget *parent = nullptr);
protected:
    void initUi();
    void enterEvent(QEnterEvent *event) override {
        // 当鼠标进入时改变指针形状
        setCursor(Qt::PointingHandCursor);
        QLineEdit::enterEvent(event);
    }
    void mousePressEvent(QMouseEvent *event) override {
        QLineEdit::mousePressEvent(event); // 调用基类的事件处理器
        selectPath();
    }
    void selectPath() {
        QStringList downloadDirs = QStandardPaths::standardLocations(QStandardPaths::DownloadLocation);
        QString dir = QFileDialog::getExistingDirectory(nullptr, "选择目录", downloadDirs.first(),
            QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        if (!dir.isEmpty()) {
            setText(dir);
        } else {
            setText(downloadDirs.first());
        }
    }
signals:
};

#endif // PATHSELECTEDIT_H
