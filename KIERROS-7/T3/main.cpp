#include "node_stack.h"
#include <iostream>

using namespace std;

void print_node(const char *name, const Node *n)
{
    cout << name << " = " << n;

    if (!n)
        cout << " (nullptr)\n";
    else
        cout << " | value: " << n->entry
             << " | next:  " << n->next
             << "\n";
}

int main()
{
    cout << "\n\n____________________-'=== A ==='-____________________\n";
    {
        // p1 node value '1', ->next defaults to null
        // p0 node value '0', ->next goes to p1
        Node *p1 = new Node('1');
        Node *p0 = new Node('0', p1);

        print_node("p0", p0);
        print_node("p1", p1);

        delete p1;
        delete p0;
    }

    // ===========================================

    cout << "\n\n____________________-'=== B ==='-____________________\n";
    {
        // p0 node value '0', ->next defaults to null
        // p1 node value '1', ->next goes to p0
        // p2 inherits p1
        Node *p0 = new Node('0');
        Node *p1 = new Node('1', p0);
        Node *p2 = p1;

        print_node("p0", p0);
        print_node("p1", p1);
        print_node("p2", p2);

        delete p1;
        delete p0;
    }

    // ===========================================

    cout << "\n\n____________________-'=== C ==='-____________________\n";
    {
        // p2 node value '2', ->next can't be defined yet, so left empty
        // p1 node value '1', ->next goes to p2
        // p0 node value '0', ->next goes to p1
        // p2 ->next goes to p1

        Node *p2 = new Node('2');
        Node *p1 = new Node('1', p2);
        Node *p0 = new Node('0', p1);
        p2->next = p1;

        print_node("p0", p0);
        print_node("p1", p1);
        print_node("p2", p2);

        delete p0;
        delete p1;
        delete p2;
    }

    cout
        << "\n\n";

    return EXIT_SUCCESS;
}