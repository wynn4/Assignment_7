#include "ellipsoid.h"
#include "shape.h"
#include<iostream>

//Constructor
Ellipsoid::Ellipsoid(void)
{

}

//Destructor
Ellipsoid::~Ellipsoid(void)
{

}


void Ellipsoid::print()
{
    std::cout << "There's and Ellipsoid here" << std::endl;
}

//Define the "Get" methods
void Ellipsoid::GetRadiusX(int &rad_x)
{
    rad_x = mEllipsoidRadX;
}

void Ellipsoid::GetRadiusY(int &rad_y)
{
    rad_y = mEllipsoidRadY;
}

void Ellipsoid::GetRadiusZ(int &rad_z)
{
    rad_z = mEllipsoidRadZ;
}

void Ellipsoid::GetOrigin(int &orx, int &ory, int &orz)
{
    orx = mEllipsoidOrx;
    ory = mEllipsoidOry;
    orz = mEllipsoidOrz;
}

//Define the "Set" methods
void Ellipsoid::SetRadiusX(const int rad_x)
{
    mEllipsoidRadX = rad_x;
}

void Ellipsoid::SetRadiusY(const int rad_y)
{
    mEllipsoidRadY = rad_y;
}

void Ellipsoid::SetRadiusZ(const int rad_z)
{
    mEllipsoidRadZ = rad_z;
}

void Ellipsoid::SetOrigin(const int orx, const int ory, const int orz)
{
    mEllipsoidOrx = orx;
    mEllipsoidOry = ory;
    mEllipsoidOrz = orz;
}
