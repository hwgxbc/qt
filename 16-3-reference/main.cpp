#include <iostream>

using namespace std;

double vals[] = {10.1, 12.6, 33.1, 24.1, 50.0};


double& setValue(int i)
{
    double& ref = vals[i];
    return ref;
}

int main()
{
    setValue(3) = 88.9;
    cout << vals[3] ;
    return 0;
}
