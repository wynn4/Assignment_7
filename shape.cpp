#include <QCoreApplication>
#include <iostream>
#include "shape.h"


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

void Shape::GetTranslation(int &tx, int &ty, int &tz)
{
    tx = mTx;
    ty = mTy;
    tz = mTz;
}

void Shape::GetRotation(int &rx, int &ry, int &rz)
{
    rx = mRx;
    ry = mRy;
    rz = mRz;
}

void Shape::GetScale(int &sx, int &sy, int &sz)
{
    sx = mSx;
    sy = mSy;
    sz = mSz;
}

void Shape::GetFillColor(float &r, float &g, float &b)
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

void Shape::SetTranslation(const int tx, const int ty, const int tz)
{
    mTx = tx;
    mTy = ty;
    mTz = tz;
}

void Shape::SetRotation(const int rx, const int ry, const int rz)
{
    mRx = rx;
    mRy = ry;
    mRz = rz;
}

void Shape::SetScale(const int sx, const int sy, const int sz)
{
    mSx = sx;
    mSy = sy;
    mSz = sz;

}

void Shape::SetFillColor(const float r, const float g, const float b)
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



