#include <iostream> 
using namespace std; 

#4
void fun(int *p)
{
   *p = (*p) * (*p);
}

int main() 
{ 
   #1
   double n = 12;
   double *pn = &n;

   #2
   int a = 555;
   int *pa = &a;
   *pa = 777;
   cout << a << endl;

   #3
   int arr[] = {1, 2, 3, 4, 5};
   int *parr = arr;
   cout << *parr + 2 << endl;

   #5
   int x;
   cin >> x;
   int *px = new int(x);
   delete px;
   cout << x << endl;
   
   #5
   int q;
   cin >> q;
   char *y = new char[q];
   delete y;
   
}   