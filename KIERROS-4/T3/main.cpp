#include <iostream>
#include "stack.h"

using namespace std;

int main()
{
    int n;
    cout << "Enter an integer: ";
    cin >> n;

    Stack s;
    int num = n;
    for (int d = 2; num > 1;)
    {
        if (num % d == 0)
        {
            s.push((Stack_entry)d);
            num /= d;
        }
        else
            d++;
    }

    Stack_entry e;
    bool first = true;
    while (!s.empty())
    {
        s.top(e);
        s.pop();
        if (!first)
            cout << " ";
        cout << (int)e;
        first = false;
    }
    return 0;
}
