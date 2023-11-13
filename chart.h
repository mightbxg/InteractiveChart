#pragma once

#include <QtCharts>

class Chart : public QtCharts::QChart {
  Q_OBJECT
 public:
  explicit Chart(QGraphicsItem* parent = nullptr, Qt::WindowFlags flags = {});
  void adjustAxisRange(const QSizeF& pixel_range);
  qreal setOptimalAxisScale(const QSizeF& pixel_range, qreal x_min, qreal x_max, qreal y_min, qreal y_max);
  void setAxisScale(qreal scale) { axis_scale_ = scale; }

 protected:
  void wheelEvent(QGraphicsSceneWheelEvent* event) override;

 private:
  qreal axis_scale_{0.1f};
};

class ChartView : public QtCharts::QChartView {
  Q_OBJECT
 public:
  explicit ChartView(QChart* chart, QWidget* parent = nullptr) : QtCharts::QChartView(chart, parent) {}

 protected:
  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void resizeEvent(QResizeEvent* event) override;

 private:
  bool is_touching_{false};
  QPoint last_mouse_pos_;
};