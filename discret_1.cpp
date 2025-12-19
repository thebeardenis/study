#include <iostream>
#include <string>

using namespace std;

string sko_expression(int a, int b, int c, int d, int e);
string sdo_expression(int a, int b, int c, int d, int e);

int main()
{
    string SDNF, SKNF;
    bool is_first_sko{true}, is_first_sdo{true};

    cout << "a b c d e  f" << endl;
    for (int a=0; a<2; a++) {
        for (int b=0; b<2; b++) {
            for (int c=0; c<2; c++) {
                for (int d=0; d<2; d++) {
                    for (int e=0; e<2; e++) {
                        const bool result_expression = (!a && b) || c || (d && !e);
                        if (result_expression) {
                            if (is_first_sko) {
                                SDNF = sko_expression(a,b,c,d,e);
                                is_first_sko = false;
                            } else {
                                SDNF += " | " + sko_expression(a,b,c,d,e);
                            }
                        } else {
                            if (is_first_sdo) {
                                SKNF = sdo_expression(a,b,c,d,e);
                                is_first_sdo = false;
                            } else {
                                SKNF += " & " + sdo_expression(a,b,c,d,e);
                            }
                        }
                        cout << a << " " << b << " " << c << " " << d << " " << e << "  "
                        << result_expression << endl;
                    }
                }
            }
        }
    }

    cout << "SDNF = " << SDNF << endl;
    cout << "SKNF = " << SKNF << endl;

    return 0;
}

string sko_expression(const int a, const int b, const int c, const int d, const int e) {
    string result;
    result += (a ? "(a & " : "(!a & ");
    result += (b ? "b & " : "!b & ");
    result += (c ? "c & " : "!c & ");
    result += (d ? "d & " : "!d & ");
    result += (e ? "e)" : "!e)");
    return result;
}
string sdo_expression(const int a, const int b, const int c, const int d, const int e) {
    string result;
    result += (a ? "(!a | " : "(a | ");
    result += (b ? "!b | " : "b | ");
    result += (c ? "!c | " : "c | ");
    result += (d ? "!d | " : "d | ");
    result += (e ? "!e)" : "e)");
    return result;
}