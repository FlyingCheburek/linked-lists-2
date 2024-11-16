#include <vector>
#include <functional>
#include <stdexcept>

#ifndef SINGLY_LINKED_HPP

template<class T>
struct SinglyNode {
    T data;
    SinglyNode<T>* next = nullptr;
    SinglyNode() noexcept {  }
    SinglyNode(const T data, SinglyNode<T>* next = nullptr) noexcept : data(data), next(next) {  }
    inline static void swap(SinglyNode<T>* left, SinglyNode<T>* right) noexcept {
        T temp = left->data;
        left->data = right->data;
        right->data = temp;
    } 
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
    bool in_list(const SinglyNode<T>* node) const noexcept {
        if (empty()) return false;
        for (SinglyNode<T>* i = head; i; i = i->next) {
            if (node == i) return true;
        }
        return false;
    }
    void quick_insert_after(const SinglyNode<T>* at, const T data) noexcept {
        ((SinglyNode<T>*)at)->next = new SinglyNode<T>(data, at->next);
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
    SinglyLinked(const SinglyLinked<T>& other) noexcept {
        other.for_each([this](const T& item){
            this->push_front(item);
        });
        reverse();
    }
    ~SinglyLinked() {
        for (SinglyNode<T>* node = head, *temp; node;) {
            temp = node;
            node = node->next;
            delete temp;
        }
    }
    const SinglyNode<T>* operator[](const uint64_t index) const {
        if (!index) return head;
        SinglyNode<T>* node = head;
        for (uint64_t x=1; x <= index; x++) {
            if (!node) throw std::out_of_range("List index out of range.");
            node = node->next;
        }
        if (!node) throw std::out_of_range("List index out of range.");
        return node;
    }
    inline uint64_t size() const noexcept {
        uint64_t siz = 0;
        for (SinglyNode<T>* i = head; i; i = i->next) siz++;
        return siz;
    }
    void reverse() noexcept {
        if (empty()) return;
        if (!head->next) return;
        SinglyNode<T>* pred = nullptr;
        for (SinglyNode<T> *curr = head, *next = pred; curr;) {
            next = curr->next;
            curr->next = pred;
            pred = curr;
            curr = next;
        }
        head = pred;
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
    void insert_after(const SinglyNode<T>* at, const T data) {
        if (!in_list(at)) throw std::invalid_argument("Node address could not be found.");
        ((SinglyNode<T>*)at)->next = new SinglyNode<T>(data, at->next);
    }
    void insert_after(const uint64_t index, const T data) {
        SinglyNode<T>* temp = (SinglyNode<T>*)this->operator[](index);
        temp->next = new SinglyNode<T>(data, temp->next);
    }
    void insert_before(const SinglyNode<T>* at, const T data) {
        if (!in_list(at)) throw std::invalid_argument("Node address could not be found.");
        if (at == head){
           push_front(data); 
           return;
        } 
        SinglyNode<T>* pred = head;
        for (; pred->next != at; pred = pred->next);
        pred->next = new SinglyNode<T>(data, pred->next); 
    }
    void insert_before(const uint64_t index, const T data) {
        if (!index){
           push_front(data); 
           return;
        } 
        SinglyNode<T>* pred = head;
        const SinglyNode<T>* temp = this->operator[](index);
        for (; pred->next != temp; pred = pred->next);
        pred->next = new SinglyNode<T>(data, pred->next); 
    }
    void append(const SinglyLinked<T>& other) {
        SinglyNode<T>* tail = get_back();
        bool first = true;
        other.for_each([this, &tail, &first](const T& data){
            if (!tail && first) {
                this->push_front(data);
                first = false;
                tail = get_back();
            } 
            else {
                tail->next = new SinglyNode<T>(data);
                tail = tail->next;
            }
        });
    }
    void merge(SinglyLinked<T>& other, const bool&& ensure_sort = false) noexcept {
        if (other.empty()) return;
        if (empty()) append(other);
        else {
            SinglyNode<T>* o_curr = other.head, *curr = head, *head_ref = head;
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
    void sort() noexcept {
        if (empty()) return;
        if (!head->next) return;
        while (true) {
            bool sorted = true;
            for (SinglyNode<T>* pred = head, *curr = head->next; curr;) {
                if (pred->data > curr->data) {
                    sorted = false;
                    SinglyNode<T>::swap(pred, curr);
                }
                pred = curr;
                curr = curr->next;
            }
            if (sorted) break;
        }  
    }
    bool erase_where(const T value) noexcept {
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
    inline void erase_all_where(const T value) noexcept { while(erase_where(value)); } 
    void erase(const SinglyNode<T>* node) {
        if (empty()) return;
        if (node == head) pop_front();
        for (SinglyNode<T>* pred = head, *curr = head->next; curr; pred = curr, curr = curr->next) {
            if (curr == node) {
                pred->next = curr->next;
                delete curr;
                break;
            } 
        }
    }
};

#endif