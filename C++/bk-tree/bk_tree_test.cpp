#include "bk_tree.h"
#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    /*std::string dict_file;
    if (argc == 1)
        dict_file = "/usr/share/dict/words";
    else
        dict_file = argv[1];
    qap::bk_tree<> t;
    std::ifstream dict(dict_file);
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
    }*/
    
    qap::bk_tree<int, std::vector> t2;
    t2.insert({1,2,3});
    t2.insert({3,2,1});

    auto x = t2.find_all({1,2,4}, 1);
    for (auto i : x) {
        for (auto j : i)
            std::cout << j << " ";
        std::cout << std::endl;
    }
    return 0;
}
