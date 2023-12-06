#include "spider.h"
#include <QWidget>
#include <QTimer>
#include <QDebug>
#include <QDir>


Spider::Spider(QObject *parent, int spiderScale, QPoint spiderPosition, float shift) : QObject{parent} {
    //QString currentPath = QDir::currentPath();
    //QString parentPath = currentPath + "/Spider_image.png";
    //spiderImage_ = QPixmap(parentPath);

    QString parentPath = "/Users/llziraell/Desktop/Spider_image.png";
    spiderImage_ = QPixmap(parentPath);
    spiderScale_ = spiderScale;
    spiderPosition_.setX(spiderPosition.x());
    spiderPosition_.setY(spiderPosition.y());
    shift_ = shift;
}

void Spider::DrawSpider(QPainter *painter) {
    QRect rect(spiderPosition_.x(), spiderPosition_.y(), spiderScale_, spiderScale_);
    QPixmap rotatedPixmap = spiderImage_.transformed(QTransform().rotate(rotate));
    painter->drawPixmap(rect, rotatedPixmap);
}

void Spider::changeDirection(QRect windowRect) {
    if (spiderPosition_.x() >= windowRect.width() - 50) {
        moveDirection_ = "Left";
        spiderPosition_.setX(spiderPosition_.x() - 50);
        rotate = 180;
    }
    if (spiderPosition_.x() < 0) {
        moveDirection_ = "Right";
        spiderPosition_.setX(spiderPosition_.x() + 50);
        rotate = 180;
    }
    if (spiderPosition_.y() >= windowRect.height() - 50) {
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

void Spider::ChangeShift() {shift_ *= 1.2;}

void Spider::SetDirection(QRect windowRect) {
    rotate = 0;

    qDebug() << "sdsdsds";
        //QPoint newWebPoint = QPoint(spiderPosition_.x()+25, spiderPosition_.y()+25);
        //webVector.append(newWebPoint);

    changeDirection(windowRect);

    qDebug() << moveDirection_;
     //spiderPosition_.setX(spiderPosition_.x() - shift_);
    if (moveDirection_ != "") {

        if (moveDirection_ == "Up") {
            spiderPosition_.setY(spiderPosition_.y() - shift_);
        }
        if (moveDirection_ == "Down") {
            spiderPosition_.setY(spiderPosition_.y() + shift_);
            rotate = 180;
        }
        if (moveDirection_ == "Left") {
            spiderPosition_.setX(spiderPosition_.x() - shift_);
            rotate = -90;
        }
        if (moveDirection_ == "Right") {
            spiderPosition_.setX(spiderPosition_.x() + shift_);
            rotate = 90;
        }

    } else {
        qDebug() << "nan";

    }

}




void Spider::SetPressedValue(QString pressedKey) {
    moveDirection_ = pressedKey;
}


