//-------------------------------------------------------
// Filename: main.cpp
//
// Description:  main function for the opengl shape example
//
// Creator:  Professor Corey McBride for MEEN 570 - Brigham Young University
//
// Creation Date: 10/10/16
//
// Owner: Corey McBride
//-------------------------------------------------------
#include "mainwindow.h"
#include <QApplication>

/*  Main Loop
*  Open window with initial window size, title bar,
*  and handle input events.
*/
int main( int argc, char **argv )
{
  QApplication a( argc, argv );

  MainWindow w;
  w.show();
  return a.exec();
}
