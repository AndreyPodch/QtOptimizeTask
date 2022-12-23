#ifndef LINES_H
#include "optimizeLogic.h"
#define LINES_H

const size_t WINDOW_WIDTH = 600;
const size_t WINDOW_HEIGHT= 400;
const size_t COLOR_MATRIX_LEFT=10;
const size_t COLOR_MATRIX_ABOVE=20;
const size_t COLOR_MATRIX_WIDTH=581;
const size_t COLOR_MATRIX_HEIGHT=361;

const size_t COLOR_MATRIX_GRID_STEP=4;
const size_t COLOR_MATRIX_SMOOTH_DEGREE=10;

#include <QWidget>
#include <QPainter>

class Lines : public QWidget
{
    Q_OBJECT
public:
    explicit Lines(QWidget *parent = nullptr);
protected:
  void paintEvent(QPaintEvent *event);
  void drawLines(QPainter *qp);

signals:

};

#endif // LINES_H
