#ifndef MYIMAGE_H
#define MYIMAGE_H
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>



class MyImage : public QWidget
{
    Q_OBJECT
    QPainter* painter;
    static const int MAX_X = 100;
    static const int MAX_Y = 100;
    static const int MAX_R = 100;
    static const int MIN_X = -100;
    static const int MIN_Y = -100;
    static const int MIN_R = -100;

    int x0;
    int y0;
    int r;

public:
    explicit MyImage(QWidget *parent = 0);
    char setX(int x);
    char setY(int y);
    char setRadius(int radius);

protected:
    void paintEvent(QPaintEvent *event);
signals:

public slots:
    //void mousePressEvent ( QMouseEvent * event );
private:

};

#endif // MYIMAGE_H
