#ifndef CIRCLE_H
#define CIRCLE_H

#include <QPainter>

class Circle
{
public:
    Circle();

    void setPosX(int value);
    void setPosY(int value);
    void setR(int value);

    QImage getImage(int width, int height);

    void save(QString filename, int width, int height);

private:
    int posX, posY, R;
};

#endif // CIRCLE_H
