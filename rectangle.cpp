#include <QCoreApplication>
#include <iostream>
#include "shape.h"
#include "rectangle.h"

//rectangle* rect = new Rectangle();


//What happens when you call the constructor
Rectangle::Rectangle(void)
{
    //std::cout << "a rectangle just got made" <<std::endl;
}

//What happens when you call the destructor
Rectangle::~Rectangle(void)
{
    //std::cout << "a rectangle just got destroyed"  <<std::endl;
}

//print function for debugging
void Rectangle::print()
{
    std::cout << "there's a rectangle here" << std::endl;
}

//Define all of the "Get" Methods (functions)
void Rectangle::GetWidth(int &width)
{
    width = mRectWidth;

}

void Rectangle::GetHeight(int &height)
{
    height = mRectHeight;

}

void Rectangle::GetOrigin(int &orx, int &ory)
{
    orx = mRectOrx;
    ory = mRectOry;

}


//Define all of the "Set" Methods (functions)
void Rectangle::SetWidth(const int width)
{
    mRectWidth = width;

}

void Rectangle::SetHeight(const int height)
{
    mRectHeight = height;

}

void Rectangle::SetOrigin(const int orx, const int ory)
{
    mRectOrx = orx;
    mRectOry = ory;

}


