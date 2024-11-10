#include "linked_list/singly_linked.hpp"

// for debug purposes 
inline void print_item(const int& i) noexcept {
    std::cout << i << "\n";
}


int main() {
    SinglyLinked<int> list({1, 1, 2, 2, 1, 5, 5, 1});
    list.for_each(print_item);
    return 0;
}