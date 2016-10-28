#ifndef CONE_H
#define CONE_H
#include"shape.h"


class Cone : public Shape
{
public:
    Cone(void);             //constructor
    virtual ~Cone(void);    //destructor

    void print();
    int GetType(){return 3;}

    void GetRadiusX(int &rad_x);
    void GetRadiusY(int &rad_y);
    void GetHeight(int &height);
    void GetOrigin(int &orx, int &ory, int &orz);


    void SetRadiusX(const int rad_x);
    void SetRadiusY(const int rad_y);
    void SetHeight(const int height);
    void SetOrigin(const int orx, const int ory, const int orz);


private:
    int mConeRadX;
    int mConeRadY;
    int mConeHeight;
    int mConeOrx, mConeOry, mConeOrz;
};

#endif // CONE_H
