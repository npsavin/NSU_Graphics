#include "mainwindow.h"
#include "circle.h"
#include <QApplication>

#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    if (argc > 1) {
        QCoreApplication c(argc, argv);

        Circle circle = Circle();
        circle.setPosX(0);
        circle.setPosY(0);
        circle.setR(20);
        circle.save("out.png", 300, 300);

        /*loadConfig(c.arguments().at(0));

        for (int i = 0; i < options.size(); i++) {
            if (options[i].name == "posX") {
                circle.setPosX(options[i].value.toInt());
            }
            if (options[i].name == "posY") {
                circle.setPosY(options[i].value.toInt());
            }
            if (options[i].name == "R") {
                circle.setR(options[i].value.toInt());
            }
        }*/
        //circle.save("out.jpg", PanelWidth, PanelHeight);
        //circle.save("out.png", 300, 300);//
        //circle.getImage(PanelWidth, PanelHeight).save("out.png", "PNG");
        return c.exec();
    }
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
