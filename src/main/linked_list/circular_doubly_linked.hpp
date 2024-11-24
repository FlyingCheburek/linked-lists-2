#include "doubly_linked.hpp"
#include <iostream>

#ifndef CIRCULAR_DOUBLY_LINKED_HPP
#define CIRCULAR_DOUBLY_LINKED_HPP

template<class T>
class CircularDoublyLinked final : public DoublyLinked<T> {
private:
    DoublyNode<T>* tail = nullptr;
    bool in_list(const DoublyNode<T>* node) const noexcept override {
        if (empty()) return false;
        if (tail != tail->next) {
            for (DoublyNode<T>* head = tail->next; head != tail; head = head->next) {
                if (head == node) return true;
            }
        }
        return tail == node;
    }

public:
    CircularDoublyLinked() noexcept {  }
    CircularDoublyLinked(const std::vector<T>&& items) noexcept {
        for (auto it = items.rbegin(); it != items.rend(); it++) {
            push_front(*it);
        }
    }
    CircularDoublyLinked(const std::vector<T>& items) noexcept {
        for (auto it = items.rbegin(); it != items.rend(); it++) {
            push_front(*it);
        }
    }
    CircularDoublyLinked(const CircularDoublyLinked<T>& other) {
        other.for_each([this](const T& x){
            this->push_back(x);
        });
    }
    ~CircularDoublyLinked() noexcept {
        if (empty()) return;
        if (tail == tail->next) delete tail;
        else {
            DoublyNode<T>* head = tail->next, *temp = head->next;
            do {
               delete head;
               head = temp;
               if (temp) temp = temp->next; 
            } while(head != tail);
            if (!empty()) delete tail;
        }
    }
    const DoublyNode<T>* operator[](const uint64_t index) const noexcept {
        if (empty()) return nullptr;
        if (!index) return tail->next;
        DoublyNode<T>* node = tail->next;
        for (uint64_t x=1; x <= index; x++) {
            node = node->next;
        }
        return node;
    }
    inline uint64_t size() const noexcept override {
        if (empty()) return 0;
        uint64_t siz = 0;
        DoublyNode<T>* curr = tail->next;
        do {
            siz++;
            curr = curr->next;
        } while(curr != tail->next);
        return siz;
    }
    void reverse() noexcept override {
        if (empty()) return;
        if (tail == tail->next) return;
        DoublyNode<T>* head_ref = tail->next, *curr = head_ref, *pred = nullptr, *next = nullptr, *temp;
        do {
            next = curr->next;
            curr->next = pred;
            pred = curr;
            curr = next;
        } while (curr != head_ref);
        head_ref->next = pred;
        temp = head_ref;
        head_ref = tail;
        tail = temp;
    }
    inline bool empty() const noexcept override { return tail == nullptr; }
    void for_each(std::function<void(T item)> func) const noexcept override {
        if (empty()) return;
        if (tail == tail->next) func(tail->data);
        else {
            DoublyNode<T>* curr = tail->next;
            do {
                func(curr->data);
                curr = curr->next;
            } while(curr != tail->next);
        }
    }
    T front() const override {
        if (empty()) throw std::out_of_range("Cannot acess 'head' pointer from an empty list.");
        return tail->next->data;
    }
    T back() const override {
        if (empty()) throw std::out_of_range("Cannot acess 'head' pointer from an empty list.");
        return tail->data;
    }
    void push_front(const T item) noexcept override {
        if (empty()) {
            tail = new DoublyNode<T>(item);
            tail->pred = tail->next = tail;
        }
        else {
            DoublyNode<T>* node = new DoublyNode<T>(item, tail->next, tail);
            tail->next->pred = node;
            tail->next = node;
        }
    }
    void push_back(const T item) noexcept override {
        if (empty()) {
            tail = new DoublyNode<T>(item);
            tail->pred = tail->next = tail;
        }
        else {
            DoublyNode<T>* node = new DoublyNode<T>(item, tail->next, tail);
            tail->next = node;
            tail = node;
        }
    }
    
};

#endif 