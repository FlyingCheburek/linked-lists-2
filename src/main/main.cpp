#include "linked_list/linked_lists.hpp"
#include <iostream>

// for debug purposes 
template<typename T>
inline void print_item(const T& i) noexcept {
    std::cout << i << "\n";
}
#define _BRK std::cout<<"\n"
// ...................

int main() {
    CircularDoublyLinked<int> list;
    list.for_each(print_item<int>);
    _BRK;
    list.push_back(0);
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_front(-1);
    list.for_each(print_item<int>);
    _BRK;
    return 0;
}