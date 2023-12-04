#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QString>

class Widget : public QWidget {
  Q_OBJECT

 public:
  Widget(QWidget *parent = nullptr);
  ~Widget();

  signals:
  void setSignal();

 protected:
  virtual void resizeEvent(QResizeEvent *event);
  virtual void keyPressEvent(QKeyEvent *event);
  virtual void paintEvent(QPaintEvent *event);
  virtual void keyReleaseEvent(QKeyEvent *event);


 private slots:
  void UpdateSpiderPosition();

private:
    void DrawEllipse(QPainter *painter);
    void DrawSpider(QPainter *painter);
    void ShowMousePosition();
    void AddToTimerInterval(int milliseconds);
    void SetSpiderPosition();

    QString moveDirection_;
    QPoint spiderPosition_;
    QRect windowRect_;
    int shift = 10;
    int timeInterval_;
    QTimer *spiderMoveTimer_;
    QTimer *spiderBoostTimer_;
};
#endif  // WIDGET_H
