#include <iostream>
#include "list.h"

using namespace std;

void print_int(int &x)
{
    cout << x << " ";
}

int main()
{
    List<int> numbers;
    numbers.insert(0, 10);
    numbers.insert(1, 20);
    numbers.insert(2, 30);

    cout << "Numbers in list: ";
    numbers.traverse(print_int);
    cout << endl;

    int removed = 0;
    numbers.remove(1, removed);

    cout << "Numbers after remove: ";
    numbers.traverse(print_int);
    cout << "\nRemoved: " << removed << endl;

    return EXIT_SUCCESS;
}
