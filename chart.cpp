#include "chart.h"

#include <QValueAxis>

using namespace QtCharts;

Chart::Chart(QGraphicsItem *parent, Qt::WindowFlags flags) : QChart(parent, flags) {
  setAcceptHoverEvents(true);
  auto x_axis = new QValueAxis();
  auto y_axis = new QValueAxis();
  x_axis->setRange(-50, 50);
  y_axis->setRange(-50, 50);
  setAxisX(x_axis);
  setAxisY(y_axis);
}

void Chart::wheelEvent(QGraphicsSceneWheelEvent *event) {
  auto pt_org = mapToValue(event->pos());
  qreal scale = event->delta() < 0 ? 2.0 : 0.5;
  const auto mod = event->modifiers();
  if (mod & Qt::CTRL) scale = std::sqrt(scale);
  axis_scale_ *= scale;
  auto ZoomAxis = [scale](QAbstractAxis *axis, qreal org) {
    auto ax = qobject_cast<QValueAxis *>(axis);
    auto min_val = ax->min();
    auto max_val = ax->max();
    ax->setMin((min_val - org) * scale + org);
    ax->setMax((max_val - org) * scale + org);
  };
  ZoomAxis(axisX(), pt_org.x());
  ZoomAxis(axisY(), pt_org.y());
  QGraphicsItem::wheelEvent(event);
}

void Chart::adjustAxisRange(const QSizeF &pixel_range) {
  auto value_range = pixel_range * axis_scale_;
  auto x_axis = qobject_cast<QValueAxis *>(axisX());
  auto y_axis = qobject_cast<QValueAxis *>(axisY());
  auto ZoomAxis = [](QValueAxis *axis, qreal range) {
    range *= 0.5;
    qreal org = (axis->max() + axis->min()) * 0.5;
    axis->setMin(org - range);
    axis->setMax(org + range);
  };
  ZoomAxis(x_axis, value_range.width());
  ZoomAxis(y_axis, value_range.height());
}

qreal Chart::setOptimalAxisScale(const QSizeF &pixel_range, qreal x_min, qreal x_max, qreal y_min, qreal y_max) {
  qreal x_scale = (x_max - x_min) / pixel_range.width();
  qreal y_scale = (y_max - y_min) / pixel_range.height();
  axis_scale_ = x_scale > y_scale ? x_scale : y_scale;
  adjustAxisRange(pixel_range);
  return axis_scale_;
}

void ChartView::mousePressEvent(QMouseEvent *event) {
  is_touching_ = true;
  last_mouse_pos_ = event->pos();
  QChartView::mousePressEvent(event);
}

void ChartView::mouseMoveEvent(QMouseEvent *event) {
  if (is_touching_) {
    QPoint delta = last_mouse_pos_ - event->pos();
    chart()->scroll(delta.x(), -delta.y());
    last_mouse_pos_ = event->pos();
  }
  QChartView::mouseMoveEvent(event);
};

void ChartView::mouseReleaseEvent(QMouseEvent *event) {
  is_touching_ = false;
  QChartView::mouseReleaseEvent(event);
}

void ChartView::resizeEvent(QResizeEvent *event) {
  QChartView::resizeEvent(event);
  auto c = qobject_cast<Chart *>(chart());
  c->adjustAxisRange(event->size());
}
