#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "measurement.h"
#include "database.h"

Database database;

Measurement measurement;
QVector<double> power;

void generateSamples();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->plot->addGraph();
    ui->plot->xAxis->setLabel("Power [W]");
    ui->plot->yAxis->setLabel("Thrust [mN]");
    ui->plot->xAxis->setAutoTicks(true);
    ui->plot->yAxis->setAutoTicks(true);

    generateSamples();

    ui->plot->graph(0)->setData(power,  measurement.thrust);
    ui->plot->xAxis->setRange(power.first(),power.last());
    ui->plot->yAxis->setRange(measurement.thrust.first(),measurement.thrust.last());
    ui->plot->replot();

    initializePropellerGUI();
}

void generateSamples() {
    measurement.engineType = "Engine name";
    measurement.ECStype = "ECS 50A";
    measurement.propeller.type = "Very nice propeller";
    measurement.propeller.numberOfBlades = 2;
    for (uint32_t i=0; i<20000; i++){
        measurement.current.push_back(i);
        measurement.voltage.push_back(12000);
        measurement.thrust.push_back(0.5 * i);

        power.push_back(measurement.current[i] * measurement.voltage[i] / 1000);
    }
}

void MainWindow::initializePropellerGUI() {
    std::vector<std::string> manufacturers = database.propeller.getAllManufacturers();
    QStringList manufacturerList;
    for (const std::string &man : manufacturers) {
        QString *tmp = new QString(man.c_str());
        manufacturerList.push_back(*tmp);
    }
//    ui->propeller_manufacturer_comboBox->addItems(manufacturerList);

//    ui->propeller_type_comboBox->clear();
//    ui->propeller_bladeAngle_comboBox->clear();
//    ui->propeller_bladeCount_comboBox->clear();
//    ui->propeller_shaft_comboBox->clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}
