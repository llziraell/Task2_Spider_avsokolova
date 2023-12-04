#include "widget.h"

#include <QRandomGenerator>
#include <QKeyEvent>
#include <QPainter>
#include <QPoint>

Widget::Widget(QWidget *parent) : QWidget(parent) {
    windowRect_ = rect();
    SetSpiderPosition();
}

Widget::~Widget() {}

void Widget::SetSpiderPosition() {
        int width = this->width();
        int height = this->height();

        int x = 0, y = 0;

        x = QRandomGenerator::global()->bounded(width);
        y = QRandomGenerator::global()->bounded(height);

        spiderPosition_.setX(x);
        spiderPosition_.setY(y);
        isDrawingWeb_ = true;
}

void Widget::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Up) {
        spiderPosition_.setY(spiderPosition_.y() - shift);
    }
    if (event->key() == Qt::Key_Down) {
        spiderPosition_.setY(spiderPosition_.y() + shift);
    }
    if (event->key() == Qt::Key_Left) {
        spiderPosition_.setX(spiderPosition_.x() - shift);
    }
    if (event->key() == Qt::Key_Right) {
        spiderPosition_.setX(spiderPosition_.x() + shift);
    }
    repaint();
}

void Widget::resizeEvent(QResizeEvent *event) {
    Q_UNUSED(event);
    windowRect_ = rect();
}

void Widget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    // Создаем экземпляр класса для низкоуровневого рисования
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);  // Добавляем сглаживание

    if (isDrawingWeb_) {  // Рисуем паутину и паука при зажатой левой кнопке мыши
        //DrawWeb(&painter);
        DrawSpider(&painter);
    }
}

void Widget::DrawSpider(QPainter *painter) {
    int width = 5;
    int height = 5;

    painter->setBrush(QBrush(Qt::red, Qt::SolidPattern));
    painter->drawEllipse(spiderPosition_, width, height);
}

