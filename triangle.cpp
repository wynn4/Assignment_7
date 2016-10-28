#include <QCoreApplication>
#include <iostream>
#include "shape.h"
#include "triangle.h"

Triangle::Triangle(void)    //constructor implementation
{
    //std::cout << "A Triangle just got made" << std::endl;
}

Triangle::~Triangle(void)  //destructor implementation
{

}

//Print function for debugging
void Triangle::print()
{
    std::cout << "there's a triangle here" << std::endl;
}

//Get Method (function) implementations
void Triangle::GetPoints(int &p1x, int &p1y, int &p2x, int &p2y, int &p3x, int &p3y)
{
   p1x = mp1x;
   p1y = mp1y;

   p2x = mp2x;
   p2y = mp2y;

   p3x = mp3x;
   p3y = mp3y;

}


//Set Method (function) implementations
void Triangle::SetPoints(int p1x, int p1y, int p2x, int p2y, int p3x, int p3y)
{
    mp1x = p1x;
    mp1y = p1y;

    mp2x = p2x;
    mp2y = p2y;

    mp3x = p3x;
    mp3y = p3y;

}




