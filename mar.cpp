#include <iostream>
#include <set>
#include <cmath>
#include <queue>
#include <algorithm>

int waga(char typ, int U) {
    if (typ == 'U') {
        return U + 1;
    } else if (typ == '<' || typ == '>') {
        return 0;
    } else {
        return 1;
    }
}

int floor_log2(int n) {
    int res = 0;
    int a = 1;
    while (a * 2 <= n) {
        res++;
        a = a * 2;
    }

    return res;
}

typedef std::pair<int, std::pair<int, int>> pair;

int main() {

    int n, K, U;
    std::cin >> n >> K >> U;

    const int INF = std::numeric_limits<int>::max();

    char tor[n];
    int wagi[n];

    int log = floor_log2(n);

    for (int i = 0; i < n; i++) {
        char aux;
        std::cin >> aux;
        tor[i] = aux;
        wagi[i] = waga(aux, U);
    }
    int d[n][log+1];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < log + 1; j++) {
            d[i][j] = INF;
        }
    }
    d[0][0] = 0;

    std::priority_queue<pair, std::vector<pair>, std::greater<pair>> dijkstraQueue;

    dijkstraQueue.push(pair(0, std::pair<int, int>(0, 1)));

    while (!dijkstraQueue.empty()) {
        std::pair<int, int> node = dijkstraQueue.top().second;
        int dist = dijkstraQueue.top().first;
        dijkstraQueue.pop();
        int i = node.first;

        if (dist == INF) {
            continue;
        }
        char typ = tor[i];
        int waga = wagi[i];

        std::pair<int, int> s1 = std::pair<int, int>(-1, -1);
        std::pair<int, int> s2 = std::pair<int, int>(-1, -1);

        switch (typ) {
            case '.':
                if (i + 1 < n) {
                    if (tor[i+1] == '*') {
                        s1 = std::pair<int, int>(i + 1, std::min(node.second + 1, log + 1));
                    } else {
                        s1 = std::pair<int, int>(i + 1, node.second);
                    }
                }
                if (i + (1 << node.second) < n) {
                    if (tor[i+(1 << node.second)] == '*') {
                        s2 = std::pair<int, int>(i + (1 << node.second), std::min(node.second + 1, log + 1));
                    } else {
                        s2 = std::pair<int, int>(i + (1 << node.second), node.second);
                    }
                }
                break;
            case '*':
                if (i + 1 < n) {
                    if (tor[i+1] == '*') {
                        s1 = std::pair<int, int>(i + 1, std::min(node.second + 1, log + 1));
                    } else {
                        s1 = std::pair<int, int>(i + 1, node.second);
                    }
                }
                if (i + (1 << node.second) < n) {
                    if (tor[i+(1 << node.second)] == '*') {
                        s2 = std::pair<int, int>(i + (1 << node.second), std::min(node.second + 1, log + 1));
                    } else {
                        s2 = std::pair<int, int>(i + (1 << node.second), node.second);
                    }
                }
                break;
            case '#':
                break;
            case '>':
                if (i + K < n) {
                    if (tor[i+K] == '*') {
                        s1 = std::pair<int, int>(i + K, std::min(node.second + 1, log + 1));
                    } else {
                        s1 = std::pair<int, int>(i + K, node.second);
                    }
                }
                break;
            case '<':
                if (i - K >= 0) {
                    if (tor[i-K] == '*') {
                        s1 = std::pair<int, int>(i - K, std::min(node.second + 1, log + 1));
                    } else {
                        s1 = std::pair<int, int>(i - K, node.second);
                    }
                }
                break;
            case 'U':
                if (i + 1 < n) {
                    if (tor[i+1] == '*') {
                        s1 = std::pair<int, int>(i + 1, std::min(node.second + 1, log + 1));
                    } else {
                        s1 = std::pair<int, int>(i + 1, node.second);
                    }
                }
                if (i + (1 << node.second) < n) {
                    if (tor[i+(1 << node.second)] == '*') {
                        s2 = std::pair<int, int>(i + (1 << node.second), std::min(node.second + 1, log + 1));
                    } else {
                        s2 = std::pair<int, int>(i + (1 << node.second), node.second);
                    }
                }
                break;
            default:break;
        }

        if (s1.first >= 0 && s1.second >= 1) {
            int log_s1 = s1.second;
            if (log_s1 > 0 && log_s1 <= log+1 && d[s1.first][log_s1-1] > dist + waga) {
                d[s1.first][log_s1-1] = dist + waga;
                dijkstraQueue.push(pair(d[s1.first][log_s1-1], std::pair<int, int>(s1.first, s1.second)));
            }
        }
        if (s2.first >= 0 && s2.second >= 1) {
            int log_s2 = s2.second;
            if (log_s2 > 0 && log_s2 <= log + 1 && d[s2.first][log_s2-1] > dist + waga) {
                d[s2.first][log_s2-1] = dist + waga;
                dijkstraQueue.push(pair(d[s2.first][log_s2-1], std::pair<int, int>(s2.first, s2.second)));
            }
        }
    }



    int minimum = INF;
    for (int i = 0; i < log + 1; i++) {
        if (d[n-1][i] < minimum) {
            minimum = d[n-1][i];
        }
    }

    if (minimum == INF) {
        std::cout << -1;
    } else {
        std::cout << minimum;
    }

    return 0;
}