#include "linked_list/singly_linked.hpp"

// for debug purposes 
inline void print_item(const int& i) noexcept {
    std::cout << i << "\n";
}


int main() {
    SinglyLinked<int> list({1, 2, 3});
    
    return 0;
}