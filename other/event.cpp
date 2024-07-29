#include "QtGui/qevent.h"
#include "QtGui/qpainter.h"
#include "mainwindow.h"

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 抗锯齿，使边缘平滑
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white); // 设置背景颜色
    QRect rect = this->rect();
    painter.drawRoundedRect(rect, 12, 12); // 20是圆角的水平和垂直半径
}
void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        // 记录鼠标按下时的位置，用于计算后续的偏移量
        dragPosition = event->globalPosition().toPoint() - window()->frameGeometry().topLeft();
    }
    QWidget::mousePressEvent(event);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        // 处理Enter键按下事件
        emit pressEnter(); // 发出自定义信号，或者直接在这里执行你需要的操作
        // 可选：如果希望Enter键不起默认作用（如提交表单），可以调用ignore()防止进一步处理
        // event->ignore();
    }
    // 调用基类实现以保持其他按键功能
    // QLineEdit::keyPressEvent(event);
}



void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        // 当鼠标左键被按下并且正在移动时，开始窗口拖动
        auto newPos = event->globalPosition().toPoint() - dragPosition;
        window()->move(newPos);
    }
    QWidget::mouseMoveEvent(event);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::MouseButtonPress) {
        // 处理鼠标按下事件，记录点击位置
    } else if (event->type() == QEvent::MouseMove) {
        // 处理鼠标移动事件，移动窗口
    }

    return QWidget::eventFilter(obj, event);

}
