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
typedef Node_entry Queue_entry;

struct Node
{
    // data members
    Node_entry entry;
    Node *next;
    // constructors
    Node();
    Node(Node_entry item, Node *add_on = NULL);
};

class Queue
{
public:
    // Standard Queue methods
    Queue();
    bool empty() const;
    Error_code retrieve(Queue_entry &item) const;
    Error_code append(const Queue_entry &item);
    Error_code serve();
    // Safety features for linked structures
    ~Queue();
    Queue(const Queue &original);
    void operator=(const Queue &original);

protected:
    Node *front, *rear;
};

class Extended_queue : public Queue
{
public:
    Extended_queue();
    Extended_queue(const Extended_queue &original);
    void operator=(const Extended_queue &original);
    bool full() const;
    int size() const;
    void clear();
    Error_code append(const Queue_entry &item);
    Error_code serve();
    Error_code serve_and_retrieve(Queue_entry &item);

private:
    int count;
};
