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
    void GetTranslation(int &tx, int &ty);
    void GetRotation(int &rz);
    void GetScale(int &sx, int &sy);
    void GetFillColor(int &r, int &g, int &b);
    void GetLineColor(int &r, int &g, int &b);
    void GetLineWidth(int &width);



    void SetIdentifier(const int ID);
    void SetTranslation(const int tx, const int ty);
    void SetRotation(const int rz);
    void SetScale(const int sx, const int sy);
    void SetFillColor(const int r, const int g, const int b);
    void SetLineColor(const int r, const int g, const int b);
    void SetLineWidth(const int width);

     //Members (variables) of class Shape
     Shape* Next(){return mNextPtr;}
     Shape* Previous(){return mPrevPtr;}


private:
   int          mID;         // object ID
   int          mTx, mTy;    // object translation
   int          mRz;         // object rotation
   int          mSx, mSy;    // object scale
   int          mRedF;        // object fill color
   int          mGreenF;      // object fill color
   int          mBlueF;       // object fill color
   int          mRedL;        // object line color
   int          mGreenL;      // object line color
   int          mBlueL;       // object line color
   int          mlWidth;     // object line width

   Shape* mNextPtr;     // linked list next pointer
   Shape* mPrevPtr;     // linked list previous pointer
};

#endif // SHAPE_H
