#include <iostream>

using namespace std;

int main ()
{
   // �����򵥵ı���
   int    i;
   int j;
   double d;

   int *p = NULL;
   p = &i;
   // �������ñ���
   int&    r = i;

   double& s = d;

   i = 5;
   cout << "Value of i : " << i << endl;
   cout << "Value of i reference : " << r  << endl;
   cout << "Value of i pointer : " << *p  << endl;

   d = 11.7;
   cout << "Value of d : " << d << endl;
   cout << "Value of d reference : " << s  << endl;

   return 0;
}
