#include <iostream>
#include <vector>

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    int nodes[n];
    std::vector<int> components;
    int max = 0, min = n + 1;

    for (int i = 0; i < n; i++) {
        std::cin >> nodes[i];

        if (nodes[i] < min) {
            min = nodes[i];
        }

        if (nodes[i] > max) {
            max = nodes[i];
        }

        if (min == 1 && max == i + 1) {
            components.push_back(i + 1);
        }
    }

    int i = 1, last = 0;
    std::cout << components.size() << std::endl;
    for (auto it = components.begin(); it != components.end(); it++) {
        if (it == components.begin()) {
            last = *it;
            std::cout << *it;

            for (; i <= *it; i++) {
                std::cout << " " << i;
            }
            std::cout << std::endl;
        } else {
            std::cout << *it - last;

            for (; i <= *it; i++) {
                std::cout << " " << i;
            }
            std::cout << std::endl;
            last = *it;
        }
    }

    return 0;
}