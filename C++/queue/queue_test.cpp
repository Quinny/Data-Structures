#include "queue.h"
#include <iostream>

int main() {
    queue<int> q;
    for (int i = 0; i < 10; ++i)
        q.push(i);

    while (!q.empty())
        std::cout << q.pop() << std::endl;
    return 0;
}
