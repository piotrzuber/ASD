#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

//void bfs(std::vector<int> *ins, std::vector<int> *outs, int *emps, int node) {
//    if (outs[node].empty()) {
//        return;
//    }
//    for (auto it = outs[node].begin(); it != outs[node].end(); it++) {
//        bfs(ins, outs, emps, *it);
//    }
//
//    for (auto it = outs[node].begin(); it != outs[node].end(); it++) {
//        if (emps[*it] < emps[node]) {
//            emps[*it] = emps[node];
//        }
//    }
//}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, k;
    std::cin >> n >> m >> k;

    if (!k) {
        std::cout << 0;
        return 0;
    }

    int emps[n+1];
    std::vector<int> outs[n+1];
    std::vector<int> ins[n+1];
    int din[n+1];
    for (int i = 1; i <= n; i++) {
        std::cin >> emps[i];
        din[i] = 0;
    }
    int in, out;
    for (int i = 0; i < m; i++) {
        std::cin >> in >> out;
        ins[in].push_back(out);
        outs[out].push_back(in);
        din[in]++;
    }

    std::queue<int> queue;

    for (int i = 1; i <= n; i++) {
        if (din[i] == 0) {
//            bfs(ins, outs, emps, i);
            queue.push(i);
        }
    }
    int node;
    while (!queue.empty()) {
        node = queue.front();
        queue.pop();
        for (auto it = outs[node].begin(); it != outs[node].end(); it++) {
            if (emps[*it] < emps[node]) {
                emps[*it] = emps[node];
            }
            din[*it]--;
            if (din[*it] == 0) {
                queue.push(*it);
            }
        }
    }

    std::sort(emps + 1, emps + n + 1);

    std::cout << emps[k];

    return 0;
}