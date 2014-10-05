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



QImage Polygon::getImage(int width, int height) {
    this->width = width;
    this->height = height;

    lines.clear();

    QImage backBuffer(width, height, QImage::Format_RGB888);
    backBuffer.fill(qRgb(255, 255, 255));

    //drawBezier(&backBuffer, Qt::black);
    Bezier(&backBuffer, points[0].x(),points[0].y(), points[1].x(), points[1].y(), points[2].x(), points[2].y(), points[3].x(), points[3].y(), Qt::black);

    return backBuffer;
}





void Polygon::drawPixel(QImage *backBuffer, int x, int y, QColor color)
{
    uchar *bits = backBuffer->bits();
    bits[y * backBuffer->bytesPerLine() + x * 3 + 0] = color.red();
    bits[y * backBuffer->bytesPerLine() + x * 3 + 1] = color.green();
    bits[y * backBuffer->bytesPerLine() + x * 3 + 2] = color.blue();
}

void Polygon::drawLine(QImage *backBuffer, double x1, double y1, double x2, double y2, QColor color) {
//Brezinhem
      /*double dx = abs(x1-x0);
      double dy = abs(y1-y0);
      double sx;
      double sy;
      if (x0 < x1)
      {
        sx = 1;
      }
      else
      {
        sx = -1;
      }
      if (y0 < y1)
      {
        sy = 1;
      }
      else
      {
      sy = -1;
      }
      double err = dx-dy;

      while(true)
      {
        drawPixel(backBuffer, x0, y0, Qt::black);
        if (x0 == x1 && y0 == y1){
        break;
        }
        double e2 = 2*err;
        if (e2 > -dy)
        {
          err = err - dy;
          x0 = x0 + sx;
        }

        if (e2 < dx)
        {
          err = err + dx;
          y0 = y0 + sy;
        }
      }*/
     const int deltaX = abs(x2 - x1);
     const int deltaY = abs(y2 - y1);
     const int signX = x1 < x2 ? 1 : -1;
     const int signY = y1 < y2 ? 1 : -1;

     int error = deltaX - deltaY;

     drawPixel(backBuffer, x2, y2, Qt::black );
     while(x1 != x2 || y1 != y2) {
         drawPixel(backBuffer, x1, y1, Qt::black );
         const int error2 = error * 2;

         if(error2 > -deltaY) {
             error -= deltaY;
             x1 += signX;
         }
         if(error2 < deltaX) {
             error += deltaX;
             y1 += signY;
         }
     }
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
/*void Polygon::drawBezier(QImage *backBuffer, QColor color){
    //drawLine(backBuffer, points[0].x(), points[0].y(), points[1].x(), points[1].y(), color);
    //drawLine(backBuffer, points[1].x(), points[1].y(), points[2].x(), points[2].y(), color);
    //drawLine(backBuffer, points[2].x(), points[2].y(), points[3].x(), points[3].y(), color);
    int npts = 4;
    int cpts = 2;
    int icount, jcount;
    double step, t;
    double x[cpts];
    double y[cpts];

    icount = 0;
    t = 0;
    step = (double)1.0/(cpts - 1);

    for(int i1 = 0; i1 != cpts; i1++)
    {
        if((1.0-t) < 5e-6)
        {
            t=1.0;
        }
        jcount = 0;
        x[icount] = 0.0;
        y[icount] = 0.0;
        for(int i = 0; i != npts; i++)
        {
            double basis = Bernstein(npts - 1 , i, t);
            x[icount] += basis* points[jcount].x();
            y[icount] += basis* points[jcount].y();
            jcount++;
        }
        icount++;
        t+=step;


    }
    for (int i=0; i< cpts - 1; i++)
    {
        drawLine(backBuffer, x[i], y[i], x[i+1], y[i+1], color);
    }

}
double Polygon::Bernstein(int ntps, int i, double t){
    double result=0;
    result = (Factorial(ntps))/(Factorial(i)*Factorial( (ntps-i) )) * (pow(t, i))*(pow((1-t),( (ntps-i) )));
    return result;
}
int Polygon::Factorial(int number){
    if(number == 0 || number ==1)
    {
        return 1;
    }
    else
    {
        return number*(Factorial(number - 1));
    }
}*/
void Polygon::setPoint(int index, int x, int y)
{
    points[index].setX(x);
    points[index].setY(y);
}
void Polygon::Bezier(QImage *backBuffer, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4,  QColor color){
    double m_distance_tolerance = 0.25;

    double x12  = (x1 + x2) / 2;
    double y12  = (y1 + y2) / 2;
    double x23  = (x2 + x3) / 2;
    double y23  = (y2 + y3) / 2;
    double x34  = (x3 + x4) / 2;
    double y34  = (y3 + y4) / 2;
    double x123  = (x12 + x23) / 2;
    double y123  = (y12 + y23) / 2;
    double x234  = (x23 + x34) / 2;
    double y234  = (y23 + y34) / 2;
    double x1234 = (x123 + x234) / 2;
    double y1234 = (y123 + y234) / 2;

    double dx = x4 - x1;
        double dy = y4-y1;

        double d2 = fabs(((x2 - x4) * dy - (y2 - y4) * dx));
        double d3 = fabs(((x3 - x4) * dy - (y3 - y4) * dx));


    if( (d2 + d3)*(d2 + d3) < m_distance_tolerance * (dx*dx + dy*dy) ){

        drawLine(backBuffer, x1, y1, x4, y4, color);
    }
    else{
        Bezier(backBuffer, x1, y1, x12, y12, x123, y123, x1234, y1234, color);
        Bezier(backBuffer, x1234, y1234, x234, y234, x34, y34, x4, y4, color);
    }
}
