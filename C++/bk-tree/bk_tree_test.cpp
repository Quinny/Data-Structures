#include "bk_tree.h"
#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    if (argc == 1) {
        std::cout << "Enter a dictionary file" << std::endl;
        return 0;
    }
    qap::bk_tree t;
    std::ifstream dict(argv[1]);
    for (std::string s; dict >> s; )
        t.insert(s);
    std::cout << "file imported, do lookups now" << std::endl;
    std::string s;
    int n;
    while (true) {
        std::cin >> s >> n;
        auto v = t.find_all(s, n);
        std::cout << "-------------" << std::endl;
        std::cout << v.size() << " matches found" << std::endl;
        for (auto i : v)
            std::cout << i << std::endl;
        std::cout << "------------" << std::endl;
    }
    return 0;
}
