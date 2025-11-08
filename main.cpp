#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <thread>
#include <chrono>

using namespace std;

int main() {
    winsize size{};
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);

    const int CONSOLE_WIDTH = size.ws_col;
    const int CONSOLE_HEIGHT = size.ws_row;

    system("clear");

    char monitor[CONSOLE_HEIGHT][CONSOLE_WIDTH];

    int position_line[80];
    for (int d=0 ;d < 80;) {
        for (int i=0; i > -20; i--) {
            position_line[d] = i;
            d++;
        }
        for (int i=-20; i<1; i++) {
            position_line[d] = i;
            d++;
        }
        for (int i=1; i<20; i++) {
            position_line[d] = i;
            d++;
        }
        for (int i=20; i>0; i--) {
            position_line[d] = i;
            d++;
        }
    }

    while (true) {
        for (int h=0;  h<80; ) {
            for (int index=0; index<20; index++) {
                for (int i=0; i<CONSOLE_HEIGHT; i++) {
                    for (int j=0; j<CONSOLE_WIDTH; j++) {
                        const int radius[20] = {5,6,7,8,9,10,11,12,13,14,15,14,13,12,11,10,9,8,7,6};
                        if ((j - CONSOLE_WIDTH/2)*(j - CONSOLE_WIDTH/2+position_line[h]) + (i - CONSOLE_HEIGHT/2)*(i - CONSOLE_HEIGHT/2)*4
                            <= radius[index] * radius[index]) {
                            monitor[i][j] = *"#";
                            } else {
                                monitor[i][j] = *" ";
                            }
                    }
                }
                h++;

                cout << endl;
                for (int i=0; i<CONSOLE_HEIGHT; i++) {
                    for (int j=0; j<CONSOLE_WIDTH; j++) {
                        cout << monitor[i][j];
                    }

                }
                this_thread::sleep_for(chrono::milliseconds(20));
            }
        }
    }


    return 0;
}