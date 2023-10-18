#ifndef SPIDER_H
#define SPIDER_H

#include <QObject>

class Spider : public QObject {
  Q_OBJECT
 public:
  explicit Spider(QObject *parent = nullptr);

 signals:
};

#endif  // SPIDER_H
