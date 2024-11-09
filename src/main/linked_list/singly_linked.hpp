template<class T>
struct Node {
    T data;
    Node<T>* next;
};

template<class T>
class SinglyLinked {
    Node<T>* head;
};