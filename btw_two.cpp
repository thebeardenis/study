#include <iostream>
#include <cmath>
using namespace std;

int bin(int x) {
    int binary_x = 0;
    int i = 1;
    while (x != 0) {
        binary_x += (x%2) * i;
        x = x / 2;
        i *= 10;
    }

    return binary_x;
}

int main() {

    int a,b,c;
    cout << "Введите a:" << endl;
    cin >> a;
    cout << "Введите b:" << endl;
    cin >> b;
    cout << "Введите c:" << endl;
    cin >> c;

    cout << a << " " <<  bin(a) << endl;
    cout << b << " " << bin(b) << endl;
    cout << c << " " << bin(c) << endl;

    return 0;
}
