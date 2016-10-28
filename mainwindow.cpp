//-------------------------------------------------------
// Filename: mainwindow.cpp
//
// Description:  The cpp file for the main window for the opengl
//               shape example
//
// Creator:  Professor Corey McBride for MEEN 570 - Brigham Young University
//
// Creation Date: 10/10/16
//
// Owner: Corey McBride
//-------------------------------------------------------

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "meshfactory.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mOpenGLExample= new OpenGLExample(this);
    this->setCentralWidget(mOpenGLExample);
}

MainWindow::~MainWindow()
{
    delete ui;
}

