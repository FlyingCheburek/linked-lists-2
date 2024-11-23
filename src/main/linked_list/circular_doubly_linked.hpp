#include "doubly_linked.hpp"

#ifndef CIRCULAR_DOUBLY_LINKED_HPP
#define CIRCULAR_DOUBLY_LINKED_HPP

template<class T>
class CircularDoublyLinked final : public DoublyLinked<T> {
private:
    DoublyNode<T>* tail = nullptr;
    
};

#endif