#include <iostream>
#include "list.h"

using namespace std;

void print_int(int &x)
{
    cout << x << " ";
}

int main()
{
    List<int> a, b, c;
    int x;
    cout << "Testing insert_first and insert_last...\n";
    insert_first(1, a); // a: 1
    insert_last(2, a);  // a: 1 2
    insert_last(3, a);  // a: 1 2 3
    insert_first(0, a); // a: 0 1 2 3
    cout << "a: ";
    a.traverse(print_int);
    cout << endl;

    cout << "Testing remove_first and remove_last...\n";
    remove_first(x, a);
    cout << "removed first: " << x << endl; // x=0
    remove_last(x, a);
    cout << "removed last: " << x << endl; // x=3
    cout << "a: ";
    a.traverse(print_int);
    cout << endl;

    cout << "Testing median_list...\n";
    median_list(x, a);
    cout << "median: " << x << endl;

    cout << "Testing interchange...\n";
    insert_last(4, a);    // a: 1 2 4
    interchange(0, 2, a); // swap 1 and 4
    cout << "a: ";
    a.traverse(print_int);
    cout << endl;

    cout << "Testing reverse_traverse_list...\n";
    cout << "a reversed: ";
    reverse_traverse_list(a, print_int);
    cout << endl;

    cout << "Testing copy...\n";
    copy(b, a);
    cout << "b: ";
    b.traverse(print_int);
    cout << endl;

    cout << "Testing join...\n";
    insert_last(5, b); // b: 4 2 1 5
    join(a, b);        // append a to b
    cout << "b after join: ";
    b.traverse(print_int);
    cout << endl;

    cout << "Testing reverse...\n";
    reverse(b);
    cout << "b reversed: ";
    b.traverse(print_int);
    cout << endl;

    cout << "Testing split...\n";
    split(b, a, c);
    cout << "a (odd positions): ";
    a.traverse(print_int);
    cout << endl;
    cout << "c (even positions): ";
    c.traverse(print_int);
    cout << endl;

    return EXIT_SUCCESS;
}
