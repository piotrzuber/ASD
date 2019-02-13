#include <iostream>
#include <cassert>

using namespace std;

int links[20][500001];

int pow2(int pow) {
    return 1 << pow;
}

void depthCount(int *depth, const int *left, const int *right, int d, int idx, int n) {
    depth[idx] = d;

//    assert(left[idx] > 0 && left[idx] <= n);
    if (left[idx] != -1) {
        depthCount(depth, left, right, d+1, left[idx], n);
    }
//    assert(right[idx] > 0 && right[idx] <= n);
    if (right[idx] != -1) {
        depthCount(depth, left, right, d+1, right[idx], n);
    }
}

int ancestor(int v, int h, int logn, int n, int links[20][500001]) {
    int res = v, i = logn;
//    assert(h > 0);
    while (h > 0) {
        if (pow2(i) > h) {
            i--;
        } else {
            assert(i <= 19);
//            assert(1 <= res && 500000 >= res);
            res = links[i][res];
            h = h - pow2(i);
        }
//        assert(h > 0);
    }

    return res;
}

int lca(int v, int w, const int *depth, int logn, int n, int links[20][500001], const int *parent) {
//    assert(0 < v && v <= n);
//    assert(0 < w && w <= n);
    int dw = depth[w], dv = depth[v];

    if (dw < dv) {
        v = ancestor(v, dv - dw, logn, n, links);
    } else if (dw > dv) {
        w = ancestor(w, dw - dv, logn, n, links);
    }

    if (w == v) {
        return w;
    }

    int i = logn;
    while (i >= 0) {
//        assert(i>= 0 && i <= logn);
//        assert(w> 0 && w <= n);
//        assert(v > 0 && v <= n);
        if (links[i][w] != links[i][v]) {
            w = links[i][w];
            v = links[i][v];
        }

        i--;
    }

//    assert(w > 0 && w <= n);
    return parent[w];
}

void lowestNode(pair<int, int> *fardown, const int *left, const int *right, int idx, int n) {
    pair<int, int> p = pair<int, int>(0, idx);
    pair<int, int> p1 = pair<int, int>(-1, -1);
    pair<int, int> p2 = pair<int, int>(-1, -1);

//    assert(left[idx] > 0 && left[idx] < n +1);
    if (left[idx] != -1) {
        lowestNode(fardown, left, right, left[idx], n);
        p1 = pair<int, int>(fardown[left[idx]].first + 1, fardown[left[idx]].second);
    }

//    assert(right[idx] > 0 && right[idx] < n + 1);
    if (right[idx] != -1) {
        lowestNode(fardown, left, right, right[idx], n);
        p2 = pair<int, int>(fardown[right[idx]].first + 1, fardown[right[idx]].second);
    }

//    assert(idx > 0 && idx < n + 1);
    fardown[idx] = p;
    if (p1.first > fardown[idx].first) {
        fardown[idx] = p1;
    }
    if (p2.first > fardown[idx].first) {
        fardown[idx] = p2;
    }
}

void highestNode(pair<int, int> *fardown, pair<int, int> *farup, const int *parent, const int *left, const int *right, int idx, int n) {

    pair<int, int> p = pair<int, int>(0, idx);
    pair<int, int> p1 = pair<int, int>(-1, -1);
    pair<int, int> p2 = pair<int, int>(-1, -1);
    int sibling = -1;

//    assert(parent[idx] > 0 && parent[idx] < n + 1);
    if (parent[idx] != -1) {
        p1.first = farup[parent[idx]].first + 1;
        p1.second = farup[parent[idx]].second;

        sibling = left[parent[idx]] == idx ? right[parent[idx]] : left[parent[idx]];
    }

//    assert(sibling > 0 && sibling < n + 1);
    if (sibling != -1) {
        p2.first = fardown[sibling].first + 2;
        p2.second = fardown[sibling].second;
    }

//    assert(idx > 0 && idx < n + 1);
    farup[idx] = p;
    if (p1.first > farup[idx].first) {
        farup[idx] = p1;
    }
    if (p2.first > farup[idx].first) {
        farup[idx] = p2;
    }

//    assert(left[idx] > 0 && left[idx] < n + 1);
    if (left[idx] != -1) {
        highestNode(fardown, farup, parent, left, right, left[idx], n);
    }
//    assert(right[idx] > 0 && right[idx] < n + 1);
    if (right[idx] != -1) {
        highestNode(fardown, farup, parent, left, right, right[idx], n);
    }
}

int dist(int idx, int d, const pair<int, int> *furthest, const int *depth, int logn, int n, int links[20][500001], const int *parent) {

    if (d > furthest[idx].first) {
        return -1;
    }

//    assert(idx > 0 && idx < n + 1);
//    assert(furthest[idx].second > 0 && furthest[idx].second < n + 1);

    int comAnc = lca(idx, furthest[idx].second, depth, logn, n, links, parent);

//    assert(comAnc > 0 && comAnc < n + 1);
    int d1 = depth[idx] - depth[comAnc];
    int d2 = depth[furthest[idx].second] - depth[comAnc];

    if (d <= d1) {
        return ancestor(idx, d, logn, n, links);
    } else {
        return ancestor(furthest[idx].second, d1 + d2 - d, logn, n, links);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    int l, r;
    cin >> n;

    int left[n+1], right[n+1], parent[n+1], depth[n+1];
    pair<int, int> furthest[n+1], fardown[n+1], farup[n+1];

    for (int i = 0; i < n + 1; i++) {
        left[i] = right[i] = parent[i] = depth[i] = -1;
    }

    for (int i = 1; i <= n; i++) {
        cin >> l >> r;

        left[i] = l;
        right[i] = r;

        parent[l] = parent[r] = i;
    }

    depthCount(depth, left, right, 0, 1, n);

    int logn = 0;
    while ((1 << logn) <= n) logn++;
    logn--;

    for (int idx = 1; idx <= n; idx++) {
        links[0][idx] = parent[idx];
    }

    for (int i = 1; i <= 19; i++) {
        for (int v = 1; v < n+1; v++) {
            if (links[i-1][v] != -1) {
                links[i][v] = links[i-1][links[i-1][v]];
            } else {
                links[i][v] = -1;
            }

        }
    }

    lowestNode(fardown, left, right, 1, n);
    highestNode(fardown, farup, parent, left, right, 1, n);

    for (int i = 1; i <= n; i++) {
        furthest[i] = fardown[i].first > farup[i].first ? fardown[i] : farup[i];
    }

    int m, idx, d;
    cin >> m;

    for (int i = 0; i < m; i++) {
        cin >> idx >> d;

        cout << dist(idx, d, furthest, depth, logn, n, links, parent) << endl;
    }
}