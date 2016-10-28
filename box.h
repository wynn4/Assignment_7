#ifndef BOX_H
#define BOX_H
#include "shape.h"


class Box : public Shape
{
public:
    Box(void);  //constructor
    virtual ~Box(void);   //destructor

    void print();
    int GetType(){return 1;}

    void GetWidth(int &width);
    void GetHeight(int &height);
    void GetDepth(int &depth);
    void GetOrigin(int &orx, int &ory, int &orz);


    void SetWidth(const int width);
    void SetHeight(const int height);
    void SetDepth(const int depth);
    void SetOrigin(const int orx, const int ory, const int orz);


private:
    int mBoxWidth;
    int mBoxHeight;
    int mBoxDepth;
    int mBoxOrx, mBoxOry, mBoxOrz;


};

#endif // BOX_H
