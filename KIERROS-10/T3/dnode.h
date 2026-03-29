#pragma once

template <class Node_entry>
struct DNode
{
    Node_entry entry;
    DNode<Node_entry> *next;
    DNode<Node_entry> *back;

    DNode();
    DNode(Node_entry item, DNode<Node_entry> *link_back = nullptr, DNode<Node_entry> *link_next = nullptr);
};

template <class Node_entry>
DNode<Node_entry>::DNode()
{
    next = nullptr;
    back = nullptr;
}

template <class Node_entry>
DNode<Node_entry>::DNode(Node_entry item, DNode<Node_entry> *link_back, DNode<Node_entry> *link_next)
{
    entry = item;
    back = link_back;
    next = link_next;
}
