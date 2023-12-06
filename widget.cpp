#include "widget.h"

#include <QRandomGenerator>
#include <QKeyEvent>
#include <QPainter>
#include <QRect>
#include <QTimer>
#include <QDebug>
#include <QVector>
#include <QTransform>
#include <QObject>


Widget::Widget(QWidget *parent) : QWidget(parent) {

    windowRect_ = rect();
    //SetSpiderPosition();
    spider = new Spider(nullptr, 50, SetSpiderPosition(), 10);

    spiderMoveTimer_ = new QTimer(this);
    spiderBoostTimer_ = new QTimer(this);
    AddToTimerInterval(100);

    //spiderMoveTimer_->start(100);
    connect(spiderMoveTimer_, &QTimer::timeout, this, &Widget::UpdateSpiderPosition);
    connect(spider, &Spider::SetDirection, spider, &Spider::changeDirection);

    //connect(spiderBoostTimer_, &QTimer::timeout,spider,  &Spider::ChangeShift);
}

Widget::~Widget() {
}


QPoint Widget::SetSpiderPosition() {
        int width = this->width();
        int height = this->height();

        qDebug() << "111";

        int x = 0, y = 0;
        x = QRandomGenerator::global()->bounded(width);
        y = QRandomGenerator::global()->bounded(height);

        QPoint startSpiderPosition = QPoint(x, y);
        //QPoint newWebPoint = QPoint(x+ 25, y+25);
        //webVector.append(newWebPoint);
        return startSpiderPosition;
}

void Widget::UpdateSpiderPosition() {
        qDebug() << "ddd";
        emit spider->SetDirection(windowRect_);
//        spider->SetDirection();
        repaint();
}


//void Widget::keyReleaseEvent(QKeyEvent *event) {
//    Q_UNUSED(event);
//    spiderBoostTimer_->stop();
//    shift = 10;
//}

void Widget::resizeEvent(QResizeEvent *event) {
    Q_UNUSED(event);
    windowRect_ = rect();
}

void Widget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
        //DrawWeb(&painter);
        spider->DrawSpider(&painter);
}

//void Widget::DrawWeb(QPainter *painter) {
//    QPen pen(Qt::black);
//    pen.setWidth(5);
//    painter->setPen(pen);
//    for (const auto& webPoint : webVector) {
//        painter->drawPoint(webPoint);
//    }
//}

void Widget::AddToTimerInterval(int milliseconds) {
    int minInterval = 100;
    int maxInterval = 1000;

    int newInterval = spiderMoveTimer_->interval() + milliseconds;

    newInterval = qBound(minInterval, newInterval, maxInterval);

    spiderMoveTimer_->setInterval(newInterval);
}

void Widget::keyPressEvent(QKeyEvent *event) {
    spiderMoveTimer_->start();
    qDebug() << "timer";

    if (event->key()) {

        if (event->key() == Qt::Key_Up) {
            spider->SetPressedValue("Up");
        }
        if (event->key() == Qt::Key_Down) {
            spider->SetPressedValue("Down");
        }
        if (event->key() == Qt::Key_Left) {
           spider->SetPressedValue("Left");
        }
        if (event->key() == Qt::Key_Right) {
           spider->SetPressedValue("Right");
        }
        if (event->key() == Qt::Key_Space) {
            spiderMoveTimer_->stop();
        }
        //widget.spiderBoostTimer_->start(50);
    } else {
        qDebug() << "nooooo";
    }
}




