#include <iostream>
#include "linked_list/singly_linked.hpp"

int main() {
    SinglyLinked<int> list;
    try {
        list.push_front(1);
        list.push_front(2);
        list.push_front(3);
        list.push_front(4);
        list.push_front(5);
        
    } catch (std::exception err) {
        std::cerr << err.what();
    }
    return 0;
}