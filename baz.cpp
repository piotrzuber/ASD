#include <iostream>
#include <vector>

#define MIN (-1)

int main() {

    long long n, m;
    long long pom;

    std::cin >> n; // [1; 10^6]

    std::vector<long long> parzyste;
    std::vector<long long> nieparzyste;

    for (long long i = 0; i < n; i++) {
        std::cin >> pom; // [1;10^9]
        if (pom % 2) {
            nieparzyste.push_back(pom);
        } else {
            parzyste.push_back(pom);
        }
    }

    std::vector<long long> kParzyste(parzyste);
    std::vector<long long> kNieparzyste(nieparzyste);

    std::cin >> m; // [1;10^6]

    long long produkty[m];

    for (long long i = 0; i < m; i++) {
        std::cin >> produkty[i]; // [1;n]
    }

    long long wyniki[n];

    if (nieparzyste.empty()) {
        wyniki[0] = MIN;
    } else {
        wyniki[0] = *nieparzyste.rbegin();
        nieparzyste.pop_back();
    }

    for (long long k = 2; k < n; k += 2) {
        if (wyniki[k-2] == MIN) {
            wyniki[k] = MIN;
        } else {
            if (parzyste.size() > 1 && nieparzyste.size() > 1) {
                long long sumParz = *parzyste.rbegin() + *(parzyste.rbegin() + 1);
                long long sumNParz = *nieparzyste.rbegin() + *(nieparzyste.rbegin() + 1);

                long long delta;

                if (sumParz >= sumNParz) {
                    delta = sumParz;
                    parzyste.pop_back();
                    parzyste.pop_back();
                } else {
                    delta = sumNParz;
                    nieparzyste.pop_back();
                    nieparzyste.pop_back();
                }

                wyniki[k] = wyniki[k - 2] + delta;
            } else if (parzyste.size() > 1) {
                long long sumParz = *parzyste.rbegin() + *(parzyste.rbegin() + 1);
                wyniki[k] = wyniki[k-2] + sumParz;
                parzyste.pop_back();
                parzyste.pop_back();
            } else if (nieparzyste.size() > 1) {
                long long sumNParz = *nieparzyste.rbegin() + *(nieparzyste.rbegin() + 1);
                wyniki[k] = wyniki[k-2] + sumNParz;
                nieparzyste.pop_back();
                nieparzyste.pop_back();
            } else {
                wyniki[k] = MIN;
            }
        }
    }

    if (kNieparzyste.empty() || kParzyste.empty()) {
        wyniki[1] = MIN;
    } else {
        wyniki[1] = *kNieparzyste.rbegin() + *kParzyste.rbegin();
        kParzyste.pop_back();
        kNieparzyste.pop_back();
    }

    for (long long k = 3; k < n; k += 2) {
        if (wyniki[k-2] == MIN) {
            wyniki[k] = MIN;
        } else {
            if (kParzyste.size() > 1 && kNieparzyste.size() > 1) {
                long long sumParz = *kParzyste.rbegin() + *(kParzyste.rbegin() + 1);
                long long sumNParz = *kNieparzyste.rbegin() + *(kNieparzyste.rbegin() + 1);

                long long delta;

                if (sumParz >= sumNParz) {
                    delta = sumParz;
                    kParzyste.pop_back();
                    kParzyste.pop_back();
                } else {
                    delta = sumNParz;
                    kNieparzyste.pop_back();
                    kNieparzyste.pop_back();
                }

                wyniki[k] = wyniki[k - 2] + delta;
            } else if (kParzyste.size() > 1) {
                long long sumParz = *kParzyste.rbegin() + *(kParzyste.rbegin() + 1);
                wyniki[k] = wyniki[k-2] + sumParz;
                kParzyste.pop_back();
                kParzyste.pop_back();
            } else if (kNieparzyste.size() > 1) {
                long long sumNParz = *kNieparzyste.rbegin() + *(kNieparzyste.rbegin() + 1);
                wyniki[k] = wyniki[k-2] + sumNParz;
                kNieparzyste.pop_back();
                kNieparzyste.pop_back();
            } else {
                wyniki[k] = MIN;
            }
        }
    }

    for (long long liczba : produkty) {
        std::cout << wyniki[liczba - 1] << std::endl;
    }

    return 0;
}

