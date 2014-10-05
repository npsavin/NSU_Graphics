#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>
#include <QPainter>
#include "polygon.h"
#include <QMouseEvent>

class DrawWidget : public QWidget
{

    Q_OBJECT
public:
    explicit DrawWidget(QWidget *parent = 0);

    void addPoint(QPoint point);
    void clear();

    QVector <QPoint> getPoints();
    QPoint mouseCurPoint;

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent * event);
private:
    int mx;
    int my;
    Polygon polygon;
    QString comment;
    bool isDrawingLine;
    int indexPoint;


};

#endif // DRAWWIDGET_H
