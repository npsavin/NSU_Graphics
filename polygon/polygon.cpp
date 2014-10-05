#include "polygon.h"

#include "math.h"

#include <QtCore>



Polygon::Polygon()
{
    width = 0;
    height = 0;
}

void Polygon::addPoint(QPoint point) {
    points.push_back(point);
}

void Polygon::clearLines() {
    lines.clear();
}

bool Polygon::createLines(){
    //lines.clear();
    if (points.size() >= 2) {

        maxy = 0;
        miny = height;

        for (int i = 0; i < points.size() - 1; i++) {
            if (points[i].y() < points[i+1].y()) {
                lines.push_back(new Line(points[i], points[i + 1]));
            } else {
                lines.push_back(new Line(points[i+1], points[i]));
            }
            miny = __min(points[i].y(), miny);
            maxy = __max(points[i].y(), maxy);
        }
        int i1 = points.size() - 1;
        int i2 = 0;

        if (points[i1].y() < points[i2].y()) {
            lines.push_back(new Line(points[i1], points[i2]));
        } else {
            lines.push_back(new Line(points[i2], points[i1]));
        }
        miny = __min(points[points.size() - 1].y(), miny);
        maxy = __max(points[points.size() - 1].y(), maxy);

        return true;
    }
    return false;
}

bool Polygon::createLines(QVector <QPoint> points){
    //lines.clear();
    if (points.size() >= 2) {

        maxy = 0;
        miny = height;

        for (int i = 0; i < points.size() - 1; i++) {
            if (points[i].y() < points[i+1].y()) {
                lines.push_back(new Line(points[i], points[i + 1]));
            } else {
                lines.push_back(new Line(points[i+1], points[i]));
            }
            miny = __min(points[i].y(), miny);
            maxy = __max(points[i].y(), maxy);
        }
        int i1 = points.size() - 1;
        int i2 = 0;

        if (points[i1].y() < points[i2].y()) {
            lines.push_back(new Line(points[i1], points[i2]));
        } else {
            lines.push_back(new Line(points[i2], points[i1]));
        }
        miny = __min(points[points.size() - 1].y(), miny);
        maxy = __max(points[points.size() - 1].y(), maxy);

        return true;
    }
    return false;
}


QImage Polygon::getImage(int width, int height) {
    this->width = width;
    this->height = height;

    QImage backBuffer(width, height, QImage::Format_RGB888);
    backBuffer.fill(qRgb(255, 255, 255));

    for (int i = 0; i < polygons.size(); i++) {

        QVector <QPoint> points = polygons[i];
        clearLines();
        createLines(points);

    if (points.size() > 2){

        QVector <Line*> activeLines;

        for (int y = miny; y < maxy; y++)
        {
            QVector <QPoint> crossPoints;

            for (int i = activeLines.size() - 1; i >= 0 ; i--)
            {
                if (y >= activeLines[i]->p2.y())
                {
                    activeLines.remove(i);
                }
            }

            for (int i = 0; i < lines.size(); i++)
            {
                if (y == lines[i]->p1.y())
                {
                    activeLines.push_back(lines[i]);
                }
            }

            for (int i = 0; i < activeLines.size(); i++)
            {
                crossPoints.push_back(activeLines[i]->crossPoint(y));
            }
            qSort(crossPoints.begin(), crossPoints.end(), xLessThan);

            for (int i = 0; i < crossPoints.size() - 1; i++)
            {
                if ((0 == i % 2) && (crossPoints[i].x() != crossPoints[i + 1].x()))
                {
                    drawLine(&backBuffer, crossPoints[i].x(), crossPoints[i + 1].x(), crossPoints[i].y(), Qt::black);
                }

            }
        }
    }

    }
    return backBuffer;
}


void Polygon::addPolygon(QVector <QPoint> points) {
    polygons.push_back(points);
}


void Polygon::drawPixel(QImage *backBuffer, int x, int y, QColor color)
{
    uchar *bits = backBuffer->bits();
    bits[y * backBuffer->bytesPerLine() + x * 3 + 0] = color.red();
    bits[y * backBuffer->bytesPerLine() + x * 3 + 1] = color.green();
    bits[y * backBuffer->bytesPerLine() + x * 3 + 2] = color.blue();
}

void Polygon::drawLine(QImage *backBuffer, int x1, int x2, int y, QColor color) {
    if (x2 > x1)
    {
        for (int x = x1; x != x2; x++)
        {
            drawPixel(backBuffer, x, y, color);
        }
    }
    else
    {
        for (int x = x2; x != x1; x++)
        {
            drawPixel(backBuffer, x, y, color);
        }
    }


}
bool Polygon::createAllLines(){
    /*
    bool flag = true;
    if (!createLines()) {
        flag = false;
    }
    for(int i = 0; i < polygons.size(); i++) {
        if (!createLines(polygons[i])) {
            flag = false;
        }
    }
    return flag;*/
    for(int i = 0; i < polygons.size(); i++) {
        createLines(polygons[i]);
    }
    return createLines();
}


void Polygon::clear() {
    points.clear();
}

QVector <QPoint> Polygon::getPoints() {
    return points;
}
QVector <Line*> Polygon::getLines() {
    return lines;
}
