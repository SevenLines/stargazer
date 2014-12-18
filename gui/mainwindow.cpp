#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->sldDec, SIGNAL(valueChanged(int)), this, SLOT(updateCenterStar()));
    connect(ui->sldRA, SIGNAL(valueChanged(int)), this, SLOT(updateCenterStar()));
    ui->graphicsView->setSky(&sky);
    ui->graphicsView->reloadSky();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateCenterStar()
{
    if (lastDec != ui->sldDec->value() || lastRA != ui->sldRA->value()) {
        ui->graphicsView->setCenterStar((float) ui->sldRA->value()/ 10, ui->sldDec->value());
    }
    lastRA = ui->sldRA->value();
    lastDec = ui->sldDec->value();
}
