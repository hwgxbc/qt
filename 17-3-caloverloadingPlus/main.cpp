#include <iostream>

using namespace std;

class Point {
public:
    int x, y;

    Point operator+(Point ptmp);
};

Point Point::operator+(Point ptmp)
{
    Point ret;
    ret.x = x + ptmp.x;
    ret.y = y + ptmp.y;

    return ret;
}

int main()
{
    Point p1;
    p1.x = 2;
    p1.y = 3;

    Point p2;
    p2.x = 3;
    p2.y = 4;

    Point p3 = p1+p2;
    cout << "P3.x=" << p3.x;
    cout << ",P3.y=" << p3.y << endl;
    return 0;
}
