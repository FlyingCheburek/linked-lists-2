#include "linked_list/doubly_linked.hpp"
#include <iostream>

// for debug purposes 
template<typename T>
inline void print_item(const T& i) noexcept {
    std::cout << i << "\n";
}
#define _BRK std::cout<<"\n"
// ...................

int main() {
    DoublyLinked<int> list({1,2,3,4,5,6,7,8,9,10}), list2(list);
    list2.for_each(print_item<int>);
    _BRK;
    
    return 0;
}