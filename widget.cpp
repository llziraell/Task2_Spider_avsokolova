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
#include <QObject>

Widget::Widget(QWidget *parent) : QWidget(parent) {

    //QString currentPath = QDir::currentPath();
    //QString parentPath = currentPath + "/Spider_image.png";
    //spiderImage_ = QPixmap(parentPath);
    QString parentPath = "/Users/llziraell/Desktop/Spider_image.png";
    spiderImage_ = QPixmap(parentPath);

    windowRect_ = rect();
    SetSpiderPosition();

    spiderMoveTimer_ = new QTimer(this);
    spiderBoostTimer_ = new QTimer(this);
    AddToTimerInterval(100);

    shift = 10;

    connect(spiderBoostTimer_, &QTimer::timeout, [this]{ shift*= 1.2; });
    connect(spiderMoveTimer_, &QTimer::timeout, this, &Widget::UpdateSpiderPosition);
}

Widget::~Widget() {
}

void Widget::changeDirection() {
    if (spiderPosition_.x() >= windowRect_.width() - 50) {
        moveDirection_ = "Left";
        spiderPosition_.setX(spiderPosition_.x() - 50);
        rotate = 180;
    }
    if (spiderPosition_.x() < 0) {
        moveDirection_ = "Right";
        spiderPosition_.setX(spiderPosition_.x() + 50);
        rotate = 180;
    }
    if (spiderPosition_.y() >= windowRect_.height() - 50) {
        moveDirection_ = "Up";
        spiderPosition_.setY(spiderPosition_.y() - 50);
        rotate = 180;
    }
    if (spiderPosition_.y() < 0) {
        moveDirection_ = "Down";
        spiderPosition_.setY(spiderPosition_.y() + 50);
        rotate = 180;
    }
}

void Widget::UpdateSpiderPosition() {
    rotate = 0;

    QPoint newWebPoint = QPoint(spiderPosition_.x()+25, spiderPosition_.y()+25);
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
        int width = this->width();
        int height = this->height();

        int x = 0, y = 0;
        x = QRandomGenerator::global()->bounded(width);
        y = QRandomGenerator::global()->bounded(height);

        spiderPosition_.setX(x);
        spiderPosition_.setY(y);

        QPoint newWebPoint = QPoint(x+ 25, y+25);

        webVector.append(newWebPoint);
}

void Widget::keyPressEvent(QKeyEvent *event) {
    spiderMoveTimer_->start();
    if (event->key()) {
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
     spiderBoostTimer_->start(50);
    }
}

void Widget::keyReleaseEvent(QKeyEvent *event) {
    Q_UNUSED(event);
    spiderBoostTimer_->stop();
    shift = 10;
}

void Widget::resizeEvent(QResizeEvent *event) {
    Q_UNUSED(event);
    windowRect_ = rect();
}

void Widget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
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

void Widget::DrawWeb(QPainter *painter) {
    QPen pen(Qt::black);
    pen.setWidth(5);
    painter->setPen(pen);
    for (const auto& webPoint : webVector) {
        painter->drawPoint(webPoint);
    }
}

void Widget::AddToTimerInterval(int milliseconds) {
    int minInterval = 100;
    int maxInterval = 1000;

    int newInterval = spiderMoveTimer_->interval() + milliseconds;

    newInterval = qBound(minInterval, newInterval, maxInterval);

    spiderMoveTimer_->setInterval(newInterval);
}



