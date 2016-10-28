#include <QCoreApplication>
#include <iostream>
#include "shape.h"
#include "rectangle.h"


//constructor
Shape::Shape(void)
{
    //std::cout << "shape constructor called" << std::endl;
    mID = 0;
}

//destructor
Shape::~Shape(void)
{
    //std::cout << "shape destructor called" << std::endl;
}



//Define all of the "Get" Methods (functions)

void Shape::GetIdentifier(int &ID)
{
    ID = mID;

}

void Shape::GetTranslation(int &tx, int &ty)
{
    tx = mTx;
    ty = mTy;

}

void Shape::GetRotation(int &rz)
{
    rz = mRz;


}

void Shape::GetScale(int &sx, int &sy)
{
    sx = mSx;
    sy = mSy;

}

void Shape::GetFillColor(int &r, int &g, int &b)
{
    r = mRedF;
    g = mGreenF;
    b = mBlueF;
}

void Shape::GetLineColor(int &r, int &g, int &b)
{
    r = mRedL;
    g = mGreenL;
    b = mBlueL;
}

void Shape::GetLineWidth(int &width)
{
    width = mlWidth;

}


//Define all of the "Set" Methods (functions)

void Shape::SetIdentifier(const int ID)
{
    mID = ID;

}

void Shape::SetTranslation(const int tx, const int ty)
{
    mTx = tx;
    mTy = ty;

}

void Shape::SetRotation(const int rz)
{
    mRz = rz;


}

void Shape::SetScale(const int sx, const int sy)
{
    mSx = sx;
    mSy = sy;

}

void Shape::SetFillColor(const int r, const int g, const int b)
{
    mRedF = r;
    mGreenF = g;
    mBlueF = b;

}

void Shape::SetLineColor(const int r, const int g, const int b)
{
    mRedL = r;
    mGreenL = g;
    mBlueL = b;

}

void Shape::SetLineWidth(const int width)
{
    mlWidth  = width;

}



