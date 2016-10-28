#include <QCoreApplication>
#include <iostream>
#include "shape.h"
#include "ellipse.h"

Ellipse::Ellipse(void)  //constructor
{
    //std::cout << "An Ellipse just got made" << std::endl;
}

Ellipse::~Ellipse(void) //destructor
{

}

//print function for debugging
void Ellipse::print()
{
    std::cout << "there's an ellipse here" << std::endl;
}


//Define all of the "Get" Methods (functions)
void Ellipse::GetWidth(int &width)
{
    width = mEllipseWidth;

}

void Ellipse::GetHeight(int &height)
{
    height = mEllipseHeight;

}

void Ellipse::GetOrigin(int &orx, int &ory)
{
    orx = mEllipseOrx;
    ory = mEllipseOry;

}


//Define all of the "Set" Methods (functions)
void Ellipse::SetWidth(const int width)
{
    mEllipseWidth = width;

}

void Ellipse::SetHeight(const int height)
{
    mEllipseHeight = height;

}

void Ellipse::SetOrigin(const int orx, const int ory)
{
    mEllipseOrx = orx;
    mEllipseOry = ory;

}


