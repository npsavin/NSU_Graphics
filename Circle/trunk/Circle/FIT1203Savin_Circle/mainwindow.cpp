#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->widget, SLOT(setPosX(int)));
    connect(ui->horizontalSlider_2, SIGNAL(valueChanged(int)), ui->widget, SLOT(setPosY(int)));
    connect(ui->horizontalSlider_3, SIGNAL(valueChanged(int)), ui->widget, SLOT(setR(int)));

    connect(ui->actionLoad_config, SIGNAL(triggered()), this, SLOT(openConfig()));
    connect(ui->actionSave_config, SIGNAL(triggered()), this, SLOT(saveConfig()));
    connect(ui->actionSave_image, SIGNAL(triggered()), this, SLOT(saveImage()));

    ui->horizontalSlider->setValue(0);
    ui->horizontalSlider->setMinimum(-10000);
    ui->horizontalSlider->setMaximum(10000);
    ui->spinBox->setValue(0);
    ui->spinBox->setMinimum(-10000);
    ui->spinBox->setMaximum(10000);

    ui->horizontalSlider_2->setValue(0);
    ui->horizontalSlider_2->setMinimum(-10000);
    ui->horizontalSlider_2->setMaximum(10000);
    ui->spinBox_2->setValue(0);
    ui->spinBox_2->setMinimum(-10000);
    ui->spinBox_2->setMaximum(10000);

    ui->horizontalSlider_3->setValue(20);
    ui->horizontalSlider_3->setMinimum(0);
    ui->horizontalSlider_3->setMaximum(10000);
    ui->spinBox_3->setValue(20);
    ui->spinBox_3->setMinimum(0);
    ui->spinBox_3->setMaximum(10000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QDomElement MainWindow::newOption(QDomDocument &doc,
                                  QString tag,
                                  QString name,
                                  QString type,
                                  QString min,
                                  QString max,
                                  QString value,
                                  QString comment) {

    QDomElement option = doc.createElement(tag);

    QDomElement el = doc.createElement("comment");
    QDomText txt = doc.createTextNode(comment);
    el.appendChild(txt);
    option.appendChild(el);

    el = doc.createElement("entry");
    el.setAttribute("key", "name");
    txt = doc.createTextNode(name);
    el.appendChild(txt);
    option.appendChild(el);

    el = doc.createElement("entry");
    el.setAttribute("key", "type");
    txt = doc.createTextNode(type);
    el.appendChild(txt);
    option.appendChild(el);

    el = doc.createElement("entry");
    el.setAttribute("key", "min");
    txt = doc.createTextNode(min);
    el.appendChild(txt);
    option.appendChild(el);

    el = doc.createElement("entry");
    el.setAttribute("key", "max");
    txt = doc.createTextNode(max);
    el.appendChild(txt);
    option.appendChild(el);

    el = doc.createElement("entry");
    el.setAttribute("key", "value");
    txt = doc.createTextNode(value);
    el.appendChild(txt);
    option.appendChild(el);

    return option;
}

void MainWindow::updateUIByOption(Option option) {
    if ("posX" == option.name) {
        ui->horizontalSlider->setMinimum(option.min.toInt());
        ui->horizontalSlider->setMaximum(option.max.toInt());
        ui->horizontalSlider->setValue(option.value.toInt());
        ui->spinBox->setMinimum(option.min.toInt());
        ui->spinBox->setMaximum(option.max.toInt());
        ui->spinBox->setValue(option.value.toInt());
    }

    if ("posY" == option.name) {
        ui->horizontalSlider_2->setMinimum(option.min.toInt());
        ui->horizontalSlider_2->setMaximum(option.max.toInt());
        ui->horizontalSlider_2->setValue(option.value.toInt());
        ui->spinBox_2->setMinimum(option.min.toInt());
        ui->spinBox_2->setMaximum(option.max.toInt());
        ui->spinBox_2->setValue(option.value.toInt());
    }

    if ("R" == option.name) {
        ui->horizontalSlider_3->setMinimum(option.min.toInt());
        ui->horizontalSlider_3->setMaximum(option.max.toInt());
        ui->horizontalSlider_3->setValue(option.value.toInt());
        ui->spinBox_3->setMinimum(option.min.toInt());
        ui->spinBox_3->setMaximum(option.max.toInt());
        ui->spinBox_3->setValue(option.value.toInt());
    }

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

    properties.appendChild(newOption(doc,
                                     "option",
                                     "posX",
                                     "int",
                                     QString::number(ui->horizontalSlider->minimum()),
                                     QString::number(ui->horizontalSlider->maximum()),
                                     QString::number(ui->horizontalSlider->value()),
                                     "X position of circle's center"));

    properties.appendChild(newOption(doc,
                                     "option",
                                     "posY",
                                     "int",
                                     QString::number(ui->horizontalSlider_2->minimum()),
                                     QString::number(ui->horizontalSlider_2->maximum()),
                                     QString::number(ui->horizontalSlider_2->value()),
                                     "Y position of circle's center"));

    properties.appendChild(newOption(doc,
                                     "option",
                                     "R",
                                     "int",
                                     QString::number(ui->horizontalSlider_3->minimum()),
                                     QString::number(ui->horizontalSlider_3->maximum()),
                                     QString::number(ui->horizontalSlider_3->value()),
                                     QString("Radius of circle's center")));

    doc.appendChild(properties);

    QTextStream out(&file);
    out << doc.toString();
    file.close();
}

void MainWindow::openConfig() {
    QString fileName =
            QFileDialog::getOpenFileName(this,
                                         tr("Load File"),
                                         QDir::currentPath(),
                                         tr("All files (*.xml)"));
    if (fileName.isEmpty()) {
        return;
    }

    options.clear();
    loadConfig(fileName);
    for (int i = 0; i < options.size(); i++) {
        updateUIByOption(options[i]);
    }
}

void loadConfig(QString fileName) {
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        /*QMessageBox::warning(this, tr("Circle"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));*/
        return;
    }

    QDomDocument doc("mydocument");
    if (!doc.setContent(&file)) {
        return;
    }

    QDomElement docElem = doc.documentElement();

    PanelWidth = docElem.attribute("PanelWidth").toInt();
    PanelHeight = docElem.attribute("PanelHeight").toInt();

    QDomNodeList nodeList = docElem.elementsByTagName("option");
    for (int i = 0; i < nodeList.count(); i++) {
        QDomElement node = nodeList.at(i).toElement();
        QDomNodeList childNodes = node.childNodes();

        Option option;

        for (int j = 0; j < childNodes.count(); j++) {
            QDomElement el = childNodes.at(j).toElement();
            option.setData(el.attribute("key"), el.text());
        }

        options.push_back(option);
    }
}

void MainWindow::saveImage() {
    ui->widget->circle.save("out.png", 300, 300);
}
