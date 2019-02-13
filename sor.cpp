#include <iostream>

#define MODULO (1000000000)

int main() {
    int n;
    std::cin >> n;

    int ciag[n];
    for (int i = 0; i < n; i++) {
        std::cin >> ciag[i];
    }

    int ostatniP[n][n];
    int ostatniK[n][n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ostatniP[i][j] = 0;
            ostatniK[i][j] = 0;
        }
    }

    for (int len = 1; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            if (len == 1) {
                ostatniP[len-1][i] = 1;
                ostatniK[len-1][i] = 0;
            } else {
                if (ciag[i+1] > ciag[i]) {
                    ostatniP[len-1][i] = (ostatniP[len-1][i] + ostatniP[len-2][i+1]) % MODULO;
                }
                if (ciag[i] < ciag[i+len-1]) {
                    ostatniP[len-1][i] = (ostatniP[len-1][i] + ostatniK[len-2][i+1]) % MODULO;
                }
                if (ciag[i+len-1] > ciag[i]) {
                    ostatniK[len-1][i] = (ostatniK[len-1][i] + ostatniP[len-2][i]) % MODULO;
                }
                if (ciag[i+len-1] > ciag[i+len-2]) {
                    ostatniK[len-1][i] = (ostatniK[len-1][i] + ostatniK[len-2][i]) % MODULO;
                }
            }
        }
    }

    std::cout << (ostatniK[n-1][0] + ostatniP[n-1][0]) % MODULO;
}