#include <forward_list>
#include <functional>
#include <stdexcept>

template<class T>
struct SinglyNode {
    T data;
    SinglyNode<T>* next = nullptr;
    SinglyNode() noexcept {  }
    SinglyNode(const T data, SinglyNode<T>* next) noexcept : data(data), next(next) {  } 
};

template<class T>
class SinglyLinked {
protected:
    SinglyNode<T>* head = nullptr;

public:
    SinglyLinked() noexcept {  }

    void for_each(std::function<void(T item)> func) const noexcept {
        for (SinglyNode<T>* node = head; node; node = node->next) func(node->data);
    }
    T front() const {  
        if (!head) throw std::out_of_range("Cannot acess 'head' pointer from an empty list.");
        return head->data;
    }
    void push_front(const T item) noexcept {
        head = new SinglyNode<T>(item, head);
    }
};