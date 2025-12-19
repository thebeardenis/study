#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    srand(time(nullptr));

    int mass[20];

    for (int i=0; i<20; i++) {
        mass[i] = -100000 + (rand() % (200001));
    }

    sort(&mass[0], &mass[20]);

    ofstream data("data_for_lab.txt");
    for (int i=0; i<20; i++) {
        data << to_string(mass[i]) << endl;
    }
    data.close();

    int my_num;
    cin >> my_num;

    ifstream in_f("data_for_lab.txt");
    string file_content;

    bool isEnter = false;
    bool isFirst = true;
    string line_f;
    int last_n;
    while (std::getline(in_f, line_f)) {
        int n = stoi(line_f);
        if (!isEnter) {
            if (isFirst) {
                if (my_num < n) {
                    file_content += to_string(my_num) + "\n";
                    isEnter =true;
                }
                isFirst = false;
            }
            if (my_num > last_n && my_num <= n) {
                file_content += to_string(my_num) + "\n";
                isEnter = true;
            }
        }
        file_content += line_f + "\n";
        last_n = n;
    }
    if (!isEnter) file_content += to_string(my_num) + "\n";
    in_f.close();

    ofstream out_f("data_for_lab.txt");
    out_f << file_content;
    out_f.close();

    return 0;
}