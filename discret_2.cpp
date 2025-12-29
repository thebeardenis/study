#include <iostream>

using namespace std;

struct figure {
    bool isCircle;
    double x0, y0, width, height, radius;
};
struct point {
    double x, y;
};

void select_figure_type(figure& result);
void enter_figur_data(figure& result, int& counter);
void enter_point_data(point& dot, int& count);
bool does_point_belong_to_figure(const point& dot, const figure& space);
void enter_a_figure(char name, figure& result);
void report_about_dot(const point& dot, const figure& A, const figure& B, const figure& C, const figure& D);
void main_select(point& dot, figure& A, figure& B, figure& C, figure& D);

int main() {
    system("clear");

    figure A{},B{},C{},D{};

    enter_a_figure(*"A", A);
    enter_a_figure(*"B", B);
    enter_a_figure(*"C", C);
    enter_a_figure(*"D", D);

    point dot{};

    while (true) {
        main_select(dot, A, B, C, D);

        report_about_dot(dot, A, B, C, D);
    }
    return 0;
}

void enter_a_figure(const char name, figure& result) {
    cout << "Введи 1 или 2:" << endl << "1 - Ввести фигиру " << name << "." << endl << "2 - Завершить программу" << endl;
    string input_str;
    cin >> input_str;
    try {
        int input = stoi(input_str);
        if (input == 1) {
            select_figure_type(result);
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
void main_select(point& dot, figure& A, figure& B, figure& C, figure& D) {
    cout << "Введи число от 1 до 6:" << endl << "1 - Ввести точку для проверки." << endl << "2 - Изменить фигуру A" << endl << "3 - Изменить фигуру B" << endl << "4 - Изменить фигуру C" << endl << "5 - Изменить фигуру D"<< endl << "6 - Завершить программу" << endl;
    string input_str;
    cin >> input_str;
    try {
        const int input = stoi(input_str);
        if (input == 1) {
            int counter = 0;
            enter_point_data(dot, counter);
        } else if (input == 6) {
            exit(0);
        } else if (2 <= input && input <= 5) {
            if (input == 2) {
                enter_a_figure(*"A", A);
            } else if (input == 3) {
                enter_a_figure(*"B", B);
            } else if (input == 4) {
                enter_a_figure(*"C", C);
            } else {
                enter_a_figure(*"D", D);
            }
            main_select(dot,A,B,C,D);
        } else {
            throw invalid_argument("");
        }
    } catch (...) {
        system("clear");
        cout << "Неправильно введённые данные. Попробуйте снова.";
        main_select(dot,A,B,C,D);
    }
}
void select_figure_type(figure& result) {
    cout << "Введите число от 1 до 2:" << endl << "1 - Ввести круг." << endl <<  "2 - Ввести прямоугольник" << endl;
    string input_str;
    cin >> input_str;
    try {
        const int input = stoi(input_str);
        int counter =0;
        if (input == 1) {
            result.isCircle = true;
        } else if (input == 2) {
            result.isCircle = false;
        } else {
            throw invalid_argument("");
        }
        enter_figur_data(result, counter);
    } catch (...) {
        system("clear");
        cout << "Неправильно введённые данные. Попробуйте снова.";
        select_figure_type(result);
    }
}
void enter_point_data(point& dot, int& count) {
    try {
        if (count < 1) {
            string x_str;
            cout << "Введите x:" << endl;
            cin >> x_str;
            const double x = stod(x_str);
            dot.x = x;
            count++;
        }

        if (count < 2) {
            string y_str;
            cout << "Введите y:" << endl;
            cin >> y_str;
            const double y = stod(y_str);
            dot.y = y;
            count++;
        }

    } catch (...) {
        system("clear");
        cout << "Неправильно введённые данные. Попробуйте снова." << endl;
        enter_point_data(dot, count);
    }
}
void enter_figur_data(figure& result, int& counter) {
    try {
        if (counter < 1) {
            string x0_str;
            cout << "Введите x0:" << endl;
            cin >> x0_str;
            const double x0 = stod(x0_str);
            result.x0 = x0;
            counter++;
        }

        if (counter < 2) {
            string y0_str;
            cout << "Введите y0:" << endl;
            cin >> y0_str;
            const double y0 = stod(y0_str);
            result.y0 = y0;
            counter++;
        }
        if (result.isCircle) {
            if (counter < 3) {
                string radius_str;
                cout << "Ведите radius:" << endl;
                cin >> radius_str;
                const double radius = stod(radius_str);
                result.radius = radius;
                counter++;
            }
        } else {
            if (counter < 3) {
                string width_str;
                cout << "Введите width:" << endl;
                cin >> width_str;
                const double width = stod(width_str);
                result.width = width;
                counter++;
            }

            if (counter < 4) {
                string height_str;
                cout << "Введите height:" << endl;
                cin >> height_str;
                const double height = stod(height_str);
                result.height = height;
                counter++;
            }
        }
    } catch (...) {
        system("clear");
        cout << "Неправильно введённые данные. Попробуйте снова." << endl;
        enter_figur_data(result, counter);
    }
}
void report_about_dot(const point& dot, const figure& A, const figure& B, const figure& C,const figure& D) {
    const bool belong_A = does_point_belong_to_figure(dot, A);
    const bool belong_B = does_point_belong_to_figure(dot, B);
    const bool belong_C = does_point_belong_to_figure(dot, C);
    const bool belong_D = does_point_belong_to_figure(dot, D);

    cout << "Точка {" << dot.x << ";" << dot.y << "} "
    << ((!belong_A && (belong_B || belong_C)) || belong_D ? "ПРИНАДЛЕЖИТ" : "НЕ ПРИНАДЛЕЖИТ")
    << " плоскому множеству точек :" << "(!A & (B | C)) | D" << endl << endl;

}
bool does_point_belong_to_figure(const point& dot, const figure& space) {
    if (space.isCircle) {
        const double r = sqrt((dot.x - space.x0)*(dot.x - space.x0) + (dot.y - space.y0)*(dot.y - space.y0));
        return  space.radius >= r;
    }
    const bool inX = (dot.x >= space.x0 - space.width / 2) && (dot.x <= space.x0 + space.width / 2);
    const bool inY = (dot.y >= space.y0 - space.height / 2) && (dot.y <= space.y0 + space.height / 2);
    return inX && inY;

}