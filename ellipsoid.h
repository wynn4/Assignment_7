#ifndef ELLIPSOID_H
#define ELLIPSOID_H
#include "shape.h"


class Ellipsoid : public Shape
{
public:
    Ellipsoid(void);            //constructor
    virtual ~Ellipsoid(void);   //destructor

    void print();
    int GetType(){return 2;}

    void GetRadiusX(int &rad_x);
    void GetRadiusY(int &rad_y);
    void GetRadiusZ(int &rad_z);
    void GetOrigin(int &orx, int &ory, int &orz);


    void SetRadiusX(const int rad_x);
    void SetRadiusY(const int rad_y);
    void SetRadiusZ(const int rad_z);
    void SetOrigin(const int orx, const int ory, const int orz);


private:
    int mEllipsoidRadX;
    int mEllipsoidRadY;
    int mEllipsoidRadZ;
    int mEllipsoidOrx, mEllipsoidOry, mEllipsoidOrz;
};

#endif // ELLIPSOID_H
