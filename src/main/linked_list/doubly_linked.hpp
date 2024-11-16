#include "singly_linked.hpp"

#ifndef DOUBLY_LINKED_HPP

template<class T>
struct DoublyNode : public SinglyNode<T> {
    DoublyNode<T>* next = nullptr, *pred = nullptr;
    DoublyNode() noexcept {  }
    DoublyNode(const T data, DoublyNode<T>* next = nullptr, DoublyNode<T>* pred = nullptr): next(next), pred(pred) {
        this->data = data;
    }
    
};

template<class T>
class DoublyLinked : public SinglyLinked<T> {
private:
    DoublyNode<T>* head = nullptr;
    DoublyNode<T>* get_back() const noexcept {
        if (empty()) return nullptr;
        DoublyNode<T>* back = head;
        while (back->next) back = back->next;
        return back;
    }
    bool in_list(const DoublyNode<T>* node) const noexcept {
        if (empty()) return false;
        for (DoublyNode<T>* i = head; i; i = i->next) {
            if (node == i) return true;
        }
        return false;
    }
    void quick_insert_after(const DoublyNode<T>* at, const T data) noexcept {
        ((DoublyNode<T>*)at)->next = new DoublyNode<T>(data, at->next, at);
    }

public:
    DoublyLinked() noexcept {  }
    DoublyLinked(const std::vector<T>&& items) noexcept {
        for (auto it = items.rbegin(); it != items.rend(); it++) {
            push_front(*it);
        }
    }
    DoublyLinked(const std::vector<T>& items) noexcept {
        for (auto it = items.rbegin(); it != items.rend(); it++) {
            push_front(*it);
        }
    }
    DoublyLinked(const DoublyLinked<T>& other) noexcept {
        DoublyNode<T>* curr = head;
        other.for_each([this, &curr](const T& item){
            if (!this->head) {
               head = new DoublyNode<T>(item);
               curr = head; 
            } 
            else {
                curr->next = new DoublyNode<T>(item, nullptr, curr);
                curr = curr->next;
            }
        });
    }
    ~DoublyLinked() noexcept {
        for (DoublyNode<T>* node = head, *temp; node;) {
            temp = node;
            node = node->next;
            delete temp;
        }
    }
    const DoublyNode<T>* operator[](const uint64_t index) const {
        if (!index) return head;
        DoublyNode<T>* node = head;
        for (uint64_t x=1; x <= index; x++) {
            if (!node) throw std::out_of_range("List index out of range.");
            node = node->next;
        }
        if (!node) throw std::out_of_range("List index out of range.");
        return node;
    }
    inline uint64_t size() const noexcept override {
        uint64_t siz = 0;
        for (DoublyNode<T>* i = head; i; i = i->next) siz++;
        return siz;
    }
    void reverse() noexcept override {
        
    }
    inline bool empty() const noexcept override {
        return head == nullptr;
    }
    void push_front(const T item) noexcept override {
        DoublyNode<T>* node = new DoublyNode<T>(item, head);
        if (head) head->pred = node;
        head = node;
    }
    void push_back(const T item) noexcept override {
        if (!head) head = new DoublyNode<T>(item);
        else {
            DoublyNode<T>* node = new DoublyNode<T>(item, nullptr, get_back());
            node->pred->next = node;
        }
    }
    void for_each(std::function<void(T item)> func) const noexcept override {
        for (DoublyNode<T>* node = head; node; node = node->next) func(node->data);
    }
    T front() const override {
        if (empty()) throw std::out_of_range("Cannot acess 'head' pointer from an empty list.");
        return head->data;
    }
    T back() const override {
        if (empty()) throw std::out_of_range("Cannot acess 'head' pointer from an empty list.");
        return get_back()->data;
    }
};

#endif