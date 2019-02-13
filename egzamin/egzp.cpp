#include <iostream>
#include <set>
#include <algorithm>

struct Projekt {
    int p;
    int k;
    int w;

    Projekt() = default;

    Projekt (int _p, int _k, int _w) : p(_p), k(_k), w(_w) {}

    bool operator<(const Projekt &projekt2) {
        if (k == projekt2.k) {
            if (p == projekt2.p) {
                return w < projekt2.w;
            }

            return p < projekt2.p;
        }

        return k < projekt2.k;
    }
};

bool comp (const Projekt &p1, const Projekt &p2) {
    if (p1.k == p2.k) {
        if (p1.p == p2.p) {
            return p1.w < p2.w;
        }

        return p1.p < p2.p;
    }

    return p1.k < p2.k;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    Projekt projekty[n];
    int next[n + 1];
    long long max_val[n + 1];

    int p, k, w;
    for (int i = 0; i < n; i++) {
        std::cin >> p >> k >> w;
        projekty[i] = Projekt(p, k, w);
    }

    std::sort(projekty, projekty + n, comp);

    int l, r, s;
    for (int i = 1; i <= n; i++){
        l = 0; r = n - 1;
        while (l < r) {
            s = (l + r) / 2;
            if (projekty[s].k < projekty[i - 1].p) l = s + 1;
            else r = s;
        }
        if (l == 0 && projekty[0].k >= projekty[0].p) {
            next[i] = 0;
        } else {
            next[i] = l;
        }
    }

    max_val[0] = 0;
    next[0] = 0;
    for (int i = 1; i <= n; i++) {
        max_val[i] = std::max(projekty[i - 1].w + max_val[next[i]], max_val[i - 1]);
    }

    std::cout << max_val[n];

    return 0;
}
