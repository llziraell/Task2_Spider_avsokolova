#ifndef SPIDER_H
#define SPIDER_H

#include <QObject>
#include <QPainter>
#include <QPoint>
#include <QString>
#include <QPixmap>
#include <QKeyEvent>
#include <QRect>

class Spider : public QObject {
  Q_OBJECT

 public:
  Spider(QObject *parent, int spiderScale, QPoint spiderPosition, float shift);
  void DrawSpider(QPainter *painter);

  void SetPressedValue(QString pressedKey);

signals:
  void SetDirection(QRect rect);

public slots:
    void ChangeShift();
    void changeDirection(QRect windowRect);

private:
  QPoint spiderPosition_;
  int rotate;
  QPixmap spiderImage_;
  int spiderScale_;
  float shift_;
  QString moveDirection_;
};

#endif  // SPIDER_H
