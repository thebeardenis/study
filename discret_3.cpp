#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void fill_matrix(int** matrix, int n);
void fill_names_columns_and_rows_matrix(int** matrix, int n);
void view_matrix_of_incidence(int** matrix, int n, int count_edges, int** edges);
void view_adjacency_list(int** matrix, int n);
void view_incidence_list(int** matrix, int n, int count_edges, int** edges);
void view_matrix_of_adjacency(int** matrix, int n);

void select_type_matrix(int** matrix, int n) {
    cout << "Введи число от 1 до 5:" << endl << "1 - Показать матрицу инциденций." << endl << "2 - Показать список смежностей."<< endl << "3 - Показать список инциденций." << endl << "4 - Показать матрицу смежности." << endl << "5 - Завершить программу" << endl;
    string input_str;
    cin >> input_str;
    try {
        int input = stoi(input_str);
        system("clear");
        int count_edge = 0;
        for (int i=1; i<n; i++) {
            for (int j=i+1; j<n; j++) {
                if (*(*(matrix + i) + j) == 1) {
                    count_edge++;
                }
            }
        }
        int** edges = new int*[count_edge];
        for (int i=0; i<count_edge; i++) {
            edges[i] = new int[2];
        }
        for (int i=0; i<count_edge; i++) {
            for (int m=1; m<n; m++) {
                for (int v=m+1; v<n; v++) {
                    if (*(*(matrix + m) + v) == 1) {
                        *(*(edges + i)) = *(*(matrix) + v);
                        *(*(edges + i) + 1) = *(*(matrix + m));
                        i++;
                    }
                }
            }
        }
        if (input == 1) {
            view_matrix_of_incidence(matrix, n, count_edge, edges);
        } else if (input == 2) {
            view_adjacency_list(matrix, n);
        } else if (input == 3) {
            view_incidence_list(matrix, n, count_edge, edges);
        } else if (input == 4) {
            view_matrix_of_adjacency(matrix, n);
        } else if (input == 5) {
            exit(0);
        } else {
            throw invalid_argument("");
        }
    } catch (...) {
        system("clear");
        cout << "Неправильно введённые данные. Попробуйте снова." << endl;
        select_type_matrix(matrix, n);
    }
}

void view_matrix_of_incidence(int** matrix, int n, int count_edge, int** edges) {
    int** matrix_of_incidence = new int*[n];
    for (int i=0; i<n; i++) {
        matrix_of_incidence[i] = new int[count_edge+1];
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<=count_edge+1; j++) {
            if (i==0) {
                *(*(matrix_of_incidence + i) + j) = j;
            } else {
                if (j==0) {
                    *(*(matrix_of_incidence + i) + j) = i;
                }
            }
        }
    }
    int p=0;
    for (int j=1; j<=count_edge; j++) {
        for (int i=1; i<n; i++) {
            if (*(*(matrix_of_incidence + i)) == *(*(edges + p)) || *(*(matrix_of_incidence + i)) == *(*(edges + p) + 1)) {
                *(*(matrix_of_incidence + i) + j) = 1;
            } else {
                *(*(matrix_of_incidence + i) + j) = 0;
            }
        }
        p++;
    }
    system("clear");
    for (int i=0; i<n; i++) {
        for (int j=0; j<count_edge+1; j++) {
            cout << *(*(matrix_of_incidence + i) + j) << " ";
        }
        cout << endl;
    }
    select_type_matrix(matrix, n);

}
void view_adjacency_list(int** matrix, int n) {
    system("clear");
    for (int i=1; i<n; i++) {
        cout << i << ": ";
        for (int j=1; j<n; j++) {
            if (*(*(matrix + i) + j) == 1) {
                if (j+1==n) {
                    cout << j;
                } else {
                    cout << j << ", ";
                }
            }
        }
        cout << endl;
    }
    select_type_matrix(matrix, n);
}
void view_incidence_list(int** matrix, int n, int count_edges, int** edges) {
    system("clear");
    for (int i=0; i<count_edges; i++) {
        cout << "[" << *(*(edges + i)) << ", " << *(*(edges + i) + 1) << "]" << endl;
    }
    select_type_matrix(matrix, n);
}
void view_matrix_of_adjacency(int** matrix, int n) {
    system("clear");
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            cout << *(*(matrix + i) + j) << " ";
        }
        cout << endl;
    }
    select_type_matrix(matrix, n);
}

void enter_graph() {
    cout << "Введи число вершин графа:" << endl;
    string input_str;
    cin >> input_str;
    try {
        int input = stoi(input_str) + 1;
        system("clear");
        int** matrix = new int*[input];
        for (int i=0; i<input; i++) {
            matrix[i] = new int[input];
        }
        fill_names_columns_and_rows_matrix(matrix, input);
        fill_matrix(matrix, input);

        select_type_matrix(matrix, input);
    } catch (...) {
        system("clear");
        cout << "Неправильно введённые данные. Попробуйте снова.";
        enter_graph();
    }
}

void fill_names_columns_and_rows_matrix(int** matrix, int n) {
    for (int i=0; i<n; i++) {
        *(*(matrix + i)) = i;
        *(*(matrix) + i) = i;
    }
}

void fill_matrix(int** matrix, int n) {
    for (int i=1; i<n; i++) {
        for (int j=i+1; j<n; j++) {
            cout << "Введи 0 или 1 в зависимости от наличия связи между " << i << " и " << j << ":" << endl;
            string input_str;
            cin >> input_str;
            try {
                int input = stoi(input_str);
                system("clear");
                *(*(matrix + i) + j) = input;
                *(*(matrix + j) + i) = input;
            } catch (...) {
                system("clear");
                cout << "Неправильно введённые данные. Попробуйте снова.";
                enter_graph();
            }
        }
    }
}

int main() {

    enter_graph();

    return 0;
}