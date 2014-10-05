#include "drawwidget.h"
#include "math.h"


DrawWidget::DrawWidget(QWidget *parent) :
    QWidget(parent)
{
    //polygon.addPoint(QPoint(100, 100));
    //polygon.addPoint(QPoint(200, 200));
    //polygon.addPoint(QPoint(150, 250));
    magnetFlag = false;
}

void DrawWidget::paintEvent(QPaintEvent */*event*/) {
    QPainter painter(this);

    //if(magnetFlag){
       painter.drawImage(0,0, polygon.getImage(width(), height()));
    //}
    if (!polygon.getPoints().empty() && !magnetFlag) {
        painter.drawEllipse(polygon.getPoints()[0], 10, 10);
    }
    polygon.clearLines();
    polygon.createLines();
    for(int i = 0; i < polygon.getLines().size() - 1; i++){
        painter.drawLine(polygon.getLines()[i]->p1, polygon.getLines()[i]->p2);
    }
    if(getPoints().size() > 1){
        painter.drawLine(polygon.getPoints()[polygon.getPoints().size() - 1], polygon.getPoints()[polygon.getPoints().size() - 2]);
    }

}


void DrawWidget::clear() {
    polygon.clear();
}

QVector <QPoint> DrawWidget::getPoints() {
    return polygon.getPoints();
}
void DrawWidget::addPoint(QPoint point) {
    bool isAdd = true;
    //if (polygon.createLines()) {
    polygon.clearLines();
    polygon.createAllLines();
    //if (polygon.createAllLines()) {
    //if (polygon.getLines().size() > 3) {
    //if (polygon.getPoints().size() > 2) {
        for (int i = 0; i < polygon.getLines().size()-1; i++) {
            if (polygon.getPoints().size() > 0) {
            if ((polygon.getPoints()[polygon.getPoints().size() - 1] != polygon.getLines()[i]->p1) &&
                (polygon.getPoints()[polygon.getPoints().size() - 1] != polygon.getLines()[i]->p2)) {
            Line line(point, polygon.getPoints()[polygon.getPoints().size() - 1]);
                if (Line::isIntersected(*polygon.getLines()[i], line)) {
                    isAdd = false;
                    break;
                }
            }
            }
            /*
            } else {
                if
                Line line(point, polygon.getPoints()[polygon.getPoints().size() - 1]);
                    if (Line::isIntersected(*polygon.getLines()[i], line)) {
                        isAdd = false;
                        break;
                    }

            }*/
        }
    //}
    if (isAdd) {
        polygon.addPoint(point);

    }
    update();
}
void DrawWidget::mousePressEvent(QMouseEvent *event){
    //if(!magnetFlag){
    if (!polygon.getPoints().isEmpty()){
        if((pow((polygon.getPoints()[0].x() - event->x()),2) + pow((polygon.getPoints()[0].y()-event->y()),2)) < 100){
            //magnetFlag = true;
            polygon.addPolygon(polygon.getPoints());
            polygon.clear();
        }
        else{
            addPoint(event->pos());
        }
    }
    else{
    addPoint(event->pos());
    }
    //}
    update();
}
