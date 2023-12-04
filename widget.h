#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPoint>
#include <QRect>

class Widget : public QWidget {
  Q_OBJECT

 public:
  Widget(QWidget *parent = nullptr);
  ~Widget();

 protected:
  virtual void resizeEvent(QResizeEvent *event);
  virtual void keyPressEvent(QKeyEvent *event);
  virtual void paintEvent(QPaintEvent *event);

 private slots:
  void SetSpiderPosition();

private:
    void DrawEllipse(QPainter *painter);
    void DrawSpider(QPainter *painter);
    void ShowMousePosition();

    QPoint spiderPosition_;
    QRect windowRect_;
    bool isDrawingWeb_;
    int shift = 10;
};
#endif  // WIDGET_H
