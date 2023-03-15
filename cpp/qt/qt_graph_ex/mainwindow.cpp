#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <unistd.h>

using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    i=-1;
    ui->clear->setDisabled(1);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Start_clicked()
{

    // create graph and assign data to it:
    ui->customPlot->addGraph();
    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->customPlot->xAxis->setRange(0, 12);
    ui->customPlot->yAxis->setRange(-1, 2);

    // create graph and assign data to it:
    ui->custom->addGraph();
    // give the axes some labels:
    ui->custom->xAxis->setLabel("x");
    ui->custom->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->custom->xAxis->setRange(0, 12);
    ui->custom->yAxis->setRange(-1, 4);

if(i==-1){
    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    timer.start(1000);}
    ui->Start->setDisabled(1);
    ui->clear->setEnabled(1);
    i=1;
}


void MainWindow::on_radioButton_clicked()
{
    ui->custom->hide();
    ui->customPlot->show();
}

void MainWindow::on_radioButton_2_clicked()
{
    ui->customPlot->hide();
    ui->custom->show();
}

void MainWindow::on_clear_clicked()
{

    i= 0;
    ui->customPlot->clearGraphs();
    ui->custom->clearGraphs();
    ui->Start->setEnabled(1);
    ui->clear->setDisabled(1);
}

void MainWindow::update()
{
    if(i==0){}
    else{
    xaxis[0] = i*1.0;
    if(yaxis[0]==0.0){yaxis[0] = 1.0;}
    else{yaxis[0] = 0.0;}
    // add data to lines:
    ui->customPlot->graph(0)->addData(xaxis[0], yaxis[0]);
    // make key axis range scroll with the data (at a constant range size of 8):
    if(xaxis[0] >= 12){
    ui->customPlot->xAxis->setRange(xaxis[0], 10, Qt::AlignRight);}
    ui->customPlot->replot();
    i++;

    xaxis[1] = i*1.0;
    if(yaxis[1]==0.0){yaxis[1] = 3.0;}
    else{yaxis[1] = 0.0;}
    // add data to lines:
    ui->custom->graph(0)->addData(xaxis[1], yaxis[1]);
    // make key axis range scroll with the data (at a constant range size of 10):
    if(xaxis[1] >= 12){
    ui->custom->xAxis->setRange(xaxis[1], 10, Qt::AlignRight);}
    ui->custom->replot();
    i++;
    }
}

