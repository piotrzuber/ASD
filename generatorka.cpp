//
// Created by kiwipodptak on 12.12.18.
//
#include <iostream>
#include <cstdlib>
#include <string>

#define N 5
#define M 15
#define Q 10

using namespace std;

int main () {
    cout << N << endl;
    srand(static_cast<unsigned int>(time(nullptr)));
    for (int i = 0; i < N; i++) {
        int a = rand() % M + 1;
        int b = rand() % M + 1;
        cout << a << " " << b << endl;
    }

    /*
    cout << Q << endl;
    string s[4] = {"in", "none", "some", "over"};
    for (int i = 0; i < Q; i++) {
        string msg = s[rand()%4];
        int a = rand() % M + 1;
        int b = a + (rand() % M + 1);
        cout << msg << " " << a << " " << b << endl;
    } */
}