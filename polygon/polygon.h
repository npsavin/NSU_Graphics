#ifndef POLYGON_H
#define POLYGON_H

#include <QPoint>
#include <QVector>
#include <QImage>
#include <QColor>

#include <QDebug>

struct Line {
    Line(QPoint p1, QPoint p2) {
        this->p1 = p1;
        this->p2 = p2;
    }
    QPoint p1;
    QPoint p2;

    QPoint crossPoint(int y) {
        int x = p1.x() + (p2.x() - p1.x()) * (p1.y() - y) / (p1.y() - p2.y());
        return QPoint(x, y);
    }
    static int area(const QPoint &a, const QPoint &b, const QPoint &c) {
        return (b.x() - a.x()) * (c.y() - a.y()) - (b.y() - a.y()) * (c.x() - a.x());
    }

    static bool intersect(int a, int b, int c, int d) {
        if (a > b)  {
            std::swap(a, b);
        }
        if (c > d)  {
            std::swap(c, d);
        }
        return std::max(a, c) <= std::min(b, d);
    }


    static bool isIntersected(Line line1, Line line2) {
        return (intersect(line1.p1.x(), line1.p2.x(), line2.p1.x(), line2.p2.x() ) &&
                intersect(line1.p1.y(), line1.p2.y(), line2.p1.y(), line2.p2.y() ) &&
                area(line1.p1, line1.p2, line2.p1) *
                area(line1.p1, line1.p2, line2.p2) <= 0 &&
                area(line2.p1, line2.p2, line1.p1) *
                area(line2.p1, line2.p2, line1.p2) <= 0 );
    }
};


class Polygon
{
public:
    Polygon();
    bool createLines();
    bool createLines(QVector <QPoint> points);
    bool createAllLines();

    void addPoint(QPoint point);
    void addPolygon(QVector <QPoint> points);
    void clear();
    void clearLines();
    QImage getImage(int width, int height);

    QVector <QPoint> getPoints();
    QVector <Line*> getLines();

private:
    QVector <QPoint> points;
    QVector <Line*> lines;
    QVector <QVector <QPoint> > polygons;

    void drawPixel(QImage *backBuffer, int x, int y, QColor color);
    void drawLine(QImage *backBuffer, int x1, int x2, int y, QColor color);

    int width;
    int height;
    int maxy;
    int miny;

    static bool xLessThan(const QPoint &p1, const QPoint &p2) {
        return p1.x() < p2.x();
    }
};

#endif // POLYGON_H
