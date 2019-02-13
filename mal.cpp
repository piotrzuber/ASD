#include <iostream>

using namespace std;

typedef pair<int, int> node;    // <pomalowane, kolor> kolor: 0 - czarny, 1 biały, -1 - spotkany bez jednolitego koloru

void growBranches(int idx, node* tree, int fullSize) {
    if (tree[idx].second > -1 && 2 * idx < fullSize) { // spotkany, nie w ostatnim rzędzie drzewa przedziaowego
        int type = tree[idx].second;
        tree[idx].second = -1;

        tree[2*(idx+1)-1].second = type;
        tree[2*(idx+1)].second = type;

        if (type == 0) {
            tree[2*(idx+1)-1].first = 0;
            tree[2*(idx+1)].first = 0;
        } else {
            tree[2*(idx+1)-1].first = tree[idx].first / 2;
            tree[2*(idx+1)].first = tree[idx].first / 2;
        }
    }
}

void color(int fullSize, node* tree, int left, int right, int type, int begin, int end, int idx) {
    if (right < begin || end < left || (tree[idx].second == type)) {
        return;
    }

    if (right >= end && left <= begin) {
        tree[idx].second = type;

        if (type == 0) {
            tree[idx].first = 0;
        } else {
            tree[idx].first = end - begin + 1;
        }
    } else {
        growBranches(idx, tree, fullSize);
        int half = (end + begin) / 2;

        if (2 * idx < fullSize) { // nie w ostatnim rzędzie
            color(fullSize, tree, left, right, type, begin, half, 2*(idx+1)-1);
            color(fullSize, tree, left, right, type, half+1, end, 2*(idx+1));
        }

        if (right >= end && left <= begin) {
            tree[idx].second = type;

            if (type == 0) {
                tree[idx].first = 0;
            } else {
                tree[idx].first = end - begin + 1;
            }
        } else {
            tree[idx].first = tree[2*(idx+1)-1].first + tree[2*(idx+1)].first;

            if (tree[2*(idx+1)-1].second == tree[2*(idx+1)].second) {
                tree[idx].second = tree[2*(idx+1)].second;
            }
        }
    }
}

int main() {

    int n, m;
    int left, right;
    char type;

    cin >> n >> m;

    int logCeil = 1;
    int fullSize;
    while (logCeil < n) {
        logCeil *= 2;
    }
    fullSize = 2 * logCeil - 1;

    node segTree[fullSize];
    segTree[0].first = 0;
    segTree[0].second = 0;

    for (int i = 0; i < m; i++) {
        cin >> left;
        cin >> right;
        cin >> type;

        color(fullSize, segTree, left - 1, right - 1, type == 'C' ? 0 : 1, 0, logCeil - 1, 0);
        cout << segTree[0].first << endl;
    }



    return 0;
}