#include <iostream>
#include <set>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::set<int> numbers;

    int n, d;
    std::cin >> n >> d;

    if (n == 1) {
        std::cout << "NIE";
        return 0;
    }

    int number;
    for (int i = 0; i < n; i++) {
        std::cin >> number;
        numbers.insert(number);
    }

    auto it_res = numbers.end();

    for (auto it = numbers.begin(); it != numbers.end(); it++) {
        auto asd = numbers.find(*it + d);
        if (asd != numbers.end() && asd != it) {
            it_res = it;
            break;
        }
    }

    if (it_res == numbers.end()) {
        std::cout << "NIE";
    } else {
        std::cout << *it_res + d << " " << *it_res;
    }

    return 0;
}