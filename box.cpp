#include "box.h"
#include "shape.h"
#include<iostream>


//constructor
Box::Box(void)
{

}

//destructor
Box::~Box(void)
{

}

void Box::print()
{
    std::cout<< "There's a box here" <<std::endl;
}

//Define the "Get" methods
void Box::GetWidth(int &width)
{
    width = mBoxWidth;
}

void Box::GetHeight(int &height)
{
    height = mBoxHeight;
}

void Box::GetDepth(int &depth)
{
    depth = mBoxDepth;
}

void Box::GetOrigin(int &orx, int &ory, int &orz)
{
    orx = mBoxOrx;
    ory = mBoxOry;
    orz = mBoxOrz;
}

//Define the "Set" methods
void Box::SetWidth(const int width)
{
    mBoxWidth = width;
}

void Box::SetHeight(const int height)
{
    mBoxHeight = height;
}

void Box::SetDepth(const int depth)
{
    mBoxDepth = depth;
}

void Box::SetOrigin(const int orx, const int ory, const int orz)
{
    mBoxOrx = orx;
    mBoxOry = ory;
    mBoxOrz = orz;
}
