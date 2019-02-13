#include <iostream>
#include <cstdlib>

int comparator(const void* a, const void* b) {

    if (*(unsigned long long*)a < *(unsigned long long*)b) return -1;
    if (*(unsigned long long*)a == *(unsigned long long*)b) return 0;
    if (*(unsigned long long*)a > *(unsigned long long*)b) return 1;
}

int main() {

    int n, m;
    std::cin >> n;
    std::cin >> m;

    std::string wynik = "TAK";

    unsigned long long kodowanie[n];
    for (int i = 0; i < n; i++) {
        kodowanie[i] = 0;
    }

    int aux;

    unsigned long long dwa = 1;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> aux;

            if (j >= n/2) {
                kodowanie[aux - 1] += dwa;
            }
        }

        dwa *= 2;
    }

    qsort(kodowanie, n, sizeof(unsigned long long), comparator);

    for (int i = 0; i + 1 < n; i++) {
        if (kodowanie[i] == kodowanie[i + 1]) {
            wynik = "NIE";
            break;
        }
    }

    std::cout << wynik;

    return 0;
}