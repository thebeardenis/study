#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void enter_graph_on_terminal();
void view_matrix_of_incidence(int** matrix, int n, int count_edges, int** edges);
void view_adjacency_list(int** matrix, int n);
void view_incidence_list(int** matrix, int n, int count_edges, int** edges);
void view_matrix_of_adjacency(int** matrix, int n);
void select_type_matrix(int** matrix, int n);


void view_matrix_of_incidence(int** matrix, const int n, const int count_edges, int** edges) {
    int** matrix_of_incidence = new int*[n];
    for (int i=0; i<n; i++) {
        matrix_of_incidence[i] = new int[count_edges+1];
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<=count_edges+1; j++) {
            if (i==0) {
                *(*(matrix_of_incidence + i) + j) = j;
            } else if (j==0){
                *(*(matrix_of_incidence + i) + j) = i;
            }
        }
    }
    int p=0;
    for (int j=1; j<=count_edges; j++) {
        for (int i=1; i<n; i++) {
            *(*(matrix_of_incidence + i) + j) =
                **(matrix_of_incidence + i) == **(edges + p) || **(matrix_of_incidence + i) == *(*(edges + p) + 1)? 1 : 0;
        }
        p++;
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<count_edges+1; j++) {
            cout << *(*(matrix_of_incidence + i) + j) << " ";
        }
        cout << endl;
    }
    cout << endl;
    select_type_matrix(matrix, n);
}
void view_incidence_list(int** matrix, const int n, const int count_edges, int** edges) {
    system("clear");
    for (int i=0; i<count_edges; i++) {
        cout << "[" << *(*(edges + i)) << ", " << *(*(edges + i) + 1) << "]" << endl;
    }
    cout << endl;
    select_type_matrix(matrix, n);
}
void view_adjacency_list(int** matrix, const int n) {
    system("clear");
    for (int i=1; i<n; i++) {
        bool isFirst = true;
        cout << i << ": ";
        for (int j=1; j<n; j++) {
            if (*(*(matrix + i) + j) == 1) {
                if (!isFirst) {
                    cout << ", ";
                }
                isFirst = false;
                cout << j;
            }
        }
        cout << endl;
    }
    cout << endl;
    select_type_matrix(matrix, n);
}
void view_matrix_of_adjacency(int** matrix, const int n) {
    system("clear");
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            cout << *(*(matrix + i) + j) << " ";
        }
        cout << endl;
    }
    cout << endl;
    select_type_matrix(matrix, n);
}

void fill_matrix(int** matrix, const int n, int& filled_node_counter) {
    int tmp_counter_nodes = 0;
    for (int i=1; i<n; i++) {
        for (int j=i+1; j<n; j++) {
            if (tmp_counter_nodes == filled_node_counter) {
                cout << "Введи 0 или 1 в зависимости от наличия связи между " << i << " строкой и " << j << " столбцом:" << endl;
                string input_str;
                cin >> input_str;
                try {
                    int input = stoi(input_str);
                    if (input != 0 && input != 1) {
                        throw invalid_argument("Матрица может содержать только 0 или 1.");
                    }
                    *(*(matrix + i) + j) = input;
                    *(*(matrix + j) + i) = input;
                    filled_node_counter++;
                    system("clear");
                } catch (...) {
                    system("clear");
                    cout << "Неправильно введённые данные. Попробуйте снова." << endl;
                    fill_matrix(matrix, n, filled_node_counter);
                }
            }
            tmp_counter_nodes++;
        }
    }
}
void select_type_matrix(int** matrix, const int n) {
    cout << "Введи число от 1 до 5:" << endl << "1 - Показать матрицу инциденций." << endl << "2 - Показать матрицу смежности."<< endl << "3 - Показать список инциденций." << endl << "4 - Показать список смежностей." << endl << "5 - Завершить программу" << endl;
    string input_str;
    cin >> input_str;
    try {
        int input = stoi(input_str);
        system("clear");
        if (input < 6 && input > 0) {
            if (input == 4) {
                view_adjacency_list(matrix, n);
            } else if (input == 2) {
                view_matrix_of_adjacency(matrix, n);
            } else if (input == 5) {
                exit(0);
            } else {
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
                if (input == 3) {
                    view_incidence_list(matrix, n, count_edge, edges);
                } else {
                    view_matrix_of_incidence(matrix, n, count_edge, edges);
                }
            }
        }  else {
            throw invalid_argument("Выбор от 1 до 5.");
        }
    } catch (...) {
        system("clear");
        cout << "Неправильно введённые данные. Попробуйте снова." << endl;
        select_type_matrix(matrix, n);
    }
}
void enter_graph_on_terminal() {
    string input_str;
    cout << "Введи число вершин графа:" << endl;
    cin >> input_str;
    try {
        int count_peaks = stoi(input_str) + 1;
        if (count_peaks < 3) {
            throw invalid_argument("Число графов не может быть меньше 2.");
        }

        int** matrix = new int*[count_peaks];
        for (int i=0; i<count_peaks; i++) {
            matrix[i] = new int[count_peaks];
        }
        for (int i=0; i<count_peaks; i++) {
            *(*(matrix + i)) = i;
            *(*(matrix) + i) = i;
        }

        int filled_node_counter = 0;
        system("clear");
        fill_matrix(matrix, count_peaks, filled_node_counter);

        system("clear");
        select_type_matrix(matrix, count_peaks);
    } catch (...) {
        system("clear");
        cout << "Неправильно введённые данные. Попробуйте снова." << endl;
        enter_graph_on_terminal();
    }
}
void enter_graph_on_file() {
    string input_str;
    cout << "Введи название файла, находящегося в этой же директории:" << endl;
    cin >> input_str;
    try {
        int n_matrix = 0;
        int** matrix = nullptr;
        ifstream file_matrix(input_str);
        if (file_matrix.is_open()) {
            string tmp_line;
            getline(file_matrix, tmp_line);
            n_matrix = tmp_line.length()/2 + 2;
            if (n_matrix < 3) {
                throw invalid_argument("Число графов не может быть меньше 2.");
            }
            matrix = new int*[n_matrix];
            for (int i=0; i<n_matrix; i++) {
                matrix[i] = new int[n_matrix];
            }
            int p=1;
            do {
                for (int i=0; i<n_matrix; i++) {
                    *(*(matrix + i)) = i;
                    *(*(matrix) + i) = i;
                }
                int index = p*2;
                for (int j=p+1; j<n_matrix; j++) {
                    cout << tmp_line << " " << index << "-" << tmp_line[index] << endl;
                    int num = stoi(&tmp_line[index]);
                    if (num != 0 && num != 1) {
                        throw invalid_argument("Значение в матрице не может быть не 1 или 0.");
                    }
                    *(*(matrix + p) + j) = num;
                    *(*(matrix + j) + p) = num;
                    index+=2;
                }
                p++;
            } while (getline(file_matrix, tmp_line));
        } else {
            system("clear");
            cout << "Файл не запускается." << endl;
            enter_graph_on_file();
        }
        file_matrix.close();
        if (matrix == nullptr) {
            throw invalid_argument("Неполучилось считать матрицу из файла.");
        }
        system("clear");
        select_type_matrix(matrix, n_matrix);
    } catch (...) {
        system("clear");
        cout << "Неправильно введённые данные. Попробуйте снова." << endl;
        enter_graph_on_terminal();
    }
}
void select_terminal_or_file() {
    string input_str;
    cout << "Введите 1 или 2:" << endl << "1 - Ввести матрицу через терминал." << endl << "2 - Ввести матрицу из файла (указать название файла)" << endl;
    cin >> input_str;
    try {
        int input = stoi(input_str);
        if (input == 1) {
            system("clear");
            enter_graph_on_terminal();
        } else if (input == 2) {
            system("clear");
            enter_graph_on_file();
        } else {
            throw invalid_argument("");
        }
    } catch (...) {
        system("clear");
        cout << "Неправильно введённые данные. Попробуйте снова." << endl;
        select_terminal_or_file();
    }
}

int main() {
    system("clear");
    select_terminal_or_file();

    return 0;
}