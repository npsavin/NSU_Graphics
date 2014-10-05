#include "myimage.h"
#include <math.h>

MyImage::MyImage(QWidget *parent) :
    QWidget(parent)
{
    x0 = 0;
    y0 = 0;
    r = 100;
}

char MyImage::setX(int x)
{
    if (x <= MAX_X && x >= MIN_X)
        x0 = x;
    else
        return -1;
    return 0;

}

char MyImage::setY(int y)
{
    if (y <= MAX_Y && y >= MIN_Y)
        y0 = y;
    else
        return -1;
    return 0;
}

char MyImage::setRadius(int radius)
{
    if (radius <= MAX_R && radius >= MIN_R)
        r = radius;
    else
        return -1;
    return 0;
}

void MyImage::paintEvent(QPaintEvent * e) {
    e->accept();
    painter = new QPainter(this);
    painter->setBrush(QColor(255, 255, 255));


    //for (int radius = 1; radius < r; ++radius) {
        int radius = r;
        double x = 0;
        double y = radius;
        int delta = 1 - 2 * radius;
        int error = 0;
        while(y >= 0) {

            for (int x1 = 0; x1 < abs(x); x1++) {
                painter->drawPoint(x0 + x1 + width()/2, y0 + abs(y) + height()/2);
                painter->drawPoint(x0 + x1 + width()/2, y0 - abs(y) + height()/2);
                painter->drawPoint(x0 - x1 + width()/2, y0 + abs(y) + height()/2);
                painter->drawPoint(x0 - x1 + width()/2, y0 - abs(y) + height()/2);
            }

            error = 2 * (delta + y) - 1;
            if(delta < 0 && error <= 0) {
                ++x;
                delta += 2 * x + 1;
                continue;
            }
            error = 2 * (delta - x) - 1;
            if(delta > 0 && error > 0) {
                --y;
                delta += 1 - 2 * y;
                continue;
            }
            ++x;
            delta += 2 * (x - y);
            --y;
        }
    //}
    /*double x = 0;
    while (x < r) {
        x += 1;
        double y = sqrt( abs(r*r - x*x));
        for (int x1 = 0; x1 < abs(x); x1++) {
            painter->drawPoint(x0 + x1 + width()/2, y0 + round(y) + height()/2);
            painter->drawPoint(x0 + x1 + width()/2, y0 - round(y) + height()/2);
            painter->drawPoint(x0 - x1 + width()/2, y0 + round(y) + height()/2);
            painter->drawPoint(x0 - x1 + width()/2, y0 - round(y) + height()/2);
        }
    }*/
    painter->end();
}
