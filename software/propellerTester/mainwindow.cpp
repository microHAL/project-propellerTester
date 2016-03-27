#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "measurementSetup.h"
#include "database.h"

Database database;

MeasurementSetup measurementSetup;
QVector<double> power;

void generateSamples();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), about(this)
{
    ui->setupUi(this);

    ui->plot->addGraph();
    ui->plot->xAxis->setLabel("Power [W]");
    ui->plot->yAxis->setLabel("Thrust [mN]");
    ui->plot->xAxis->setAutoTicks(true);
    ui->plot->yAxis->setAutoTicks(true);

    generateSamples();

    ui->plot->graph(0)->setData(power,  measurementSetup.measurement.thrust);
    ui->plot->xAxis->setRange(power.first(),power.last());
    ui->plot->yAxis->setRange(measurementSetup.measurement.thrust.first(),measurementSetup.measurement.thrust.last());
    ui->plot->replot();

    initializePropellerGUI();
}

void generateSamples() {
    //measurementSetup.engine.type = "Engine name";
    //measurementSetup.esc.type = "ECS 50A";
    //measurementSetup.propeller.type = "Very nice propeller";
    //measurementSetup.propeller.numberOfBlades = 2;
    for (uint32_t i=0; i<20000; i++){
        measurementSetup.measurement.current.push_back(i);
        measurementSetup.measurement.voltage.push_back(12000);
        measurementSetup.measurement.thrust.push_back(0.5 * i);

        power.push_back(measurementSetup.measurement.current[i] * measurementSetup.measurement.voltage[i] / 1000);
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

void MainWindow::on_export_button_clicked() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Export File"),
                               "propellerTest.csv",
                               tr("Comma-sepatated values (*.csv);;XML files(*.xml)"));
}

void MainWindow::on_actionAbout_triggered() {
    about.show();
}
