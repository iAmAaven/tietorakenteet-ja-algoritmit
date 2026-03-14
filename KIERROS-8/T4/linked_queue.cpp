#include "linked_queue.h"
#include <iostream>

Node::Node()
{
    next = NULL;
}

Node::Node(Node_entry item, Node *add_on)
{
    entry = item;
    next = add_on;
}

Queue::Queue() // Constructor
/*Post: The Queue is initialized to be empty. */
{
    front = rear = NULL;
}

Error_code Queue::append(const Queue_entry &item)
/*
Post: Add item to the rear of the Queue and return a code of success
      or return a code of overflow if dynamic memory is exhausted.
*/
{
    Node *new_rear = new Node(item);
    if (new_rear == NULL)
        return overflow;
    if (rear == NULL)
        front = rear = new_rear;
    else
    {
        rear->next = new_rear;
        rear = new_rear;
    }
    return success;
}

Error_code Queue::serve()
/*
Post: The front of the Queue is removed. If the Queue
      is empty, return an Error_code of underflow.
*/
{
    if (front == NULL)
        return underflow;
    Node *old_front = front;
    front = old_front->next;
    if (front == NULL)
        rear = NULL;
    delete old_front;
    return success;
}

Queue::Queue(const Queue &original) // copy constructor
/*Post: The Queue is initialized as a copy of Queue original. */
{
    front = rear = NULL;
    Node *new_node = original.front;
    while (new_node != NULL)
    {
        append(new_node->entry);
        new_node = new_node->next;
    }
}

Queue::~Queue() // Destructor
/*Post: The Queue is cleared. */
{
    while (!empty())
        serve();
}

bool Queue::empty() const
/*Post: Returns true if the Queue is empty, otherwise returns false. */
{
    return front == NULL;
}

Error_code Queue::retrieve(Queue_entry &item) const
/*Pre:  None.
  Post: If the Queue is not empty, the top of the Queue is returned in item.
        If the Queue is empty an Error code of underflow is returned.
*/
{
    if (front == NULL)
        return underflow;

    item = front->entry;
    return success;
}

void Queue::operator=(const Queue &original) // Overload assignment
/*Post: The Queue is reset as a copy of Queue original. */
{
    if (this == &original)
        return;

    while (!empty())
        serve();

    Node *new_node = original.front;
    while (new_node != NULL)
    {
        append(new_node->entry);
        new_node = new_node->next;
    }
}

Extended_queue::Extended_queue()
{
    count = 0;
}

Extended_queue::Extended_queue(const Extended_queue &original)
    : Queue(original)
{
    count = original.count;
}

void Extended_queue::operator=(const Extended_queue &original)
{
    if (this == &original)
        return;

    Queue::operator=(original);
    count = original.count;
}

bool Extended_queue::full() const
/*Post: Returns false unless dynamic memory is exhausted. */
{
    return false;
}

int Extended_queue::size() const
/*Post: Returns the number of entries in the Queue. */
{
    return count;
}

void Extended_queue::clear()
/*Post: All nodes are removed and the Queue is empty. */
{
    while (!empty())
        Queue::serve();
    count = 0;
}

Error_code Extended_queue::append(const Queue_entry &item)
/*Post: Adds item to the rear of the Queue and updates count. */
{
    Error_code result = Queue::append(item);
    if (result == success)
        count++;
    return result;
}

Error_code Extended_queue::serve()
/*Post: Removes the front item from the Queue and updates count. */
{
    Error_code result = Queue::serve();
    if (result == success)
        count--;
    return result;
}

Error_code Extended_queue::serve_and_retrieve(Queue_entry &item)
/*Post: The front of the Queue is copied into item and then removed.
        Returns underflow if the Queue is empty, otherwise success. */
{
    Error_code result = retrieve(item);
    if (result == success)
        serve();
    return result;
}
