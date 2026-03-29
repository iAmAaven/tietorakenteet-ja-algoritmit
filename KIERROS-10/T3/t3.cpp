#include <iostream>
#include "dnode.h"
#include "node.h"

using namespace std;

int main()
{
    Node<int> s_default;
    Node<int> s_value(10, &s_default);

    DNode<int> d_default;
    DNode<int> d_value(20, &d_default, nullptr);

    cout << "Singly linked node value: " << s_value.entry << endl;
    cout << "Singly next is null: " << (s_default.next == nullptr) << endl;
    cout << "Doubly linked node value: " << d_value.entry << endl;
    cout << "Doubly default back is null: " << (d_default.back == nullptr) << endl;

    return EXIT_SUCCESS;
}
