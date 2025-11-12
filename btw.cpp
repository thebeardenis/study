#include <iostream>
#include <cmath>
using namespace std;

int main()
{

    string A, B;

    cout << "Введите строку A" << endl;
    getline(cin, A);

    cout << "Введите строку B" << endl;
    getline(cin, B);

    string tmp_A;
    for (const char i : A) {
        int counter = 0;
        for (const char j : B) {
            if (i != j) {
                counter++;
            }
        }
        if (counter == B.length()) {
            tmp_A += i;
        }
    }
    A = tmp_A;
    cout << A << endl;

    return 0;
}