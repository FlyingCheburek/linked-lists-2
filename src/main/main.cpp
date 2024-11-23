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
    SinglyLinked<int> list;
    DoublyLinked<int> list2;
    CircularSinglyLinked<int> list3;
    CircularDoublyLinked<int> list4;
    return 0;
}