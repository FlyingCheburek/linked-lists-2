#include "singly_linked.hpp"

#ifndef CIRCULAR_SINGLY_LINKED_HPP
#define CIRCULAR_SINGLY_LINKED_HPP

template<class T>
class CircularSinglyLinked final : public SinglyLinked<T> {
private:
    SinglyNode<T>* tail = nullptr;
    bool in_list(const SinglyNode<T>* node) const noexcept override {
        if (empty()) return false;
        if (tail != tail->next) {
            for (SinglyNode<T>* head = tail->next; head != tail; head = head->next) {
                if (head == node) return true;
            }
        }
        return tail == node;
    }
    void quick_insert_after(const SinglyNode<T>* at, const T data) noexcept override {
        if (at == tail) push_back(data);
        else ((SinglyNode<T>*)at)->next = new SinglyNode<T>(data, at->next);
    }

public:
    CircularSinglyLinked() noexcept {  }
    CircularSinglyLinked(const std::vector<T>&& items) noexcept {
        for (auto it = items.rbegin(); it != items.rend(); it++) {
            push_front(*it);
        }
    }
    CircularSinglyLinked(const std::vector<T>& items) noexcept {
        for (auto it = items.rbegin(); it != items.rend(); it++) {
            push_front(*it);
        }
    }
    CircularSinglyLinked(const CircularSinglyLinked<T>& other) {
        other.for_each([this](const T& x){
            this->push_back(x);
        });
    }
    ~CircularSinglyLinked() {
        if (empty()) return;
        if (tail == tail->next) delete tail;
        else {
            SinglyNode<T>* head = tail->next, *temp = head->next;
            do {
               delete head;
               head = temp;
               if (temp) temp = temp->next; 
            } while(head != tail);
            if (!empty()) delete tail;
        }
    }
    const SinglyNode<T>* operator[](const uint64_t index) const noexcept override {
        if (empty()) return nullptr;
        if (!index) return tail->next;
        SinglyNode<T>* node = tail->next;
        for (uint64_t x=1; x <= index; x++) {
            node = node->next;
        }
        return node;
    }
    inline uint64_t size() const noexcept override {
        uint64_t siz = 0;
        for_each([&siz](const T& x){ siz++; });
        return siz;
    }
    void reverse() noexcept override {
        if (empty()) return;
        if (tail == tail->next) return;
        SinglyNode<T>* head_ref = tail->next, *curr = head_ref, *pred = nullptr, *next = nullptr, *temp;
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
            for (SinglyNode<T>* node = tail->next; node != tail; node = node->next) func(node->data);
            func(tail->data);
        }
    }
    void push_front(const T data) noexcept override {
        if (empty()) {
            tail = new SinglyNode<T>(data);
            tail->next = tail;
        }
        else tail->next = new SinglyNode<T>(data, tail->next);
    }
    void push_back(const T data) noexcept override {
        if (empty()) {
            tail = new SinglyNode<T>(data);
            tail->next = tail;
        }
        else {
            SinglyNode<T>* node = new SinglyNode<T>(data, tail->next);
            tail = tail->next = node;
        }
    }
};

#endif