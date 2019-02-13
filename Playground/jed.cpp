#include <iostream>
#include <set>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    int seq[n];
    for (int i = 0; i < n; i++) {
        std::cin >> seq[i];
    }

    std::set<int> ones;
    ones.insert(seq[0]);
    std::cout << 1 << std::endl;

    for (int i = 1; i < n; i++) {
        auto it = ones.find(seq[i]);

        if (it == ones.end()) {
            ones.insert(seq[i]);
        } else {
            int pos = *it;
            ones.erase(it++);
            while (it != ones.end()) {
                if (*it == pos + 1) {
                    pos++;
                    ones.erase(it++);
                } else {
                    break;
                }
            }

            ones.insert(pos + 1);
        }
        std::cout << ones.size() << std::endl;
    }



    return 0;
}