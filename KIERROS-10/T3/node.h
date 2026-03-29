#pragma once

template <class Node_entry>
struct Node
{
    Node_entry entry;
    Node<Node_entry> *next;

    Node();
    Node(Node_entry item, Node<Node_entry> *link = nullptr);
};

template <class Node_entry>
Node<Node_entry>::Node()
{
    next = nullptr;
}

template <class Node_entry>
Node<Node_entry>::Node(Node_entry item, Node<Node_entry> *link)
{
    entry = item;
    next = link;
}
