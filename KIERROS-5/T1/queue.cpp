#include "queue.h"

Queue::Queue() : count(0), front(0), rear(maxqueue - 1) {}

bool Queue::empty() const { return count == 0; }

Error_code Queue::append(const Queue_entry &item)
{
    if (count >= maxqueue)
        return overflow;
    count++;
    rear = ((rear + 1) == maxqueue) ? 0 : (rear + 1);
    entry[rear] = item;
    return success;
}

Error_code Queue::serve()
{
    if (count <= 0)
        return underflow;
    count--;
    front = ((front + 1) == maxqueue) ? 0 : (front + 1);
    return success;
}

Error_code Queue::retrieve(Queue_entry &item) const
{
    if (count <= 0)
        return underflow;
    item = entry[front];
    return success;
}

bool Extended_queue::full() const { return count == maxqueue; }
int Extended_queue::size() const { return count; }
void Extended_queue::clear()
{
    count = 0;
    front = 0;
    rear = maxqueue - 1;
}
Error_code Extended_queue::serve_and_retrieve(Queue_entry &item)
{
    if (count <= 0)
        return underflow;
    item = entry[front];
    count--;
    front = (front + 1) % maxqueue;
    return success;
}
