#include <iostream>
using namespace std;

int f(int n)
{
   if (n == 0)
      return 0;
   else if (n % 2 == 0)
      return f(n / 2);
   else
      return 1 + f(n - 1);
}

int f2(int n)
{
   if (n <= 1)
      return n;
   else if (n % 2 == 0)
      return n + f2(n / 2);
   else
      return f2((n + 1) / 2) + f2((n - 1) / 2);
}

int main()
{
   cout << "E1:" << f(1) << endl;
   cout << "f(1) = " << f(1) << endl;
   cout << "f(2) = " << f(2) << endl;
   cout << "f(3) = " << f(3) << endl;
   cout << "f(99) = " << f(99) << endl;
   cout << "f(100) = " << f(100) << endl;
   cout << "f(128) = " << f(128) << endl;

   cout << "\nE2: f2(n) values:" << endl;
   for (int n = 1; n <= 6; ++n)
   {
      cout << "f2(" << n << ") = " << f2(n) << endl;
   }
   return EXIT_SUCCESS;
}
