#ifndef ELLIPSE_H
#define ELLIPSE_H


class Ellipse : public Shape
{
public:
    Ellipse(void);              //constructor
    virtual ~Ellipse(void);     //destructor

    void print();
    int GetType(){return 2;}

    void GetWidth(int &width);
    void GetHeight(int &height);
    void GetOrigin(int &orx, int &ory);

    void SetWidth(const int width);
    void SetHeight(const int height);
    void SetOrigin(const int orx, const int ory);

private:
    int mEllipseWidth;
    int mEllipseHeight;
    int mEllipseOrx, mEllipseOry;
};

#endif // ELLIPSE_H
