#include <iostream>

using namespace std;

//bool compare(int a, int b)
//{
//    return a > b;
//}

//�ص�����,����������ֵ
int getMax(int a, int b, bool (*p1)(int a, int b))
{
    if(p1(a,b)){
        return a;
    }else{
        return b;
    }
}

int main()
{
    int x = 60;
    int y = 20;
    //int max = getMax(x,y,compare);
    int max = getMax(x,y,[](int a, int b)->bool{
        return a > b;
    });
    cout << max << endl;
    return 0;
}
