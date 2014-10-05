#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>

#include "circle.h"

class DrawWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrawWidget(QWidget *parent = 0);
    ~DrawWidget();
    Circle circle;

signals:

public slots:
    void setPosX(int value);
    void setPosY(int value);
    void setR(int value);

protected:
    void paintEvent(QPaintEvent *event);

private:
    //Circle circle;

};

#endif // DRAWWIDGET_H
