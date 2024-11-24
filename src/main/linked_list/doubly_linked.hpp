#include "singly_linked.hpp"

#ifndef DOUBLY_LINKED_HPP
#define DOUBLY_LINKED_HPP

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
    void quick_insert_after(const DoublyNode<T>* at, const T data) noexcept {
        ((DoublyNode<T>*)at)->next = new DoublyNode<T>(data, at->next, (DoublyNode<T>*)at);
    }

protected:
    virtual bool in_list(const DoublyNode<T>* node) const noexcept {
        if (empty()) return false;
        for (DoublyNode<T>* i = head; i; i = i->next) {
            if (node == i) return true;
        }
        return false;
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
    virtual inline uint64_t size() const noexcept override {
        uint64_t siz = 0;
        for (DoublyNode<T>* i = head; i; i = i->next) siz++;
        return siz;
    }
    virtual void reverse() noexcept override {
        if (empty()) return;
        if (!head->next) return;
        DoublyNode<T>* pred = nullptr;
        for (DoublyNode<T> *curr = head; curr;) {
            pred = curr->pred;
            curr->pred = curr->next;
            curr->next = pred;
            curr = curr->pred;
        }
        head = pred->pred;
    }
    virtual inline bool empty() const noexcept override {
        return head == nullptr;
    }
    virtual void for_each(std::function<void(T item)> func) const noexcept override {
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
    virtual void push_front(const T item) noexcept override {
        DoublyNode<T>* node = new DoublyNode<T>(item, head);
        if (head) head->pred = node;
        head = node;
    }
    virtual void push_back(const T item) noexcept override {
        if (!head) head = new DoublyNode<T>(item);
        else {
            DoublyNode<T>* node = new DoublyNode<T>(item, nullptr, get_back());
            node->pred->next = node;
        }
    }
    void pop_front() noexcept override {
        if (empty()) return;
        DoublyNode<T>* old = head;
        head = head->next;
        head->pred = nullptr;
        delete old;
    }
    void pop_back() noexcept override {
        if (empty()) return;
        if (!head->next) pop_front();
        DoublyNode<T>* tail = get_back()->pred;
        delete tail->next;
        tail->next = nullptr;
    }
    void insert_after(const DoublyNode<T>* at, const T data) {
        if (!in_list(at)) throw std::invalid_argument("Node address could not be found.");
        ((DoublyNode<T>*)at)->next = new DoublyNode<T>(data, at->next, (DoublyNode<T>*)at);
    }
    void insert_after(const uint64_t index, const T data) {
        DoublyNode<T>* temp = (DoublyNode<T>*)this->operator[](index);
        temp->next = new DoublyNode<T>(data, temp->next, (DoublyNode<T>*)temp);
    } 
    void insert_before(const DoublyNode<T>* at, const T data) {
        if (!in_list(at)) throw std::invalid_argument("Node address could not be found.");
        if (at == head){
           push_front(data); 
           return;
        } 
        DoublyNode<T>* pred = head;
        for (; pred->next != at; pred = pred->next);
        pred->next = new DoublyNode<T>(data, pred->next, pred);
    }
    void insert_before(const uint64_t index, const T data) {
        if (!index){
           push_front(data); 
           return;
        } 
        DoublyNode<T>* pred = head;
        const DoublyNode<T>* temp = this->operator[](index);
        for (; pred->next != temp; pred = pred->next);
        pred->next = new DoublyNode<T>(data, pred->next, pred); 
    }
    void append(const SinglyLinked<T>& other) noexcept {
        DoublyNode<T>* tail = get_back();
        bool first = true;
        other.for_each([this, &tail, &first](const T& data){
            if (!tail && first) {
                this->push_front(data);
                first = false;
                tail = get_back();
            } 
            else {
                tail->next = new DoublyNode<T>(data, nullptr, tail->next);
                tail = tail->next;
            }
        });
    }
    void merge(DoublyLinked<T>& other, const bool&& ensure_sort = false) noexcept {
        if (other.empty()) return;
        if (empty()) append(other);
        else {
            DoublyNode<T>* o_curr = other.head, *curr = head, *head_ref = head;
            if (o_curr->data < head_ref->data) {
                push_front(o_curr->data);
                curr = head;
                o_curr = o_curr->next;
                while (o_curr && o_curr->data < head_ref->data) {
                    quick_insert_after(curr, o_curr->data);
                    curr = curr->next;
                    o_curr = o_curr->next;
                }
                curr = head_ref;
            }
            while (o_curr) {
                if (o_curr->data > head_ref->data) {
                    while (head_ref->next && head_ref->next->data < o_curr->data) head_ref = head_ref->next;
                } 
                quick_insert_after(head_ref, o_curr->data);
                o_curr = o_curr->next;
            }
        }
        if (ensure_sort) sort();
    }
    void sort() noexcept override {
        if (empty()) return;
        if (!head->next) return;
        while (true) {
            bool sorted = true;
            for (DoublyNode<T>* pred = head, *curr = head->next; curr;) {
                if (pred->data > curr->data) {
                    sorted = false;
                    DoublyNode<T>::swap(pred, curr);
                }
                pred = curr;
                curr = curr->next;
            }
            if (sorted) break;
        }  
    }
    bool erase_where(const T value) noexcept override {
        if (empty()) return false;
        if (head->data == value) {
            pop_front();
            return true;
        } 
        else {
            for (DoublyNode<T>*curr = head->next; curr; curr = curr->next) {
                if (curr->data == value) {
                    curr->pred->next = curr->next;
                    delete curr;
                    return true;
                }
            }
        }
        return false;
    }
    void erase(const SinglyNode<T>* node) {
        if (empty()) return;
        if (node == head) pop_front();
        for (DoublyNode<T>*curr = head->next; curr; curr = curr->next) {
            if (curr == node) {
                curr->pred->next = curr->next;
                delete curr;
                break;
            } 
        }
    }
};

#endif