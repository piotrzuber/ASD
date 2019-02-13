#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <limits>

#define MAX 100000

bool comp(std::pair<int, int> p1, std::pair<int, int> p2) {
    if (p1.first == p2.first) {
        return p1.second < p2.second;
    }

    return p1.first < p2.first;
}

struct Node {
    std::pair<int, int> minMax; // para (min, max)
    std::pair<int, int> Ids; // para (min_id, max_id)
    std::set<std::pair<int, int>, bool (*)(std::pair<int, int>, std::pair<int, int>)> uppers; // para (upper, index)
};

class SegTree {
  private:
    size_t size;
  public:
    std::vector<Node> tree;
    size_t M;
    Node empty;

    SegTree() {
        empty.minMax.first = std::numeric_limits<int>::max();
        empty.minMax.second = 0;
        empty.Ids.first = empty.Ids.second = -1;
        empty.uppers = std::set<std::pair<int, int>, bool (*)(std::pair<int, int>, std::pair<int, int>)>(comp);

        size = 1;
        while (size < MAX) size *= 2;

        M = size;
        size = 2 * M;
        tree.assign(size, empty);
    }

    void insert(int begin, int end, int idx) {
        size_t v = begin + M - 1;

//        std::cout << v << " " << tree[v].minMax.first << " " << tree[v].minMax.second << std::endl;
        tree[v].uppers.insert(std::make_pair(end, idx));

        if (end < tree[v].minMax.first) {
            tree[v].minMax.first = end;
            tree[v].Ids.first = idx;

            while (v != 1) {
                v /= 2;

                if (tree[2 * v].minMax.first < tree[2 * v + 1].minMax.first) {
                    tree[v].minMax.first = tree[2 * v].minMax.first;
                    tree[v].Ids.first = tree[2 * v].Ids.first;
                } else {
                    tree[v].minMax.first = tree[2 * v + 1].minMax.first;
                    tree[v].Ids.first = tree[2 * v + 1].Ids.first;
                }
            }

            v = begin + M - 1;
        }

        if (end > tree[v].minMax.second) {
            tree[v].minMax.second = end;
            tree[v].Ids.second = idx;

            while (v != 1) {
                v /= 2;

                if (tree[2 * v].minMax.second > tree[2 * v + 1].minMax.second) {
                    tree[v].minMax.second = tree[2 * v].minMax.second;
                    tree[v].Ids.second = tree[2 * v].Ids.second;
                } else {
                    tree[v].minMax.second = tree[2 * v + 1].minMax.second;
                    tree[v].Ids.second = tree[2 * v + 1].Ids.second;
                }
            }

            v = begin + M - 1;
        }

//        std::cout << v << " " << tree[v].minMax.first << " " << tree[v].minMax.second << std::endl;
//        for (const auto &upper : tree[v].uppers) {
//            std::cout << upper.first << " " << upper.second << std::endl;
//        }
    }

    void remove(int begin, int end, int idx) {
        size_t v = begin + M - 1;

//        std::cout << v << " " << tree[v].minMax.first << " " << tree[v].minMax.second << std::endl;
        tree[v].uppers.erase(std::make_pair(end, idx));

        if (tree[v].uppers.empty()) {
            tree[v] = empty;
        } else {
            if (end == tree[v].minMax.first) {
                tree[v].minMax.first = (*tree[v].uppers.begin()).first;
                tree[v].Ids.first = (*tree[v].uppers.begin()).second;
            }
            if (end == tree[v].minMax.second) {
                tree[v].minMax.second = (*tree[v].uppers.rbegin()).first;
                tree[v].Ids.second = (*tree[v].uppers.rbegin()).second;
            }
        }

        while (v != 1) {
            v /= 2;

            if (tree[2 * v].minMax.first < tree[2 * v + 1].minMax.first) {
                tree[v].minMax.first = tree[2 * v].minMax.first;
                tree[v].Ids.first = tree[2 * v].Ids.first;
            } else {
                tree[v].minMax.first = tree[2 * v + 1].minMax.first;
                tree[v].Ids.first = tree[2 * v + 1].Ids.first;
            }
        }

        v = begin + M - 1;

        while (v != 1) {
            v /= 2;

            if (tree[2 * v].minMax.second > tree[2 * v + 1].minMax.second) {
                tree[v].minMax.second = tree[2 * v].minMax.second;
                tree[v].Ids.second = tree[2 * v].Ids.second;
            } else {
                tree[v].minMax.second = tree[2 * v + 1].minMax.second;
                tree[v].Ids.second = tree[2 * v + 1].Ids.second;
            }
        }

        v = begin + M - 1;

//        std::cout << v << " " << tree[v].minMax.first << " " << tree[v].minMax.second << std::endl;
//        for (auto it = tree[v].uppers.begin(); it != tree[v].uppers.end(); it++) {
//            std::cout << (*it).first << " " << (*it).second << std::endl;
//        }
    }

    std::pair<int, int> findIn(int begin, int end){
        size_t vb = M + begin - 1, ve = M + end - 1;

        std::pair<int, int> res = tree[vb].minMax.first < tree[ve].minMax.first
                ? std::make_pair(tree[vb].minMax.first, tree[vb].Ids.first)
                : std::make_pair(tree[ve].minMax.first, tree[ve].Ids.first);

        while (vb / 2 != ve / 2) {
            if (vb % 2 == 0 && tree[vb+1].minMax.first <= std::min(end, res.first)) {
                res.second = tree[vb+1].Ids.first;
                res.first = tree[vb+1].minMax.first;
            }
            if (ve % 2 == 1 && tree[ve-1].minMax.first <= std::min(end, res.first)) {
                res.second = tree[ve-1].Ids.first;
                res.first = tree[ve-1].minMax.first;
            }

            vb /= 2; ve /= 2;
        }

        if (res.first > end) {
            res.first = std::numeric_limits<int>::max();
            res.second = -1;
        }

        return res;
    }

    std::pair<int, int> findOver(int begin, int end) {
        size_t vb = M, ve = M + begin - 1;

        std::pair<int, int> res = tree[vb].minMax.second > tree[ve].minMax.second
                ? std::make_pair(tree[vb].minMax.second, tree[vb].Ids.second)
                : std::make_pair(tree[ve].minMax.second, tree[ve].Ids.second);

        while (vb / 2 != ve / 2) {
            if (vb % 2 == 0 && tree[vb+1].minMax.second >= std::min(end, res.first)) {
                res.second = tree[vb+1].Ids.second;
                res.first = tree[vb+1].minMax.second;
            }
            if (ve % 2 == 1 && tree[ve-1].minMax.second >= std::min(end, res.first)) {
                res.second = tree[ve-1].Ids.second;
                res.first = tree[ve-1].minMax.second;
            }

            vb /= 2; ve /= 2;
        }

        if (res.first < end) {
            res.first = std::numeric_limits<int>::max();
            res.second = -1;
        }

        return res;
    }

    std::pair<int, int> findNone(int begin, int end) {
        std::pair<int, int> resIn1 = std::make_pair(std::numeric_limits<int>::max(), -1);
        std::pair<int, int> resIn2 = std::make_pair(std::numeric_limits<int>::max(), -1);

        if (begin > 1) {
            resIn1 = findIn(1, begin - 1);
            if (resIn1.second > 0) {
                return resIn1;
            }
        }
        if (end < MAX) {
            resIn2 = findIn(end + 1, MAX);
            return resIn2;
        }

        return resIn1;
    }

    std::pair<int, int> findSome(int begin, int end) {
        size_t vb = M, ve = M + end - 1;

        std::pair<int, int> res = tree[vb].minMax.second > tree[ve].minMax.second
                ? std::make_pair(tree[vb].minMax.second, tree[vb].Ids.second)
                : std::make_pair(tree[ve].minMax.second, tree[ve].Ids.second);

        while (vb / 2 != ve / 2) {
            if (vb % 2 == 0 && tree[vb+1].minMax.second >= std::min(begin, res.first)) {
                res.second = tree[vb+1].Ids.second;
                res.first = tree[vb+1].minMax.second;
            }
            if (ve % 2 == 1 && tree[ve-1].minMax.second >= std::min(begin, res.first)) {
                res.second = tree[ve-1].Ids.second;
                res.first = tree[ve-1].minMax.second;
            }

            vb /= 2; ve /= 2;
        }

        if (res.first < begin) {
            res.first = std::numeric_limits<int>::max();
            res.second = -1;
        }

        return res;
    }

    int findSession(const std::string &type, int begin, int end, std::pair<int, int> *sessions) {
        std::pair<int, int> res;

        if (type == "in") {
            res =  findIn(begin, end);
        } else if (type == "over") {
            res = findOver(begin, end);
        } else if (type == "none") {
            res =  findNone(begin, end);
        } else if (type == "some") {
            res =  findSome(begin, end);
        }

        if (res.first < std::numeric_limits<int>::max() && res.second > 0) {
            remove(sessions[res.second - 1].first, res.first, res.second);
        }

        return res.second < std::numeric_limits<int>::max() ? res.second : -1;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    SegTree segTree{};
    std::pair<int, int> sessions[n];
    int begin, end;
    for (int i = 0; i < n; i++) {
        std::cin >> begin >> end;

        segTree.insert(begin, end, i + 1);
        sessions[i] = std::make_pair(begin, end);
    }

    int q;
    std::cin >> q;

    std::string type;
    for (int i = 0; i < q; i++) {
        std::cin >> type >> begin >> end;

        std::cout << segTree.findSession(type, begin, end, sessions) << " ";
        std::cout.flush();
    }

    return 0;
}