#include <vector>
#include <functional>
#include <stdexcept>
#include <iostream>

#ifndef SINGLY_LINKED_HPP

template<class T>
struct SinglyNode {
    T data;
    SinglyNode<T>* next = nullptr;
    SinglyNode() noexcept {  }
    SinglyNode(const T data, SinglyNode<T>* next = nullptr) noexcept : data(data), next(next) {  } 
};

template<class T>
class SinglyLinked {
protected:
    SinglyNode<T>* head = nullptr;
    SinglyNode<T>* get_back() const noexcept {
        if (empty()) return nullptr;
        SinglyNode<T>* back = head;
        while (back->next) back = back->next;
        return back;
    }

public:
    SinglyLinked() noexcept {  }
    SinglyLinked(const std::vector<T>&& items) noexcept {
        for (auto it = items.rbegin(); it != items.rend(); it++) {
            push_front(*it);
        }
    }
    SinglyLinked(const std::vector<T>& items) noexcept {
        for (auto it = items.rbegin(); it != items.rend(); it++) {
            push_front(*it);
        }
    }
    ~SinglyLinked() {
        for (SinglyNode<T>* node = head, *temp; node;) {
            temp = node;
            node = node->next;
            delete temp;
        }
    }

    inline bool empty() const noexcept {
        return head == nullptr;
    }
    void for_each(std::function<void(T item)> func) const noexcept {
        for (SinglyNode<T>* node = head; node; node = node->next) func(node->data);
    }
    T front() const {  
        if (empty()) throw std::out_of_range("Cannot acess 'head' pointer from an empty list.");
        return head->data;
    }
    T back() const {
        if (empty()) throw std::out_of_range("Cannot acess 'head' pointer from an empty list.");
        return get_back()->data;
    }
    void push_front(const T item) noexcept {
        head = new SinglyNode<T>(item, head);
    }
    void push_back(const T item) noexcept {
        SinglyNode<T>* back = get_back();
        if (!back) head = new SinglyNode<T>(item);
        else back->next = new SinglyNode<T>(item);
    }
    void pop_front() noexcept {
        if (empty()) return;
        SinglyNode<T>* old = head;
        head = head->next;
        delete old;
    }
    void pop_back() noexcept {
        if (empty()) return;
        if (!head->next) pop_front();
        else {
            SinglyNode<T>* pred = head, *curr = head->next;
            while (curr->next) {
                pred = curr;
                curr = curr->next;
            }
            delete curr;
            pred->next = nullptr;
        }
    }
    bool delete_where(const T value) noexcept {
        if (empty()) return false;
        if (head->data == value) {
            pop_front();
            return true;
        } 
        else {
            for (SinglyNode<T>* pred = head, *curr = head->next; curr; pred = curr, curr = curr->next) {
                if (curr->data == value) {
                    pred->next = curr->next;
                    delete curr;
                    return true;
                }
            }
        }
        return false;
    }
    inline void delete_all_where(const T value) noexcept { while(delete_where(value)); } 
};

#endif