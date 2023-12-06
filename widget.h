#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QString>
#include <QPixmap>
#include <QPoint>

#include "spider.h"

class Widget : public QWidget {
  Q_OBJECT

 public:
  Widget(QWidget *parent = nullptr);
  ~Widget();
  QTimer *spiderMoveTimer_;
  QTimer *spiderBoostTimer_;

protected:
    virtual void resizeEvent(QResizeEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void paintEvent(QPaintEvent *event);

private slots:
  void UpdateSpiderPosition();

private:
    void AddToTimerInterval(int milliseconds);
    QPoint SetSpiderPosition();
    //void DrawWeb(QPainter *painter);
    QVector<QPoint> webVector;
    QRect windowRect_;
    int timeInterval_;
    Spider *spider;

};
#endif  // WIDGET_H
