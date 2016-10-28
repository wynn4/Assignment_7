#ifndef RECTANGLE_H
#define RECTANGLE_H


class Rectangle : public Shape
{
public:
    Rectangle(void);        //constructor
    virtual ~Rectangle(void);   //destructor

    void print();
    int GetType(){return 1;}

    void GetWidth(int &width);
    void GetHeight(int &height);
    void GetOrigin(int &orx, int &ory);


    void SetWidth(const int width);
    void SetHeight(const int height);
    void SetOrigin(const int orx, const int ory);


private:
    int mRectWidth;
    int mRectHeight;
    int mRectOrx, mRectOry;


};

#endif // RECTANGLE_H
