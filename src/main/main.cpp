#include "linked_list/singly_linked.hpp"

// for debug purposes 
template<typename T>
inline void print_item(const T& i) noexcept {
    std::cout << i << "\n";
}


int main() {
    SinglyLinked<int> list({1, 2, 3});
    SinglyLinked<int> list2(list);
    list.for_each(print_item<int>);
    std::cout << "\n\n";
    list2.for_each(print_item<int>);
    return 0;
}