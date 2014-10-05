#include "drawwidget.h"
#include <QPainter>
#include <QImage>

DrawWidget::DrawWidget(QWidget *parent) : QWidget(parent) {

}

DrawWidget::~DrawWidget() {
}

void DrawWidget::paintEvent(QPaintEvent */*event*/) {
    QPainter painter(this);
    //painter.drawImage(0,0, circle.getImage(width(), height()));
    painter.drawImage(0,0, circle.getImage(width(), height()));
}

void DrawWidget::setPosX(int value) {
    circle.setPosX(value);
    update();
}

void DrawWidget::setPosY(int value) {
    circle.setPosY(value);
    update();
}

void DrawWidget::setR(int value) {
    circle.setR(value);
    update();
}
