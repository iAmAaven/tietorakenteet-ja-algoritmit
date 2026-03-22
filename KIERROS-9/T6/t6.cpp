#include <iostream>
using namespace std;

// (a) Nonrecursive gcd
int gcd_search(int x, int y)
{
    int gcd = 1;
    int min_val = (x < y) ? x : y;
    for (int i = 1; i <= min_val; ++i)
    {
        if (x % i == 0 && y % i == 0)
            gcd = i;
    }
    return gcd;
}

// (b) Recursive Euclid's algorithm
int gcd_recursive(int x, int y)
{
    if (y == 0)
        return x;
    else
        return gcd_recursive(y, x % y);
}

// (c) Iterative Euclid's algorithm
int gcd_iterative(int x, int y)
{
    while (y != 0)
    {
        int temp = y;
        y = x % y;
        x = temp;
    }
    return x;
}

int main()
{
    int x, y;
    cout << "Enter two positive integers: ";
    while (!(cin >> x >> y) || x <= 0 || y <= 0)
    {
        cout << "Invalid input. Please enter two positive integers: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    cout << "\n(a) gcd_search(" << x << ", " << y << ") = " << gcd_search(x, y) << endl;
    cout << "\n(b) gcd_recursive(" << x << ", " << y << ") = " << gcd_recursive(x, y) << endl;
    cout << "\n(c) gcd_iterative(" << x << ", " << y << ") = " << gcd_iterative(x, y) << endl;

    return EXIT_SUCCESS;
}
