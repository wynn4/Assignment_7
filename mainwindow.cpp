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
#include"box.h"
#include"ellipsoid.h"
#include"cone.h"



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
    write_file();
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
                Box* obj = new Box();
                obj->SetIdentifier(std::stoi(tokens[i][1]));
                obj->SetOrigin(std::stoi(tokens[i+1][0]), std::stoi(tokens[i+1][1]), std::stoi(tokens[i+1][2]));
                obj->SetWidth(std::stoi(tokens[i+1][3]));
                obj->SetHeight(std::stoi(tokens[i+1][4]));
                obj->SetDepth(std::stoi(tokens[i+1][5]));
                obj->SetFillColor(std::stof(tokens[i+2][0]), std::stof(tokens[i+2][1]), std::stof(tokens[i+2][2]));
                obj->SetTranslation(std::stoi(tokens[i+3][0]), std::stoi(tokens[i+3][1]), std::stoi(tokens[i+3][2]));
                obj->SetRotation(std::stoi(tokens[i+4][0]), std::stoi(tokens[i+5][0]), std::stoi(tokens[i+6][0]));
                obj->SetScale(std::stoi(tokens[i+7][0]), std::stoi(tokens[i+7][1]), std::stoi(tokens[i+7][2]));
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
                Ellipsoid* obj = new Ellipsoid();
                obj->SetIdentifier(std::stoi(tokens[i][1]));
                obj->SetOrigin(std::stoi(tokens[i+1][0]), std::stoi(tokens[i+1][1]), std::stoi(tokens[i+1][2]));
                obj->SetRadiusX(std::stoi(tokens[i+1][3]));
                obj->SetRadiusY(std::stoi(tokens[i+1][4]));
                obj->SetRadiusZ(std::stoi(tokens[i+1][5]));
                obj->SetFillColor(std::stof(tokens[i+2][0]), std::stof(tokens[i+2][1]), std::stof(tokens[i+2][2]));
                obj->SetTranslation(std::stoi(tokens[i+3][0]), std::stoi(tokens[i+3][1]), std::stoi(tokens[i+3][2]));
                obj->SetRotation(std::stoi(tokens[i+4][0]), std::stoi(tokens[i+5][0]), std::stoi(tokens[i+6][0]));
                obj->SetScale(std::stoi(tokens[i+7][0]), std::stoi(tokens[i+7][1]), std::stoi(tokens[i+7][2]));
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
                Cone* obj = new Cone();
                obj->SetIdentifier(std::stoi(tokens[i][1]));
                obj->SetOrigin(std::stoi(tokens[i+1][0]), std::stoi(tokens[i+1][1]), std::stoi(tokens[i+1][2]));
                obj->SetRadiusX(std::stoi(tokens[i+1][3]));
                obj->SetRadiusY(std::stoi(tokens[i+1][4]));
                obj->SetHeight(std::stoi(tokens[i+1][5]));
                obj->SetFillColor(std::stof(tokens[i+2][0]), std::stof(tokens[i+2][1]), std::stof(tokens[i+2][2]));
                obj->SetTranslation(std::stoi(tokens[i+3][0]), std::stoi(tokens[i+3][1]), std::stoi(tokens[i+3][2]));
                obj->SetRotation(std::stoi(tokens[i+4][0]), std::stoi(tokens[i+5][0]), std::stoi(tokens[i+6][0]));
                obj->SetScale(std::stoi(tokens[i+7][0]), std::stoi(tokens[i+7][1]), std::stoi(tokens[i+7][2]));
                L.push_back(obj);
                std::cout << tokens[i][0] << " object added to list" << std::endl;
            }
        }

    }
}

void MainWindow::write_file()
{
    int ID;
    int x, y, z;
    int width, height, depth;
    int rad_x, rad_y, rad_z;
    int tx, ty, tz;
    int rx, ry, rz;
    int sx, sy, sz;
    float redf, greenf, bluef;

    QString filter = "Text Files (*.txt)";
    QString file_to_save = QFileDialog::getSaveFileName(this, "Save a Shape File", "/home/jesse/Desktop/", filter);
    std::string file_to_save_to = file_to_save.toStdString();
    std::ofstream outfile(file_to_save_to);

    for (std::list<Shape*>::iterator iterator=L.begin(); iterator != L.end(); iterator++)
    {
        Shape* obj = *iterator;
        if(obj->GetType() == 1)
        {
            Box* box = dynamic_cast<Box*>(obj);
            box->GetIdentifier(ID);
            box->GetOrigin(x, y, z);
            box->GetWidth(width);
            box->GetHeight(height);
            box->GetDepth(depth);
            box->GetFillColor(redf, greenf, bluef);
            box->GetTranslation(tx, ty, tz);
            box->GetRotation(rx, ry, rz);
            box->GetScale(sx, sy, sz);
            outfile << "BOX" << ' ' << ID << std::endl;
            outfile << x << ' ' << y << ' ' << z << ' ' << width << ' ' << height << ' ' << depth << std::endl;
            outfile << redf << ' ' << greenf << ' ' << bluef << std::endl;
            outfile << tx << ' ' << ty << ' ' << tz << std::endl;
            outfile << rx << std::endl;
            outfile << ry << std::endl;
            outfile << rz << std::endl;
            outfile << sx << ' ' << sy << ' ' << sz << '\n' << std::endl;

        }
        else if(obj->GetType() == 2)
        {
            Ellipsoid* ellipsoid = dynamic_cast<Ellipsoid*>(obj);
            ellipsoid->GetIdentifier(ID);
            ellipsoid->GetOrigin(x, y, z);
            ellipsoid->GetRadiusX(rad_x);
            ellipsoid->GetRadiusY(rad_y);
            ellipsoid->GetRadiusZ(rad_z);
            ellipsoid->GetFillColor(redf, greenf, bluef);
            ellipsoid->GetTranslation(tx, ty, tz);
            ellipsoid->GetRotation(rx, ry, rz);
            ellipsoid->GetScale(sx, sy, sz);
            outfile << "ELLIPSOID" << ' ' << ID << std::endl;
            outfile << x << ' ' << y << ' ' << z << ' ' << rad_x << ' ' << rad_y << ' ' << rad_z << std::endl;
            outfile << redf << ' ' << greenf << ' ' << bluef << std::endl;
            outfile << tx << ' ' << ty << ' ' << tz << std::endl;
            outfile << rx << std::endl;
            outfile << ry << std::endl;
            outfile << rz << std::endl;
            outfile << sx << ' ' << sy << ' ' << sz << '\n' << std::endl;

        }
        else if(obj->GetType() == 3)
        {
            Cone* cone = dynamic_cast<Cone*>(obj);
            cone->GetIdentifier(ID);
            cone->GetOrigin(x, y, z);
            cone->GetRadiusX(rad_x);
            cone->GetRadiusY(rad_y);
            cone->GetHeight(height);
            cone->GetFillColor(redf, greenf, bluef);
            cone->GetTranslation(tx, ty, tz);
            cone->GetRotation(rx, ry, rz);
            cone->GetScale(sx, sy, sz);
            outfile << "CONE" << ' ' << ID << std::endl;
            outfile << x << ' ' << y << ' ' << z << ' ' << rad_x << ' ' << rad_y << ' ' << height << std::endl;
            outfile << redf << ' ' << greenf << ' ' << bluef << std::endl;
            outfile << tx << ' ' << ty << ' ' << tz << std::endl;
            outfile << rx << std::endl;
            outfile << ry << std::endl;
            outfile << rz << std::endl;
            outfile << sx << ' ' << sy << ' ' << sz << '\n' << std::endl;

        }
    }

    outfile.close();
    QMessageBox::information(this,"Saved File",file_to_save);
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
