#include "cone.h"
#include "shape.h"
#include<iostream>

//Constructor
Cone::Cone(void)
{

}

//Destructor
Cone::~Cone(void)
{

}

void Cone::print()
{
    std::cout << "There's a cone here" << std::endl;
}

//Define the "Get" methods
void Cone::GetRadiusX(int &rad_x)
{
    rad_x = mConeRadX;
}

void Cone::GetRadiusY(int &rad_y)
{
    rad_y = mConeRadY;
}

void Cone::GetHeight(int &height)
{
    height = mConeHeight;
}

void Cone::GetOrigin(int &orx, int &ory, int &orz)
{
    orx = mConeOrx;
    ory = mConeOry;
    orz = mConeOrz;
}

//Define the "Set" methods
void Cone::SetRadiusX(const int rad_x)
{
    mConeRadX = rad_x;
}

void Cone::SetRadiusY(const int rad_y)
{
    mConeRadY = rad_y;
}

void Cone::SetHeight(const int height)
{
    mConeHeight = height;
}

void Cone::SetOrigin(const int orx, const int ory, const int orz)
{
    mConeOrx = orx;
    mConeOry = ory;
    mConeOrz = orz;
}
