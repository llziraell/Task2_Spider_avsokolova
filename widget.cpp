#include "widget.h"

#include <QRandomGenerator>
#include <QKeyEvent>
#include <QPainter>
#include <QPoint>
#include <QRect>
#include <QTimer>
#include <QDebug>
#include <QPixmap>
#include <QVector>
#include <QTransform>
#include <QString>

Widget::Widget(QWidget *parent) : QWidget(parent) {

    QString currentPath = QDir::currentPath();
    QDir parentDir(currentPath);
    parentDir.cdUp();
    QString parentPath = parentDir.absolutePath();
    spiderImage_ = QPixmap(parentPath + "Task2_Spider_avsokolova" + "/Spider_image.png");


    windowRect_ = rect();
    SetSpiderPosition();

    spiderMoveTimer_ = new QTimer(this);
    spiderBoostTimer_ = new QTimer(this);
    AddToTimerInterval(100);

    // Cоединяем сигнал таймера о том, что время (интервал) прошло со слотом
    // изменения позиции фигуры
    connect(spiderMoveTimer_, &QTimer::timeout, this, &Widget::UpdateSpiderPosition);
}

Widget::~Widget() {}

void Widget::changeDirection() {
    if (spiderPosition_.x() >= windowRect_.width() - 1) {
        moveDirection_ = "Left";
    }
    if (spiderPosition_.x() <= 0) {
        moveDirection_ = "Right";
    }
    if (spiderPosition_.y() >= windowRect_.height() -1) {
        moveDirection_ = "Up";
    }
    if (spiderPosition_.y() <= 0) {
        moveDirection_ = "Down";
    }
    rotate = 180;
    //spiderImage_.transformed(QTransform().rotate(90));
    //repaint();

    //spiderImage_.transformed(QTransform().rotate(180));
}


void Widget::UpdateSpiderPosition() {
    rotate = 0;

    QPoint newWebPoint = QPoint(spiderPosition_.x(), spiderPosition_.y());
    webVector.append(newWebPoint);

    changeDirection();
    if (moveDirection_ == "Up") {
        spiderPosition_.setY(spiderPosition_.y() - shift);
    }
    if (moveDirection_ == "Down") {
        spiderPosition_.setY(spiderPosition_.y() + shift);
        rotate = 180;
    }
    if (moveDirection_ == "Left") {
        spiderPosition_.setX(spiderPosition_.x() - shift);
        rotate = -90;
    }
    if (moveDirection_ == "Right") {
        spiderPosition_.setX(spiderPosition_.x() + shift);
        rotate = 90;
    }
    repaint();
}



void Widget::SetSpiderPosition() {
        //spiderMoveTimer_->start();
        int width = this->width();
        int height = this->height();

        int x = 0, y = 0;
        x = QRandomGenerator::global()->bounded(width);
        y = QRandomGenerator::global()->bounded(height);

        spiderPosition_.setX(x);
        spiderPosition_.setY(y);

        QPoint newWebPoint = QPoint(x, y);

        webVector.append(newWebPoint);
}

void Widget::keyPressEvent(QKeyEvent *event) {
    spiderMoveTimer_->start();
    if (event->key() == Qt::Key_Up) {
            moveDirection_ = "Up";
    }
    if (event->key() == Qt::Key_Down) {
            moveDirection_ = "Down";
    }
    if (event->key() == Qt::Key_Left) {
        moveDirection_ = "Left";
    }
    if (event->key() == Qt::Key_Right) {
        moveDirection_ = "Right";
    }
    if (event->key() == Qt::Key_Space) {
    spiderMoveTimer_->stop();
    }
}

void Widget::keyReleaseEvent(QKeyEvent *event) {
    Q_UNUSED(event);
//    if (event->isAutoRepeat()){
//        spiderBoostTimer_->start();
//        qDebug() << shift;
//    }

//        if (spiderBoostTimer_) {
//            spiderBoostTimer_->stop();
//            shift*=2;
//            delete spiderMoveTimer_;
//            spiderMoveTimer_ = nullptr;
//        }

}

void Widget::resizeEvent(QResizeEvent *event) {
    Q_UNUSED(event);
    windowRect_ = rect();
}

void Widget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    // Создаем экземпляр класса для низкоуровневого рисования
    QPainter painter(this);
// spiderMoveTimer_->start();

    painter.setRenderHint(QPainter::Antialiasing);  // Добавляем сглаживание
    if (spiderMoveTimer_->isActive()) {
        DrawWeb(&painter);
        DrawSpider(&painter);
    }
}

void Widget::DrawSpider(QPainter *painter) {
    int width = 50;
    int height = 50;
    QRect rect(spiderPosition_.x(), spiderPosition_.y(), width, height);
    QPixmap rotatedPixmap = spiderImage_.transformed(QTransform().rotate(rotate));
    painter->drawPixmap(rect, rotatedPixmap);
}

//сделать его непрозрачным)))

void Widget::DrawWeb(QPainter *painter) {
    QPen pen(Qt::red); // Красный цвет
    pen.setWidth(5); // Устанавливаем толщину точки

    // Устанавливаем созданное перо для рисования
    painter->setPen(pen);

    for (const auto& webPoint : webVector) {
        painter->drawPoint(webPoint);
    }
}

void Widget::AddToTimerInterval(int milliseconds) {
    int minInterval = 100;
    int maxInterval = 1000;

    // Добавляем к текущему интервалу мс для дальнейшей проверки
    int newInterval = spiderMoveTimer_->interval() + milliseconds;

    // Не даем выйти значению интерваля за указанные границы [minInterval,
    // maxInterval]
    newInterval = qBound(minInterval, newInterval, maxInterval);

    spiderMoveTimer_->setInterval(newInterval);
}



