#include <fstream>
#include <iostream>
#include <string>
#include <map>

using namespace std;

void fill_matrix(int** matrix, const int& n, int& filled_node_counter);
void enter_graph_on_terminal(int** matrix);
void enter_graph_on_file(int** matrix);
void select_data_from_terminal_or_file(int** matrix, int n);
void eulerian_path(int** matrix, const int &n);
void delete_edge(map<int, vector<int>>& edges, int first, int second);

int main() {
    system("clear");

    int** matrix = nullptr;
    select_data_from_terminal_or_file(matrix, 0);

    return 0;
}

void fill_matrix(int** matrix, const int& n, int& filled_node_counter) {
    int tmp_counter_nodes = 0;
    for (int i=1; i<n; i++) {
        for (int j=i+1; j<n; j++) {
            if (tmp_counter_nodes == filled_node_counter) {
                cout << "Введи 0 или 1 в зависимости от наличия связи между " << i << " строкой и " << j << " столбцом:" << endl;
                string input_str;
                cin >> input_str;
                try {
                    const int input = stoi(input_str);
                    if (input != 0 && input != 1) throw invalid_argument("Матрица может содержать только 0 или 1.");
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
void enter_graph_on_terminal(int** matrix) {
    string input_str;
    cout << "Введи число вершин графа:" << endl;
    cin >> input_str;
    try {
        const int matrix_dimensions = stoi(input_str) + 1;
        if (matrix_dimensions < 3) throw invalid_argument("Число вершин графа не может быть меньше 2.");
        matrix = new int*[matrix_dimensions];
        for (int i=0; i<matrix_dimensions; i++) {
            matrix[i] = new int[matrix_dimensions];
        }
        for (int i=0; i<matrix_dimensions; i++) {
            *(*(matrix + i)) = i;
            *(*(matrix) + i) = i;
        }
        int filled_node_counter = 0;
        system("clear");
        fill_matrix(matrix, matrix_dimensions, filled_node_counter);

        system("clear");
        eulerian_path(matrix, matrix_dimensions);
    } catch (...) {
        system("clear");
        cout << "Неправильно введённые данные. Попробуйте снова." << endl;
        enter_graph_on_terminal(matrix);
    }
}
void enter_graph_on_file(int** matrix) {
    string name_file;
    cout << "Введи название файла (в формате '.txt'), находящегося в этой же директории:" << endl;
    cin >> name_file;
    try {
        int matrix_dimensions = 0;
        ifstream matrix_file(name_file);
        if (matrix_file.is_open()) {
            string tmp_line;
            getline(matrix_file, tmp_line);
            matrix_dimensions = tmp_line.length()/2 + 2;
            if (matrix_dimensions < 3) throw invalid_argument("Число графов не может быть меньше 2.");
            matrix = new int*[matrix_dimensions];
            for (int i=0; i<matrix_dimensions; i++) {
                matrix[i] = new int[matrix_dimensions];
            }
            int p=1;
            do {
                for (int i=0; i<matrix_dimensions; i++) {
                    *(*(matrix + i)) = i;
                    *(*(matrix) + i) = i;
                }
                int index = p*2;
                for (int j=p+1; j<matrix_dimensions; j++) {
                    cout << tmp_line << " " << index << "-" << tmp_line[index] << endl;
                    const int num = stoi(&tmp_line[index]);
                    if (num != 0 && num != 1) throw invalid_argument("Значение в матрице может быть только 1 ил 0.");
                    *(*(matrix + p) + j) = num;
                    *(*(matrix + j) + p) = num;
                    index+=2;
                }
                p++;
            } while (getline(matrix_file, tmp_line));
        } else {
            system("clear");
            cout << "Такого файла нету в данной директории." << endl;
            enter_graph_on_file(matrix);
        }
        matrix_file.close();
        if (matrix == nullptr) throw invalid_argument("Неполучилось считать матрицу из файла.");
        system("clear");
        eulerian_path(matrix, matrix_dimensions);
    } catch (...) {
        system("clear");
        cout << "Неправильно введённые данные. Попробуйте снова." << endl;
        enter_graph_on_terminal(matrix);
    }
}
void select_data_from_terminal_or_file(int** matrix, const int n) {
    string input_str;
    cout << "Введите цифру:" << endl << "1 - Ввести через терминал матрицу смежностей." << endl << "2 - Ввести из файла матрицу смежностей (указать название файла)";
    if (matrix == nullptr) {
        cout << endl << "3 - Выход." << endl;
    } else {
        cout << endl << "3 - Цикл Эйлера" << endl << "4 - Выход." << endl;
    }
    cin >> input_str;
    try {
        const int input = stoi(input_str);
        if (input == 1) {
            system("clear");
            enter_graph_on_terminal(matrix);
        } else if (input == 2) {
            system("clear");
            enter_graph_on_file(matrix);
        } else if (input == 3) {
            if (matrix == nullptr) {
                system("clear");
                exit(0);
            }
            eulerian_path(matrix, n);
        } else if (input == 4 && matrix != nullptr) {
            system("clear");
            exit(0);
        }else throw invalid_argument("");
    } catch (...) {
        system("clear");
        cout << "Неправильно введённые данные. Попробуйте снова." << endl;
        select_data_from_terminal_or_file(matrix, n);
    }
}
void eulerian_path(int **matrix, const int &n) {
    map<int, vector<int>> edges;
    int edge_counter = 0;
    for (int i=1; i<n; i++) {
        vector<int> counter;
        edges[i] = counter;
        for (int j=1; j<n; j++) {
            if (*(*(matrix + i) + j) == 1) {
                edges[i].push_back(j);
                if (j > i) {
                    edge_counter++;
                }
            }
        }
        if (edges[i].size()%2 != 0) {
            cout << "Четность всех вершин не соблюдена." << endl;
            select_data_from_terminal_or_file(matrix, n);
        }
    }
    int current_point = 0;
    int next_point = 0;
    cout << "Введите вершину для начала цикла Эйлера: " << endl;
    string input_str;
    cin >> input_str;
    try {
        current_point = stoi(input_str);
        if (current_point < 1 || current_point > n-1) {
            cout << "Вершина не найдена.";
            eulerian_path(matrix, n);
        }
        system("clear");
    } catch (...) {
        system("clear");
        cout << "Неправильно введённые данные. Попробуйте снова." << endl;
        eulerian_path(matrix, n);
    }

    cout << "Цикл эйлера: " << endl << current_point;
    while (edge_counter != 0) {
        bool isEnter = false;
        for (int i=0; i<edges[current_point].size(); i++) {
            next_point = edges[current_point][i];
            if (edges[next_point].size() > 1) {
                cout << next_point;
                delete_edge(edges, current_point, next_point);
                current_point = next_point;
                edge_counter--;
                isEnter = true;
                break;
            }
        }
        if (!isEnter && !edges[current_point].empty()) {
            next_point = edges[current_point][0];
            cout << next_point;
            delete_edge(edges, current_point, next_point);
            current_point = next_point;
            edge_counter--;
        }
    }
    cout << endl;
    select_data_from_terminal_or_file(matrix, n);
}
void delete_edge(map<int, vector<int>>& edges, const int first, const int second) {

    for (int i=0; i<edges[second].size(); i++) {
        if (edges[second][i] == first) {
            edges[second].erase(edges[second].begin() + i);
            break;
        }
    }

    for (int i=0; i<edges[first].size(); i++) {
        if (edges[first][i] == second) {
            edges[first].erase(edges[first].begin() + i);
            break;
        }
    }

}