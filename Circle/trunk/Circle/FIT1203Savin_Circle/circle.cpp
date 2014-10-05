#include "circle.h"

#include <math.h>

Circle::Circle()
{
    posX = 0;
    posY = 0;
    R = 0;
}

QImage Circle::getImage(int width, int height) {
    QImage backBuffer(width, height, QImage::Format_RGB888);
    backBuffer.fill(qRgb(255, 255, 255));
    uchar *bits = backBuffer.bits();
    int dx = posX + width / 2;
    int dy = posY + height / 2;
    for(int i = __max(0, -R +dx); i < __min(width, R + dx); i++){
        for ( int j = __max(0, -R + dy); j < __min(height, R + dy); j++ ){
            if ( pow(i - dx, 2) + pow(j - dy, 2) < pow(R, 2)) {
                int x = i;
                int y = j;

           if ((x > 0) && (y > 0) && (x < width) && (y < height)) {
                bits[y * backBuffer.bytesPerLine() + x * 3 + 0] = 123;
                bits[y * backBuffer.bytesPerLine() + x * 3 + 1] = 123;
                bits[y * backBuffer.bytesPerLine() + x * 3 + 2] = 123;
            }
        }
    }
   }


    //QPainter *painter;
    //painter->begin(&backBuffer);

    //painter->setBrush(QColor(255, 255, 255));


        //for (int radius = 1; radius < r; ++radius) {
/*            int radius = R;
            double x = 0;
            double y = radius;
            int delta = 1 - 2 * radius;
            int error = 0;
            while(y >= 0) {

                for (int x1 = 0; x1 < abs(x); x1++) {
                    painter->drawPoint(posX + x1 + width/2, posY + abs(y) + height/2);
                    painter->drawPoint(posX + x1 + width/2, posY - abs(y) + height/2);
                    painter->drawPoint(posX - x1 + width/2, posY + abs(y) + height/2);
                    painter->drawPoint(posX - x1 + width/2, posY - abs(y) + height/2);
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
            }*/
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
        //painter->end();
        return backBuffer;
}

void Circle::setPosX(int value) {
    posX = value;
}

void Circle::setPosY(int value) {
    posY = value;
}

void Circle::setR(int value) {
    R = value;
}

void Circle::save(QString filename, int width, int height) {
    /*QPainter map(width, height);

    QPainter painter(&map);
    painter.drawImage(0,0, circle.getImage(width(), height()));
    painter.drawImage(0,0, getImage(width, height));

    map.save(filename,"PNG");*/
}
