#include "linked_list/circular_singly_linked.hpp"
#include <iostream>

// for debug purposes 
template<typename T>
inline void print_item(const T& i) noexcept {
    std::cout << i << "\n";
}
#define _BRK std::cout<<"\n"
// ...................

int main() {
    CircularSinglyLinked<int> list({1, 2, 3, 4, 5, 6, 7});
    list.for_each(print_item<int>);
    _BRK;
    list.insert_before(uint64_t(2), -1);
    list.for_each(print_item<int>);
    _BRK;
    return 0;
}