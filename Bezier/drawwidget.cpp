#include "drawwidget.h"
#include "math.h"


DrawWidget::DrawWidget(QWidget *parent) :
    QWidget(parent)
{
    isDrawingLine = false;
    setMouseTracking(true);
    indexPoint= -1;
    mx = 0;
    my = 0;

}

void DrawWidget::paintEvent(QPaintEvent */*event*/) {
    QPainter painter(this);
         if (isDrawingLine) {
            painter.drawImage(0,0, polygon.getImage(width(), height()));
        }
         for (int i = 0; i < polygon.getPoints().size(); i++){
             painter.drawEllipse(polygon.getPoints()[i], 10, 10);
         }


}




void DrawWidget::clear() {
    polygon.clear();
}

QVector <QPoint> DrawWidget::getPoints() {
    return polygon.getPoints();
}
void DrawWidget::addPoint(QPoint point) {


        if(polygon.getPoints().size() == 4)
        {
              polygon.clear();

        }
        if(polygon.getPoints().size() == 3)
        {
            isDrawingLine = true;
        }
        else
        {
            if(isDrawingLine)
            {


                isDrawingLine = false;
            }
        }
        polygon.addPoint(point);


    update();
}
void DrawWidget::mousePressEvent(QMouseEvent *event){
    bool isAdd = true;
    if(indexPoint == -1)
    {

    for (int i = 0; i != polygon.getPoints().size(); i++)
    {
        if((pow((polygon.getPoints()[i].x() - event->x()),2) + pow((polygon.getPoints()[i].y()-event->y()),2)) < 100)
        {
            indexPoint = i;
            isAdd = false;
            break;
        }
    }
    }
    if(isAdd) {
        addPoint(event->pos());
    }
    update();
}
void DrawWidget::mouseMoveEvent(QMouseEvent * event){
    mx = event->x();
    my = event->y();
    if(indexPoint != -1)
    {
        polygon.setPoint(indexPoint, mx, my);
    }
    update();
}
 void DrawWidget::mouseReleaseEvent(QMouseEvent *event){
     indexPoint = -1;
     update();
 }
