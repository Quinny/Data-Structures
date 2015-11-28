#include "mutable_queue.h"
#include <iostream>
#include <vector>

#define INF (1 << 28)

const int n = 80;

std::vector<std::pair<int, int>> adj(std::pair<int, int> p) {
    std::vector<std::pair<int, int>> dv = {
        {1, 0},
        {0, 1},
        {-1, 0},
        {0, -1}
    };
    std::vector<std::pair<int, int>> ret;

    for (auto i: dv) {
        if (p.first + i.first >= 0 && p.second + i.second >= 0
                && p.first + i.first < n && p.second + i.second < n)
            ret.push_back({p.first + i.first, p.second + i.second});
    }
    return ret;
}

int main() {
    int cost[n][n];
    int dists[n][n];

    qap::mutable_queue<std::pair<int, int>> q;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> cost[i][j];
            dists[i][j] = INF;
        }
    }

    dists[0][0] = cost[0][0];
    q.update({{0, 0}, dists[0][0]});
    while (!q.empty()) {
        auto u = q.pop();
        for (auto i: adj(u.key)) {
            auto alt = dists[u.key.first][u.key.second] + cost[i.first][i.second];
            if (alt < dists[i.first][i.second]) {
                q.update({i, alt});
                dists[i.first][i.second] = alt;
            }
        }
    }
    std::cout << dists[n - 1][n - 1] << std::endl;
    return 0;
}
