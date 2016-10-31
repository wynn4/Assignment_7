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
#include "OpenGLExample.h"

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

//includes from OpenGLExample.cpp
#include <QApplication>
#include <QOpenGLTexture>
#include <QGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>

#include <QtMath>
#include <random>



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
    generate_3D_geometry();
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

void MainWindow::generate_3D_geometry()
{
    int ID;
    int x, y, z;
    int width, height, depth;
    int rad_x, rad_y, rad_z;
    int tx, ty, tz;
    int rx, ry, rz;
    int sx, sy, sz;
    float redf, greenf, bluef;

    std::vector<MeshGeometry3D*> all_geometry;
    //create the mesh factory
    MeshFactory factory;

    for (std::list<Shape*>::iterator iterator=L.begin(); iterator != L.end(); iterator++)
    {
        Shape* obj = *iterator;
        if(obj->GetType() == 1)
        {
            MeshGeometry3D cube;
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

            double radx = rx*3.14159/180;
            double rady = ry*3.14159/180;
            double radz = rz*3.14159/180;

            QMatrix4x4 scale(sx, 0, 0, 0,
                             0, sy, 0, 0,
                             0, 0, sz, 0,
                             0, 0, 0, 1);
            QMatrix4x4 rotate_x(1, 0, 0, 0,
                                0, cos(radx), -sin(radx), 0,
                                0, sin(radx), cos(radx), 0,
                                0, 0, 0, 1);
            QMatrix4x4 rotate_y(cos(rady), 0, sin(rady), 0,
                                0, 1, 0, 0,
                                -sin(rady), 0, cos(rady), 0,
                                0, 0, 0, 1);
            QMatrix4x4 rotate_z(cos(radz), -sin(radz), 0, 0,
                                sin(radz), cos(radz), 0, 0,
                                0, 0, 1, 0,
                                0, 0, 0, 1);
            QMatrix4x4 translate(1, 0, 0, tx,
                                 0, 1, 0, ty,
                                 0, 0, 1, tz,
                                 0, 0, 0, 1);
            QMatrix4x4 composite;
            composite.setToIdentity();
            composite = composite*translate;
            composite = composite*rotate_x;
            composite = composite*rotate_y;
            composite = composite*rotate_z;
            composite = composite*scale;

            //Create mesh for cube
            factory.GenerateCubeMesh(width, height, depth, 0, &cube);

            //transform the cube
            cube.apply_transform(composite);

            //add the cube mesh to our list of all geometry
            all_geometry.push_back(&cube);

//            QTransform transform = composite.toTransform();



//            QBrush fill(QColor(redf, greenf, bluef, 255));
//            QPen pen(QColor(redl, greenl, bluel, 255), pen_w);

//            mrect = scene->addRect(x, y, width, height, pen, fill);
//            mrect->setTransform(transform);

//            obj = obj->Next();  //Now the for-loop takes care of iterating to the next shape
        }
        else if(obj->GetType() == 2)
        {
            MeshGeometry3D ellipsoid_thing;
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

            double radx = rx*3.14159/180;
            double rady = ry*3.14159/180;
            double radz = rz*3.14159/180;

            QMatrix4x4 scale(sx, 0, 0, 0,
                             0, sy, 0, 0,
                             0, 0, sz, 0,
                             0, 0, 0, 1);
            QMatrix4x4 rotate_x(1, 0, 0, 0,
                                0, cos(radx), -sin(radx), 0,
                                0, sin(radx), cos(radx), 0,
                                0, 0, 0, 1);
            QMatrix4x4 rotate_y(cos(rady), 0, sin(rady), 0,
                                0, 1, 0, 0,
                                -sin(rady), 0, cos(rady), 0,
                                0, 0, 0, 1);
            QMatrix4x4 rotate_z(cos(radz), -sin(radz), 0, 0,
                                sin(radz), cos(radz), 0, 0,
                                0, 0, 1, 0,
                                0, 0, 0, 1);
            QMatrix4x4 translate(1, 0, 0, tx,
                                 0, 1, 0, ty,
                                 0, 0, 1, tz,
                                 0, 0, 0, 1);
            QMatrix4x4 composite;
            composite.setToIdentity();
            composite = composite*translate;
            composite = composite*rotate_x;
            composite = composite*rotate_y;
            composite = composite*rotate_z;
            composite = composite*scale;

            //Create a mesh for an ellipsoid_thing
            factory.GenerateEllipsoidMesh(rad_x, rad_y, rad_z, 2, &ellipsoid_thing);

            //transform the ellipsoid_thing
            ellipsoid_thing.apply_transform(composite);

            //add the ellipsoid_thing mesh to our list of all geometry
            all_geometry.push_back(&ellipsoid_thing);


//            QTransform transform = composite.toTransform();

//            QBrush fill(QColor(redf, greenf, bluef, 255));
//            QPen pen(QColor(redl, greenl, bluel, 255), pen_w);

//            mellipse = scene->addEllipse(x, y, width, height, pen, fill);
//            mellipse->setTransform(transform);

//            obj = obj->Next();  //Now the for-loop takes care of iterating to the next shape
        }
        else if(obj->GetType() == 3)
        {
            MeshGeometry3D cone_thing;
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

            double radx = rx*3.14159/180;
            double rady = ry*3.14159/180;
            double radz = rz*3.14159/180;

            QMatrix4x4 scale(sx, 0, 0, 0,
                             0, sy, 0, 0,
                             0, 0, sz, 0,
                             0, 0, 0, 1);
            QMatrix4x4 rotate_x(1, 0, 0, 0,
                                0, cos(radx), -sin(radx), 0,
                                0, sin(radx), cos(radx), 0,
                                0, 0, 0, 1);
            QMatrix4x4 rotate_y(cos(rady), 0, sin(rady), 0,
                                0, 1, 0, 0,
                                -sin(rady), 0, cos(rady), 0,
                                0, 0, 0, 1);
            QMatrix4x4 rotate_z(cos(radz), -sin(radz), 0, 0,
                                sin(radz), cos(radz), 0, 0,
                                0, 0, 1, 0,
                                0, 0, 0, 1);
            QMatrix4x4 translate(1, 0, 0, tx,
                                 0, 1, 0, ty,
                                 0, 0, 1, tz,
                                 0, 0, 0, 1);
            QMatrix4x4 composite;
            composite.setToIdentity();
            composite = composite*translate;
            composite = composite*rotate_x;
            composite = composite*rotate_y;
            composite = composite*rotate_z;
            composite = composite*scale;

            //Create a mesh for cone
            factory.GenerateConeMesh(rad_x, rad_y, height, 75, &cone_thing);

            //transform the cone_thing
            cone_thing.apply_transform(composite);

            //add the cone_thing mesh to our list of all geometry
            all_geometry.push_back(&cone_thing);


//            QTransform transform = composite.toTransform();

//            QPolygonF triangle;

//            triangle << QPointF(p1x, p1y) << QPointF(p2x, p2y) << QPointF(p3x, p3y);

//            QBrush fill(QColor(redf, greenf, bluef, 255));
//            QPen pen(QColor(redl, greenl, bluel, 255), pen_w);

//            mpolygon = scene->addPolygon(triangle, pen, fill);
//            mpolygon->setTransform(transform);

//            obj = obj->Next();  //Now the for-loop takes care of iterating to the next shape
        }
    }

//        //*** Prepare the geometry mesh to be passed to opengl  ***
//        std::vector<GLfloat> all_verticies;
//        std::vector<GLuint> all_indicies;
//        std::vector<GLfloat> all_normals;

//        unsigned int offset=0;
//        for(int i=0;i<all_geometry.size();i++)//For each geometry mesh in our list created above.
//        {
//            //Add the verticies coordinates from each geometry mesh to one vector.
//            all_verticies.insert(all_verticies.end(),all_geometry[i]->mVerticies.begin(),all_geometry[i]->mVerticies.end());
//            //Add the normals coordinates from each geometry mesh to one vector
//            all_normals.insert(all_normals.end(),all_geometry[i]->mNormals.begin(),all_geometry[i]->mNormals.end());

//            //Combine the triangle indicies in to one vector.
//            for(int x=0;x<all_geometry[i]->mIndicies.size();x++)
//            {
//                all_indicies.push_back(all_geometry[i]->mIndicies[x]+offset);//remember to offset the indicies
//            }
//            offset=(unsigned int)all_verticies.size()/3;//calculate the offset.
//        }


//        mNumIndicies=all_indicies.size();//total number of triangles


//        //*** Send the data to opengl section  ****
//        //Create the vertex buffer
//        glGenBuffers(1, &mVertexBufferHandle);
//        //Bind the vertex buffer to be an array buffer
//        glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferHandle);
//        //Copy our vertex data to the opengl buffer
//        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*all_verticies.size(), all_verticies.data(), GL_STATIC_DRAW);

//        //Create the index buffer
//        glGenBuffers(1, &mIndexBufferHandle);
//        //Bind the index buffer to be an element array buffer
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferHandle);
//        //Copy our index data to the opengl buffer.
//        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * all_indicies.size(), all_indicies.data(), GL_STATIC_DRAW);

//        //Create the normal buffer
//        glGenBuffers(1, &mNormalBufferHandle);
//        //Bind the normal buffer to be an array buffer
//        glBindBuffer(GL_ARRAY_BUFFER, mNormalBufferHandle);
//        //Copy our normal data to the opengl buffer.
//        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*all_normals.size(), all_normals.data(), GL_STATIC_DRAW);



//        //***  Set up the View Matricies and Lights Section  ****
//        //Find the largest coordinate in our vertex data.
//        //We are using this information to set the position of our camera and light outside the geometry
//        std::vector<GLfloat>::iterator iter=std::max_element(all_verticies.begin(),all_verticies.end());
//        mMaxCoord=*iter;

//        //Create the view matrix
//        mViewMatrix.setToIdentity();
//        mViewMatrix.lookAt( QVector3D(mMaxCoord*2,0,0), // Camera is at (mMaxCoord*2,0,0), in World Space
//                            QVector3D(0,0,0), // and looks at the origin
//                            QVector3D(0,0,1)  // Head is up (set to 0,-1,0 to look upside-down)
//                            );

//        //Create the light
//        mLightPos=QVector3D(mMaxCoord*2,mMaxCoord*2,mMaxCoord*2);
//        //Transform the light by the view matrix
//        mLightPos=mViewMatrix*mLightPos;

//        //Send some of our data to opengl.  This data is constant and doesn't change with each render
//        glUseProgram(mProgramHandle);
//        glUniform3f(mLightPositionUHandle, mLightPos[0], mLightPos[1], mLightPos[2]);
//        glUniform3f(mColorUHandle, 1.0, 0.0, 0.0);

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
