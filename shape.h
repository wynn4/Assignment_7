#ifndef SHAPE_H
#define SHAPE_H


class Shape
{

friend class Linkedlist;

public:
    Shape(void);              //constructor
    virtual ~Shape(void);     //destructor

    //pure virtual print function
    virtual void print()=0;

    //pure virtual get_type function
    virtual int GetType()=0;



    //Methods (functions) of class Shape
    void GetIdentifier(int &ID);
    void GetTranslation(int &tx, int &ty, int &tz);
    void GetRotation(int &rx, int &ry, int &rz);
    void GetScale(int &sx, int &sy, int &sz);
    void GetFillColor(float &r, float &g, float &b);
    void GetLineColor(int &r, int &g, int &b);
    void GetLineWidth(int &width);



    void SetIdentifier(const int ID);
    void SetTranslation(const int tx, const int ty, const int tz);
    void SetRotation(const int rx, const int ry, const int rz);
    void SetScale(const int sx, const int sy, const int sz);
    void SetFillColor(const float r, const float g, const float b);
    void SetLineColor(const int r, const int g, const int b);
    void SetLineWidth(const int width);

     //Members (variables) of class Shape
//     Shape* Next(){return mNextPtr;}
//     Shape* Previous(){return mPrevPtr;}


private:
   int          mID;              // object ID
   int          mTx, mTy, mTz;    // object translation
   int          mRx, mRy, mRz;    // object rotation
   int          mSx, mSy, mSz;    // object scale
   float        mRedF;            // object fill color
   float        mGreenF;          // object fill color
   float        mBlueF;           // object fill color
   int          mRedL;            // object line color
   int          mGreenL;          // object line color
   int          mBlueL;           // object line color
   int          mlWidth;          // object line width

//   Shape* mNextPtr;     // linked list next pointer
//   Shape* mPrevPtr;     // linked list previous pointer
};

#endif // SHAPE_H
