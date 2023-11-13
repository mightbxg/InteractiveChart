#include "widget.h"

#include <QLayout>

Widget::Widget(QWidget *parent) {
  chart_ = new Chart();
  chart_->legend()->hide();
  auto chartview = new ChartView(chart_);
  auto layout = new QVBoxLayout();
  layout->addWidget(chartview);
  setLayout(layout);
  resize(900, 600);
  QTimer::singleShot(0, [=] { chart_->setOptimalAxisScale(chartview->size(), -50, 50, -50, 50); });

  add_line_to_chart({{-40, -40}, {40, 30}}, Qt::blue, "1");
  add_line_to_chart({{-40, -40}, {40, 50}}, Qt::red, "2");
  add_points_to_chart({{0, 0}, {10, 10}, {20, 30}}, Qt::green, "whatever");
}

void Widget::add_line_to_chart(const QVector<QPointF> &pts, const QColor &color, const QString &name) {
  auto series = new QLineSeries();
  for (const auto &pt : pts) series->append(pt.x(), pt.y());
  series->setColor(color);
  chart_->addSeries(series);
  series->attachAxis(chart_->axisX());
  series->attachAxis(chart_->axisY());
  connect(series, &QLineSeries::clicked, [name] { qInfo() << "line" << name << "clicked"; });
}

void Widget::add_points_to_chart(const QVector<QPointF> &pts, const QColor &color, const QString &name) {
  auto series = new QScatterSeries();
  for (const auto &pt : pts) series->append(pt.x(), pt.y());
  series->setColor(color);
  chart_->addSeries(series);
  series->attachAxis(chart_->axisX());
  series->attachAxis(chart_->axisY());
  series->setMarkerSize(10);
  connect(series, &QScatterSeries::clicked, [name] { qInfo() << "points" << name << "clicked"; });
}
