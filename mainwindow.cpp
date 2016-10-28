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

#include<QFileDialog>
#include<QMessageBox>
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<fstream>
#include<QMatrix4x4>
#include<list>

#include"shape.h"
#include"rectangle.h"
#include"ellipse.h"
#include"triangle.h"



//constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mOpenGLExample= new OpenGLExample(this);
    this->setCentralWidget(mOpenGLExample);
}

//destructor
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_2_triggered()
{
    open_and_parse_file();
}

void MainWindow::on_actionSave_As_2_triggered()
{

}

void MainWindow::on_actionClose_triggered()
{
    this->close();
}

void MainWindow::open_and_parse_file()
{
    QString filter = "Text Files (*.txt)";
    QString selected_file = QFileDialog::getOpenFileName(this,"Open Shape File", "/home/jesse/Desktop/",filter);


    std::string filename = selected_file.toStdString();
    std::string line;

    std::vector<std::vector<std::string>> tokens;
    std::string delimiters(", ;\t");

    //Build the vector of token vectors
    std::ifstream infile(filename.c_str());
    while (std::getline(infile, line, '\n'))
    {
        if(line == "") continue;            //skip blank lines
        std::vector<std::string> temp;      //temp string vector to pass tokenize
        mTokenize(line, temp, delimiters);
        tokens.push_back(temp);             //pushback the new line of tokens back onto the tokens vector
    }

    int lines_of_file;
    lines_of_file = tokens.size();


    //Clear out th list if there were things there
    L.clear();


    for(int i = 0; i < lines_of_file; i++)
    {
        if(tokens[i][0] == "BOX")
        {
            //Check for errors by checking the size of each line in the vector
            if(tokens[i].size() != 2) std::cout<< "Error in file for " << tokens[i][0] << std::endl;
            else if(tokens[i+1].size() != 6) std::cout<< "Error in file for " << tokens[i][0] << std::endl;
            else if(tokens[i+2].size() != 3) std::cout<< "Error in file for " << tokens[i][0] << std::endl;
            else if(tokens[i+3].size() != 3) std::cout<< "Error in file for " << tokens[i][0] << std::endl;
            else if(tokens[i+4].size() != 1) std::cout<< "Error in file for " << tokens[i][0] << std::endl;
            else if(tokens[i+5].size() != 1) std::cout<< "Error in file for " << tokens[i][0] << std::endl;
            else if(tokens[i+6].size() != 1) std::cout<< "Error in file for " << tokens[i][0] << std::endl;
            else if(tokens[i+7].size() != 3) std::cout<< "Error in file for " << tokens[i][0] << std::endl;
            else    //No errors, make the object and add to the list
            {
                Rectangle* obj = new Rectangle();
                obj->SetIdentifier(std::stoi(tokens[i][1]));
                obj->SetOrigin(std::stoi(tokens[i+1][0]), std::stoi(tokens[i+1][1]));
                obj->SetWidth(std::stoi(tokens[i+1][2]));
                obj->SetHeight(std::stoi(tokens[i+1][3]));
                obj->SetFillColor(std::stoi(tokens[i+2][0]), std::stoi(tokens[i+2][1]), std::stoi(tokens[i+2][2]));
                obj->SetLineWidth(std::stoi(tokens[i+3][0]));
                obj->SetLineColor(std::stoi(tokens[i+4][0]), std::stoi(tokens[i+4][1]), std::stoi(tokens[i+4][2]));
                obj->SetTranslation(std::stoi(tokens[i+5][0]), std::stoi(tokens[i+5][1]));
                obj->SetRotation(std::stoi(tokens[i+6][0]));
                obj->SetScale(std::stoi(tokens[i+7][0]), std::stoi(tokens[i+7][1]));
                L.push_back(obj);
                std::cout << tokens[i][0] << " object added to list" << std::endl;
            }


        }
        else if(tokens[i][0] == "ELLIPSOID")
        {

            if(tokens[i].size() != 2) std::cout<< "Error in file for " << tokens[i][0] << std::endl;
            else if(tokens[i+1].size() != 6) std::cout<< "Error in file for " << tokens[i][0] << std::endl;
            else if(tokens[i+2].size() != 3) std::cout<< "Error in file for " << tokens[i][0] << std::endl;
            else if(tokens[i+3].size() != 3) std::cout<< "Error in file for " << tokens[i][0] << std::endl;
            else if(tokens[i+4].size() != 1) std::cout<< "Error in file for " << tokens[i][0] << std::endl;
            else if(tokens[i+5].size() != 1) std::cout<< "Error in file for " << tokens[i][0] << std::endl;
            else if(tokens[i+6].size() != 1) std::cout<< "Error in file for " << tokens[i][0] << std::endl;
            else if(tokens[i+7].size() != 3) std::cout<< "Error in file for " << tokens[i][0] << std::endl;
            else
            {
                Ellipse* obj = new Ellipse();
                obj->SetIdentifier(std::stoi(tokens[i][1]));
                obj->SetOrigin(std::stoi(tokens[i+1][0]), std::stoi(tokens[i+1][1]));
                obj->SetWidth(std::stoi(tokens[i+1][2]));
                obj->SetHeight(std::stoi(tokens[i+1][3]));
                obj->SetFillColor(std::stoi(tokens[i+2][0]), std::stoi(tokens[i+2][1]), std::stoi(tokens[i+2][2]));
                obj->SetLineWidth(std::stoi(tokens[i+3][0]));
                obj->SetLineColor(std::stoi(tokens[i+4][0]), std::stoi(tokens[i+4][1]), std::stoi(tokens[i+4][2]));
                obj->SetTranslation(std::stoi(tokens[i+5][0]), std::stoi(tokens[i+5][1]));
                obj->SetRotation(std::stoi(tokens[i+6][0]));
                obj->SetScale(std::stoi(tokens[i+7][0]), std::stoi(tokens[i+7][1]));
                L.push_back(obj);
                std::cout << tokens[i][0] << " object added to list" << std::endl;
            }
        }

        else if(tokens[i][0] == "CONE")
        {
            if(tokens[i].size() != 2) std::cout<< "Error in file for " << tokens[i][0] << std::endl;
            else if(tokens[i+1].size() != 6) std::cout<< "Error in file for " << tokens[i][0] << std::endl;
            else if(tokens[i+2].size() != 3) std::cout<< "Error in file for " << tokens[i][0] << std::endl;
            else if(tokens[i+3].size() != 3) std::cout<< "Error in file for " << tokens[i][0] << std::endl;
            else if(tokens[i+4].size() != 1) std::cout<< "Error in file for " << tokens[i][0] << std::endl;
            else if(tokens[i+5].size() != 1) std::cout<< "Error in file for " << tokens[i][0] << std::endl;
            else if(tokens[i+6].size() != 1) std::cout<< "Error in file for " << tokens[i][0] << std::endl;
            else if(tokens[i+7].size() != 3) std::cout<< "Error in file for " << tokens[i][0] << std::endl;
            else
            {
                Triangle* obj = new Triangle();
                obj->SetIdentifier(std::stoi(tokens[i][1]));
                obj->SetPoints(std::stoi(tokens[i+1][0]), std::stoi(tokens[i+1][1]), std::stoi(tokens[i+1][2]), std::stoi(tokens[i+1][3]), \
                        std::stoi(tokens[i+1][4]), std::stoi(tokens[i+1][5]));
                obj->SetFillColor(std::stoi(tokens[i+2][0]), std::stoi(tokens[i+2][1]), std::stoi(tokens[i+2][2]));
                obj->SetLineWidth(std::stoi(tokens[i+3][0]));
                obj->SetLineColor(std::stoi(tokens[i+4][0]), std::stoi(tokens[i+4][1]), std::stoi(tokens[i+4][2]));
                obj->SetTranslation(std::stoi(tokens[i+5][0]), std::stoi(tokens[i+5][1]));
                obj->SetRotation(std::stoi(tokens[i+6][0]));
                obj->SetScale(std::stoi(tokens[i+7][0]), std::stoi(tokens[i+7][1]));
                L.push_back(obj);
                std::cout << tokens[i][0] << " object added to list" << std::endl;
            }
        }

    }
}

void MainWindow::mTokenize(const std::string &str, std::vector<std::string> &tokens, const std::string &delimiters)
{
    // Skip delimiters at beginning.
    std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);

    // Find first "non-delimiter".
    std::string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (std::string::npos != pos || std::string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));

        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);

        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}
