#include <forward_list>

template<class T>
struct Node {
    T data;
    Node<T>* next;
};

template<class T>
class SinglyLinked {
protected:
    Node<T>* head;

public:
    SinglyLinked() noexcept {  }
};