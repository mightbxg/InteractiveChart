#pragma once

#include <QWidget>

#include "chart.h"

class Widget : public QWidget {
  Q_OBJECT
 public:
  explicit Widget(QWidget* parent = nullptr);
  void add_line_to_chart(const QVector<QPointF>& pts, const QColor& color, const QString& name);
  void add_points_to_chart(const QVector<QPointF>& pts, const QColor& color, const QString& name);

 private:
  Chart* chart_;
};
