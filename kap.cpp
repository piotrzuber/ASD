#include <iostream>
#include <cmath>
#include <queue>
#include <algorithm>
#include <map>

class Island {
  public:
    int id;
    int x;
    int y;

    Island() {
        this->id = 0;
        this->x = 0;
        this->y = 0;
    }

    static bool compX(const Island &i1, const Island &i2) {
        if (i1.x == i2.x) {
            return i1.y < i2.y;
        }
        return i1.x < i2.x;
    }

    static bool compY(const Island &i1, const Island &i2) {
        if (i1.y == i2.y) {
            return i1.x < i2.x;
        }
        return i1.y < i2.y;
    }
};

bool compX(std::pair<int, int> p1, std::pair<int, int> p2) {
    if (p1.first == p2.first) {
        return p1.second < p2.second;
    }
    return p1.first < p2.first;
}

bool compY(std::pair<int, int> p1, std::pair<int, int> p2) {
    if (p1.second == p2.second) {
        return p1.first < p2.first;
    }
    return p1.second < p2.second;
}

typedef std::pair<int, std::pair<int, int>> data_pair;

int main() {

    int n;
    std::cin >> n;

    Island islands[n];
    std::map<std::pair<int, int>, int, bool(*)(std::pair<int, int>, std::pair<int, int>)> sortedX = std::map<std::pair<int, int>, int, bool(*)(std::pair<int, int>, std::pair<int, int>)>(compX);
    std::map<std::pair<int, int>, int, bool(*)(std::pair<int, int>, std::pair<int, int>)> sortedY = std::map<std::pair<int, int>, int, bool(*)(std::pair<int, int>, std::pair<int, int>)>(compY);
    int dist[n];

    int x, y;
    for (int i = 0; i < n; i++) {
        std::cin >> x >> y;
        islands[i].id = i + 1;
        islands[i].x = x;
        islands[i].y = y;
        sortedX[std::make_pair(x, y)] = i + 1;
        sortedY[std::make_pair(x, y)] = i + 1;
        dist[i] = std::numeric_limits<int>::max();
    }

    dist[0] = 0;

    std::priority_queue<data_pair, std::vector<data_pair>, std::greater<data_pair>> queue;
    queue.push(data_pair(0, std::make_pair(islands[0].x, islands[0].y)));

    while (!queue.empty()) {
        std::pair<int, int> node = queue.top().second;
        int d = queue.top().first;
        queue.pop();

        auto itX = sortedX.find(node);
        auto aux_itX = itX;
        auto itY = sortedY.find(node);
        auto aux_itY = itY;

        if (itX != sortedX.end()) {
            if (++aux_itX != sortedX.end()) {
                if (dist[(aux_itX)->second-1] > d + abs(itX->first.first - aux_itX->first.first)) {
                    dist[(aux_itX)->second-1] = d + abs(itX->first.first - aux_itX->first.first);
                    queue.push(data_pair(dist[(aux_itX->second-1)], std::pair<int, int>(aux_itX->first)));
                }
            }
            aux_itX = itX;
            if (aux_itX != sortedX.begin()) {
                --aux_itX;
                if (dist[(aux_itX)->second-1] > d + abs(itX->first.first - aux_itX->first.first)) {
                    dist[(aux_itX)->second-1] = d + abs(itX->first.first - aux_itX->first.first);
                    queue.push(data_pair(dist[(aux_itX->second-1)], std::pair<int, int>(aux_itX->first)));
                }
            }
        }
        if (itY != sortedY.end()) {
            if (++aux_itY != sortedY.end()) {
                if (dist[(aux_itY)->second-1] > d + abs(itY->first.second - aux_itY->first.second)) {
                    dist[(aux_itY)->second-1] = d + abs(itY->first.second - aux_itY->first.second);
                    queue.push(data_pair(dist[(aux_itY->second-1)], std::pair<int, int>(aux_itY->first)));
                }
            }
            aux_itY = itY;
            if (aux_itY != sortedY.begin()) {
                --aux_itY;
                if (dist[(aux_itY->second-1)] > d + abs(itY->first.second - aux_itY->first.second)) {
                    dist[(aux_itY->second-1)] = d + abs(itY->first.second - aux_itY->first.second);
                    queue.push(data_pair(dist[(aux_itY->second-1)], std::pair<int, int>(aux_itY->first)));
                }
            }
        }
    }

    std::cout << dist[n-1];

    return 0;
}