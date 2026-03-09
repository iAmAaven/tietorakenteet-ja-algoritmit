#include "node_stack.h"
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

Error_code Stack::push(const Stack_entry &item)
/*Post: Stack entry item is added to the top of the Stack; returns success or
        returns a code of overflow if dynamic memory is exhausted. */
{
    Node *new_top = new Node(item, top_node);
    if (new_top == NULL)
        return overflow;
    top_node = new_top;
    return success;
}

Error_code Stack::pop()
/*Post: The top of the Stack is removed. If the Stack is empty the method returns
        underflow; otherwise it returns success. */
{
    Node *old_top = top_node;
    if (top_node == NULL)
        return underflow;
    top_node = old_top->next;
    delete old_top;
    return success;
}

Error_code Stack::top(Stack_entry &item) const
/*Pre:  None.
  Post: If the Stack is not empty, the top of the Stack is returned in item.
        If the Stack is empty an Error code of underflow is returned.
*/
{
    if (top_node == NULL)
        return underflow;
    item = top_node->entry;
    return success;
}

Stack::Stack() // Constructor
/*Post: The Stack is initialized to be empty. */
{
    top_node = NULL;
}

bool Stack::empty() const
/*Post: Returns true if the Stack is empty, otherwise returns false. */
{
    return top_node == NULL;
}

Stack::~Stack() // Destructor
/*Post: The Stack is cleared. */
{
    while (!empty())
        pop();
}

void Stack::operator=(const Stack &original) // Overload assignment
/*Post: The Stack is reset as a copy of Stack original. */
{
    Node *new_top, *new_copy, *original_node = original.top_node;
    if (original_node == NULL)
        new_top = NULL;
    else
    { // Duplicate the linked nodes
        new_copy = new_top = new Node(original_node->entry);
        while (original_node->next != NULL)
        {
            original_node = original_node->next;
            new_copy->next = new Node(original_node->entry);
            new_copy = new_copy->next;
        }
    }
    while (!empty()) // Clean out old Stack entries
        pop();
    top_node = new_top; // and replace them with new entries.
}

Stack::Stack(const Stack &original) // copy constructor
/*Post: The Stack is initialized as a copy of Stack original. */
{
    Node *new_copy, *original_node = original.top_node;
    if (original_node == NULL)
        top_node = NULL;
    else
    { // Duplicate the linked nodes.
        top_node = new_copy = new Node(original_node->entry);
        while (original_node->next != NULL)
        {
            original_node = original_node->next;
            new_copy->next = new Node(original_node->entry);
            new_copy = new_copy->next;
        }
    }
}