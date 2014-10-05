#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionLoad_config, SIGNAL(triggered()), this, SLOT(loadConfig()));
    connect(ui->actionSave_config, SIGNAL(triggered()), this, SLOT(saveConfig()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveConfig() {
    QString fileName =
            QFileDialog::getSaveFileName(this,
                                         tr("Save File"),
                                         QDir::currentPath(),
                                         tr("All files (*.xml)"));
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Circle"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    QDomDocument doc;
    doc.appendChild(doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"")) ;

    QDomElement properties = doc.createElement("properties");

    QDomElement comment = doc.createElement("comment");
    QDomText txt = doc.createTextNode("Polygon properties");
    comment.appendChild(txt);
    properties.appendChild(comment);

    QDomElement polygon = doc.createElement("Polygon");
    QVector <QPoint> points = ui->widget->getPoints();
    for (int i = 0; i < points.size(); i++) {
        QDomElement point = doc.createElement("Point");
        point.setAttribute("x", points[i].x());
        point.setAttribute("y", points[i].y());
        polygon.appendChild(point);
    }
    properties.appendChild(polygon);

    QDomElement el = doc.createElement("entry");
    el.setAttribute("key", "PanelWidth");
    txt = doc.createTextNode(QString::number(width()));
    el.appendChild(txt);
    properties.appendChild(el);

    el = doc.createElement("entry");
    el.setAttribute("key", "PanelHeight");
    txt = doc.createTextNode(QString::number(height()));
    el.appendChild(txt);
    properties.appendChild(el);

    doc.appendChild(properties);

    QTextStream out(&file);
    out << doc.toString();
    file.close();
}

void MainWindow::loadConfig() {
    ui->widget->clear();

    QString fileName =
            QFileDialog::getOpenFileName(this,
                                         tr("Load File"),
                                         QDir::currentPath(),
                                         tr("All files (*.xml)"));
    if (fileName.isEmpty()) {
        return;
    }


    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Polygon"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    QDomDocument doc("mydocument");
    if (!doc.setContent(&file)) {
        return;
    }

    QDomElement docElem = doc.documentElement();

    QDomNodeList nodeList = docElem.elementsByTagName("Point");
    for (int i = 0; i < nodeList.count(); i++) {
        QDomElement node = nodeList.at(i).toElement();
        ui->widget->addPoint(QPoint(node.attribute("x").toInt(), node.attribute("y").toInt()));
    }
}
