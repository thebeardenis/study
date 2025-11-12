#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>

using namespace std;

struct figure {
    bool isCircle;
    double x0, y0, width, height, radius;
};
struct point {
    double x, y;
};

void select_enter_circle_or_rectangle(figure& result);
void enter_data_for_circle(figure& result, int& counter);
void enter_data_for_rectangle(figure& result, int& counter);
void enter_data_for_point(point& dot, int& count);
bool does_point_belong_to_figure(const point& dot, const figure& space);

void enter_a_figure(const char name, figure& result) {
    cout << "Введи 1 или 2:" << endl << "1 - Ввести фигиру " << name << "." << endl << "2 - Завершить программу" << endl;
    string input_str;
    cin >> input_str;
    try {
        int input = stoi(input_str);
        system("clear");
        if (input == 1) {
            select_enter_circle_or_rectangle(result);
        } else if (input == 2) {
            exit(0);
        } else {
            throw invalid_argument("");
        }
    } catch (...) {
        system("clear");
        cout << "Неправильно введённые данные. Попробуйте снова.";
        enter_a_figure(name, result);
    }
}

void select_enter_a_point_or_exit(point& dot) {
    cout << "Введи число от 1 до 2:" << endl << "1 - Ввести точку для проверки." << endl << "2 - Завершить программу" << endl;
    string input_str;
    cin >> input_str;
    try {
        int input = stoi(input_str);
        system("clear");
        if (input == 1) {
            int counter = 0;
            enter_data_for_point(dot, counter);
        } else if (input == 2) {
            exit(0);
        } else {
            throw invalid_argument("");
        }
    } catch (...) {
        system("clear");
        cout << "Неправильно введённые данные. Попробуйте снова.";
        select_enter_a_point_or_exit(dot);
    }
}

void enter_data_for_point(point& dot, int& count) {
    try {
        if (count < 1) {
            string x_str;
            cout << "Введите x:" << endl;
            cin >> x_str;
            system("clear");
            const int x = stoi(x_str);
            dot.x = x;
            count++;
        }

        if (count < 2) {
            string y_str;
            cout << "Введите y:" << endl;
            cin >> y_str;
            system("clear");
            const int y = stoi(y_str);
            dot.y = y;
            count++;
        }

    } catch (...) {
        system("clear");
        cout << "Неправильно введённые данные. Попробуйте снова." << endl;
        enter_data_for_point(dot, count);
    }
}

void select_enter_circle_or_rectangle(figure& result) {
    cout << "Введите число от 1 до 2:" << endl << "1 - Ввести круг." << endl <<  "2 - Ввести прямоугольник" << endl;
    string input_str;
    cin >> input_str;
    try {
        const int input = stoi(input_str);
        system("clear");
        int counter =0;
        if (input == 1) {
            result.isCircle = true;
            enter_data_for_circle(result, counter);
        } else if (input == 2) {
            result.isCircle = false;
            enter_data_for_rectangle(result, counter);
        } else {
            throw invalid_argument("");
        }
    } catch (...) {
        system("clear");
        cout << "Неправильно введённые данные. Попробуйте снова.";
        select_enter_circle_or_rectangle(result);
    }
}

void enter_data_for_circle(figure& result, int& counter) {
    try {
        if (counter < 1) {
            string x0_str;
            cout << "Введите x0:" << endl;
            cin >> x0_str;
            system("clear");
            const int x0 = stoi(x0_str);
            result.x0 = x0;
            counter++;
        }

        if (counter < 2) {
            string y0_str;
            cout << "Введите y0:" << endl;
            cin >> y0_str;
            system("clear");
            const int y0 = stoi(y0_str);
            result.y0 = y0;
            counter++;
        }

        if (counter < 3) {
            string radius_str;
            cout << "Ведите radius:" << endl;
            cin >> radius_str;
            system("clear");
            const int radius = stoi(radius_str);
            result.radius = radius;
            counter++;
        }
    } catch (...) {
        system("clear");
        cout << "Неправильно введённые данные. Попробуйте снова." << endl;
        enter_data_for_circle(result, counter);
    }
}

void enter_data_for_rectangle(figure& result, int& counter) {
    try {
        if (counter < 1) {
            string x0_str;
            cout << "Введите x0:" << endl;
            cin >> x0_str;
            system("clear");
            const int x0 = stoi(x0_str);
            result.x0 = x0;
            counter++;
        }

        if (counter < 2) {
            string y0_str;
            cout << "Введите y0:" << endl;
            cin >> y0_str;
            system("clear");
            const int y0 = stoi(y0_str);
            result.y0 = y0;
            counter++;
        }

        if (counter < 3) {
            string width_str;
            cout << "Введите width:" << endl;
            cin >> width_str;
            system("clear");
            const int width = stoi(width_str);
            result.width = width;
            counter++;
        }

        if (counter < 4) {
            string height_str;
            cout << "Введите height:" << endl;
            cin >> height_str;
            system("clear");
            const int height = stoi(height_str);
            result.height = height;
            counter++;
        }
    } catch (...) {
        system("clear");
        cout << "Неправильно введённые данные. Попробуйте снова." << endl;
        enter_data_for_rectangle(result, counter);
    }
}

void report_about_dot(const point& dot, const figure& A, const figure& B, const figure& C,const figure& D) {
    winsize size{};
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);

    const bool belong_A = does_point_belong_to_figure(dot, A);
    const bool belong_B = does_point_belong_to_figure(dot, B);
    const bool belong_C = does_point_belong_to_figure(dot, C);
    const bool belong_D = does_point_belong_to_figure(dot, D);

    cout << "Точка {" << dot.x << ";" << dot.y << "} "
    << (((!belong_A && (belong_B || belong_C)) || belong_D) ? "ПРИНАДЛЕЖИТ" : "НЕ ПРИНАДЛЕЖИТ")
    << " плоскости точек :" << "(!A & (B | C)) | D" << endl;
    for (int i=0; i<size.ws_col; i++) {
        cout << "-";
    }
}

bool does_point_belong_to_figure(const point& dot, const figure& space) {
    if (space.isCircle) {
        double r = (dot.x - space.x0)*(dot.x - space.x0) + (dot.y - space.y0)*(dot.y - space.y0);
        return  space.radius * space.radius >= r;
    } else {
        bool inX = (dot.x >= space.x0 - space.width / 2) && (dot.x <= space.x0 + space.width / 2);
        bool inY = (dot.y >= space.y0 - space.height / 2) && (dot.y <= space.y0 + space.height / 2);
        return inX && inY;
    }
}

int main() {
    system("clear");

    figure A{},B{},C{},D{};

    enter_a_figure(*"A", A);
    enter_a_figure(*"B", B);
    enter_a_figure(*"C", C);
    enter_a_figure(*"D", D);

    point dot{};

    while (true) {
        select_enter_a_point_or_exit(dot);

        report_about_dot(dot, A, B, C, D);
    }
    return 0;
}
