#include <iostream>
using namespace std;

class Person {
public:
    string FIO;
    string address;
    string phone_number;
    void print_data_on_first_digits(const string &digits) const {
        bool havePlus = false;
        if (this->phone_number[0] == *"+") {
            havePlus = true;
        }
        bool isGood = true;
        for (int i=0; i<digits.length(); i++) {
            if (havePlus) {
                if (this->phone_number[i+1] != digits[i]) {
                    isGood = false;
                }
            } else {
                if (this->phone_number[i] != digits[i]) {
                    isGood = false;
                }
            }
        }
        if (isGood) {
            cout << "Person data:" << endl;
            cout << "name: " << FIO << endl;
            cout << "address: " << address << endl;
            cout << "phone number: " << phone_number << endl << endl;
        }
    }
};

int main() {

    Person people[5];
    for (int i=0; i<5; i++) {
        Person tmp;
        cout << "Enter name: ";
        getline(cin, tmp.FIO);
        cout << "Enter address: ";
        getline(cin, tmp.address);
        cout << "Enter phone: ";
        getline(cin, tmp.phone_number);
        people[i] = tmp;
        cout << endl;
    }

    while (true) {
        string digits;
        cout << "Enter first three digits phone number: ";
        cin >> digits;
        for (int i=0; i<5; i++) {
            people[i].print_data_on_first_digits(digits);
        }
    }

    return 0;
}
