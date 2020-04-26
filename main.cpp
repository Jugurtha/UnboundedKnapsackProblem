#include <iostream>
#include "BranchAndBound.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Objects objects{ {10,60}, {20,100}, {30,120}};
    BranchAndBound bb(50,objects);
    auto result = bb.search();
    std::cout << "Value : " << result.value << "\nSet : {\t";
    for(auto e : result.tuple)
        std::cout << e << "\t";
    std::cout << "}";
    return 0;
}