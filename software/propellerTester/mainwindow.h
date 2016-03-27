#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <about.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_export_button_clicked();
    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    About about;

    void initializePropellerGUI();
};

#endif // MAINWINDOW_H
