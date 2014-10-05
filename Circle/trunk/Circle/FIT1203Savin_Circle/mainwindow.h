#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDomDocument>

#include <QFileDialog>
#include <QMessageBox>

#include <QDebug>

void loadConfig(QString fileName);

namespace Ui {
class MainWindow;
}

static int PanelWidth = 0;
static int PanelHeight = 0;





struct Option {
    QString name;
    QString type;
    QString min;
    QString max;
    QString value;
    QString comment;
    void setData(QString attr, QString value) {
        if (attr == "name") {
            this->name = value;
        }
        if (attr == "type") {
            this->type = value;
        }
        if (attr == "min") {
            this->min = value;
        }
        if (attr == "max") {
            this->max = value;
        }
        if (attr == "value") {
            this->value = value;
        }
        if (attr == "comment") {
            this->comment = value;
        }
    }
};

static QVector <Option> options;


class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;

private slots:
    void saveConfig();
    void openConfig();
    void saveImage();
    QDomElement newOption(QDomDocument &doc,
                          QString tag,
                          QString name,
                          QString type,
                          QString min,
                          QString max,
                          QString value,
                          QString comment);

    void updateUIByOption(Option option);
};

#endif // MAINWINDOW_H
