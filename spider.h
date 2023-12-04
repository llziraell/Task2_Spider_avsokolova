#ifndef SPIDER_H
#define SPIDER_H

#include <QObject>
#include <QPainter>

class Spider : public QObject {
  Q_OBJECT
 public:
  explicit Spider(QObject *parent = nullptr);

 signals:

private:
  void DrawSpider(QPainter *painter);
};

#endif  // SPIDER_H
