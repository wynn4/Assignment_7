//-------------------------------------------------------
// Filename: mainwindow.h
//
// Description:  The main window for the opengl shape example
//
// Creator:  Professor Corey McBride for MEEN 570 - Brigham Young University
//
// Creation Date: 10/10/16
//
// Owner: Corey McBride
//-------------------------------------------------------
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "OpenGLExample.h"
#include<list>
#include<vector>
#include<string>

#include "shape.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);   //constructor
    ~MainWindow();                              //destructor

    void open_and_parse_file();

private slots:
    void on_actionOpen_2_triggered();

    void on_actionSave_As_2_triggered();

    void on_actionClose_triggered();

private:
    void mTokenize(const std::string& str,
                  std::vector<std::string>& tokens,
                  const std::string& delimiters = " ");

    Ui::MainWindow *ui;
    OpenGLExample* mOpenGLExample;
    std::list<Shape*> L;
};

#endif // MAINWINDOW_H
