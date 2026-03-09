#pragma once

#include <iostream>

enum Error_code
{
    success,
    underflow,
    overflow,
    range_error
};

typedef int Node_entry;
typedef Node_entry Stack_entry;

struct Node
{
    // data members
    Node_entry entry;
    Node *next;
    // constructors
    Node();
    Node(Node_entry item, Node *add_on = NULL);
};

class Stack
{
public:
    // Standard Stack methods
    Stack();
    bool empty() const;
    Error_code push(const Stack_entry &item);
    Error_code pop();
    Error_code top(Stack_entry &item) const;
    // Safety features for linked structures
    ~Stack();
    Stack(const Stack &original);
    void operator=(const Stack &original);

protected:
    Node *top_node;
};