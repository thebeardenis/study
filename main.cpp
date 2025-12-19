#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <thread>
#include <chrono>

using namespace std;

struct myVector {
    float x,y;
};

int main() {
    winsize size{};
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);

    const int CONSOLE_WIDTH = size.ws_col;
    const int CONSOLE_HEIGHT = size.ws_row;

    system("clear");

    char monitor[CONSOLE_HEIGHT][CONSOLE_WIDTH];

    while (true) {
        for (int i=0; i<CONSOLE_HEIGHT; i++) {
            for (int j=0; j<CONSOLE_WIDTH; j++) {
                if ((j - CONSOLE_WIDTH/2)*(j - CONSOLE_WIDTH/2) + (i - CONSOLE_HEIGHT/2)*(i - CONSOLE_HEIGHT/2)*4 <= 14 * 14) {
                    monitor[i][j] = *"#";
                } else {
                    monitor[i][j] = *" ";
                }
            }
        }
        cout << endl;
        for (int i=0; i<CONSOLE_HEIGHT; i++) {
            for (int j=0; j<CONSOLE_WIDTH; j++) {
                cout << monitor[i][j];
            }

        }
        this_thread::sleep_for(chrono::milliseconds(20));
    }
    return 0;
}