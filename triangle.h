#ifndef TRIANGLE_H
#define TRIANGLE_H


class Triangle : public Shape
{
public:
    Triangle(void);             //constructor prototype
    virtual ~Triangle(void);    //destructor prototype


    void print();
    int GetType(){return 3;}

    //prototype "Get" Methods (functions)
    void GetPoints(int &p1x, int &p1y, int &p2x, int &p2y, int &p3x, int &p3y);

    //prototype "Set" Methods (functions)
    void SetPoints(int p1x, int p1y, int p2x, int p2y, int p3x, int p3y);

private:
    int mp1x, mp1y;
    int mp2x, mp2y;
    int mp3x, mp3y;

};

#endif // TRIANGLE_H
