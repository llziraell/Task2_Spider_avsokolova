#include "widget.h"

#include <QRandomGenerator>
#include <QKeyEvent>
#include <QPainter>
#include <QPoint>
#include <QRect>
#include <QTimer>
#include <QDebug>


Widget::Widget(QWidget *parent) : QWidget(parent) {
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
}


void Widget::UpdateSpiderPosition() {
    changeDirection();
    if (moveDirection_ == "Up") {
        spiderPosition_.setY(spiderPosition_.y() - shift);
    }
    if (moveDirection_ == "Down") {
        spiderPosition_.setY(spiderPosition_.y() + shift);
    }
    if (moveDirection_ == "Left") {
        spiderPosition_.setX(spiderPosition_.x() - shift);
    }
    if (moveDirection_ == "Right") {
        spiderPosition_.setX(spiderPosition_.x() + shift);
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
        //isDrawingWeb_ = true;
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
        DrawSpider(&painter);
    }
}

void Widget::DrawSpider(QPainter *painter) {
    int width = 5;
    int height = 5;

    painter->setBrush(QBrush(Qt::red, Qt::SolidPattern));
    painter->drawEllipse(spiderPosition_, width, height);
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



