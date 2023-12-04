#include "widget.h"

#include <QRandomGenerator>
#include <QKeyEvent>
#include <QPainter>
#include <QPoint>
#include <QRect>
#include <QTimer>


Widget::Widget(QWidget *parent) : QWidget(parent) {
    windowRect_ = rect();
    SetSpiderPosition();

    spiderMoveTimer_ = new QTimer(this);
    AddToTimerInterval(100);

    // Cоединяем сигнал таймера о том, что время (интервал) прошло со слотом
    // изменения позиции фигуры
    connect(spiderMoveTimer_, &QTimer::timeout, this, &Widget::UpdateSpiderPosition);
}

Widget::~Widget() {}

void Widget::UpdateSpiderPosition() {
    if (mpveDirection_ == "Up") {
        spiderPosition_.setY(spiderPosition_.y() - shift);
    }
    if (mpveDirection_ == "Down") {
        spiderPosition_.setY(spiderPosition_.y() + shift);
    }
    if (mpveDirection_ == "Left") {
        spiderPosition_.setX(spiderPosition_.x() - shift);
    }
    if (mpveDirection_ == "Right") {
        spiderPosition_.setX(spiderPosition_.x() + shift);
    }
    repaint();
}



void Widget::SetSpiderPosition() {
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
    if (event->key() == Qt::Key_Up) {
            mpveDirection_ = "Up";
    }
    if (event->key() == Qt::Key_Down) {
            mpveDirection_ = "Down";
    }
    if (event->key() == Qt::Key_Left) {
        mpveDirection_ = "Left";
    }
    if (event->key() == Qt::Key_Right) {
        mpveDirection_ = "Right";
    }
    //timer->start(50);
}

void Widget::resizeEvent(QResizeEvent *event) {
    Q_UNUSED(event);
    windowRect_ = rect();
}

void Widget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    // Создаем экземпляр класса для низкоуровневого рисования
    QPainter painter(this);
    spiderMoveTimer_->start();
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



