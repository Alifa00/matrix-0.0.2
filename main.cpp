#include <iostream>
#include <sstream>
using namespace std;
void destroy(float ** elements,
             unsigned int ranks) {
    for (unsigned int i = 0; i < ranks; ++i) {
        delete[] elements[i];
    }
    delete[] elements;
}
float ** create_matr(unsigned int graphs,
                       unsigned int ranks) {
    float ** matr;
    matr = new float * [ranks];
    for (unsigned int i = 0; i < ranks; ++i) {
        matr[i] = new float[graphs];
        for (unsigned int j = 0; j < graphs; ++j) {
            matr[i][j] = 0.0f;
        }
    }
    return matr;
}
float det(float ** matr,
          unsigned int graphs,
          unsigned int ranks) {
    if (graphs != ranks) {
        return 0;
    }
    float result;
    if (graphs == 1) {
        result = matr[0][0];
    }
    else if (graphs == 2) {
        result = matr[0][0] * matr[1][1] - matr[0]
        [1] * matr[1][0];
    }
    else {
        for (unsigned int j = 0; j < graphs; j++) {
            float ** minor;
            minor = create_matr(graphs - 1, ranks - 1);
            for (unsigned int y = 0; y < ranks - 1; ++y) {
                int k = 0;
                for (unsigned int x = 0; x < graphs - 1; ++x) {
                    if (x == j) {
                        k = 1;
                    }
                    minor[y][x] = matr[y + 1][x + k];
                }
            }
            switch (j % 2) {
                case 0:
                    result += matr[0][j] * det(minor, graphs - 1, ranks - 1);
                    break;
                case 1:
                    result += (-matr[0][j]) * det(minor, graphs - 1, ranks - 1);
                    break;
            }
        }
    }
    return result;
}
float ** algebraic_matr(float ** matr,unsigned int graphs,unsigned int ranks) {
    float ** result;
    result = create_matr(graphs, ranks);
    for (unsigned int j = 0; j < ranks; j++) {
        for (unsigned int i = 0; i < graphs; i++) {
            float ** minor;
            minor = create_matr(graphs - 1, ranks - 1);
            int k1 = 0;
            for (unsigned int y = 0; y < ranks - 1; ++y) {
                int k = 0;
                for (unsigned int x = 0; x < graphs - 1; ++x) {
                    if (x == i) {
                        k = 1;
                    }
                    if (y == j) {
                        k1 = 1;
                    }
                    minor[y][x] = matr[y + k1][x + k];
                }
            }
            switch ((j + i) % 2) {
                case 0:
                    result[j][i] = det(minor, graphs - 1, ranks - 1);
                    break;
                case 1:
                    result[j][i] = (-det(minor, graphs - 1, ranks - 1));
                    break;
            }
        }
    }
    return result;
}
float ** sum(float ** matr1,unsigned int graphs1,unsigned int ranks1,
             float ** matr2,unsigned int graphs2,unsigned int ranks2,unsigned int & newgraphs,unsigned int & newranks) {
    float ** result;
    if (graphs1 != graphs2 || ranks1 != ranks2) {
        result = nullptr;
        return result;
    }
    result = create_matr(graphs1, ranks1);
    for (unsigned int j = 0; j < ranks1; j++) {
        for (unsigned int i = 0; i < graphs1; i++) {
            result[j][i] = matr1[j][i] + matr2[j][i];
        }
    }
    newgraphs = graphs1;
    newranks = ranks1;
    return result;
}
float ** sub(float ** matr1,unsigned int graphs1,unsigned int ranks1,
             float ** matr2,unsigned int graphs2,unsigned int ranks2,unsigned int & newgraphs,unsigned int & newranks) {
    float ** result;
    if (graphs1 != graphs2 || ranks1 != ranks2) {
        result = nullptr;
        return result;
    }
    result = create_matr(graphs1, ranks1);
    for (unsigned int j = 0; j < ranks1; j++) {
        for (unsigned int i = 0; i < graphs1; i++) {
            result[j][i] = matr1[j][i] + matr2[j][i];
        }
    }
    newgraphs = graphs1;
    newranks = ranks1;
    return result;
}
float ** mul(float ** matr1,unsigned int graphs1,unsigned int ranks1,
             float ** matr2,unsigned int graphs2,unsigned int ranks2,unsigned int & newgraphs,unsigned int & newranks) {
    float ** result;
    if (graphs1 != ranks2) {
        result = nullptr;
        return result;
    }
    result = create_matr(graphs2, ranks1);
    for (unsigned int j = 0; j < ranks1; j++) {
        for (unsigned int i = 0; i < graphs2; i++) {
            float y = 0;
            for (unsigned int z = 0; z < graphs1; z++) {
                y += matr1[j][z] * matr2[z][i];
            }
            result[j][i] = y;
        }
    }
    newgraphs = graphs2;
    newranks = ranks1;
    return result;
}
float ** transplate(float ** matr,unsigned int graphs,unsigned int ranks,unsigned int & newgraphs,unsigned int & newranks) {
    float ** result;
    result = create_matr(ranks, graphs);
    for (unsigned int j = 0; j < graphs; j++) {
        for (unsigned int i = 0; i < ranks; i++) {
            result[j][i] = matr[i]
            [j];
        }
    }
    newgraphs = ranks;
    newranks = graphs;
    return result;
}
float ** reverse(float ** matr, unsigned int graphs,unsigned int ranks,unsigned int & newgraphs,unsigned int & newranks) {
    float ** result;
    if (det(matr, graphs, ranks) == 0) {
        result = nullptr;
        return result;
    }
    if (graphs == ranks && ranks == 1) {
        result = nullptr;
        return result;
    }
    result = create_matr(graphs, ranks);
    float ** a = algebraic_matr(matr, graphs, ranks);
    a = transplate(a, graphs, ranks, newgraphs, newranks);
    float d = det(matr, graphs, ranks);
    for (unsigned int j = 0; j < ranks; j++) {
        for (unsigned int i = 0; i < graphs; i++) {
            result[j][i] = a[j][i] / d;
        }
    }
    newgraphs = graphs;
    newranks = ranks;
    return result;
}
bool get_matr(float ** & matr,unsigned int ngraphs,unsigned int nranks) {
    matr = create_matr(ngraphs, nranks);
    for (unsigned int j = 0; j < nranks; j++) {
        string new_row;
        getline(cin, new_row);
        istringstream stream(new_row);
        for (unsigned int i = 0; i < ngraphs; i++) {
            if (!(stream >> matr[j][i])) {
                destroy(matr, nranks);
                return false;
            }
        }
    }
    return true;
}
void cout_matr(float ** matr,unsigned int ngraphs,unsigned int nranks) {
    for (unsigned int j = 0; j < nranks; j++) {
        for (unsigned int i = 0; i < ngraphs; i++) {
            if (matr[j][i] == -0) {
                matr[j][i] = 0;
            }
            cout << matr[j][i] << "\t";
        }
        cout << "\n";
    }
}
bool get_size(unsigned int & graphs,unsigned int & ranks) {
    string header;
    char razdel;
    getline(cin, header);
    istringstream str(header);
    if ((str >> ranks) && (str >> razdel) && (str >> graphs) && (razdel == ',')) {
        return true;
    }
    return false;
}
int main() {
    float ** matr1;
    float ** matr2;
    float ** matr3;
    char op;
    unsigned int graphs1, ranks1,
    graphs2, ranks2, graphs3,
    ranks3;
    if (get_size(graphs1, ranks1) && get_matr(matr1, graphs1, ranks1)) {
        string com;
        getline(cin, com);
        istringstream stream(com);
        if (stream >> op) {
            switch (op) {
                case 'T':
                    matr3 = transplate(matr1, graphs1, ranks1, graphs3, ranks3);
                    break;
                case 'R':
                    matr3 = reverse(matr1, graphs1, ranks1, graphs3, ranks3);
                    break;
                default:
                    if (op != '+' && op != '-' && op != '*') {
                        cout << "An error has occured while reading input data.";
                        exit(0);
                    }
                    break;
            }
            if (matr3 != nullptr && (op == 'T' || op == 'R')) {
                cout_matr(matr3, graphs3, ranks3);
                destroy(matr3, ranks3);
                destroy(matr1, ranks1);
                exit(0);
            }
            else if (matr3 == nullptr) {
                cout << "There is no reverse matr.";
                destroy(matr1, ranks1);
                exit(0);
            }
        }
        else {
            cout << "An error has occured while reading input data.";
            exit(0);
        }
    }
    else {
        cout << "An error has occured while reading input data.";
        exit(0);
    }
    if (get_size(graphs2, ranks2) && get_matr(matr2, graphs2, ranks2)) {
        switch (op) {
            case '+':
                matr3 = sum(matr1, graphs1, ranks1, matr2, graphs2, ranks2, graphs3, ranks3);
                break;
            case '-':
                matr3 = sub(matr1, graphs1, ranks1, matr2, graphs2, ranks2, graphs3, ranks3);
                break;
            case '*':
                matr3 = mul(matr1, graphs1, ranks1, matr2, graphs2, ranks2, graphs3, ranks3);
                break;
        }
        if (matr3 != nullptr) {
            cout_matr(matr3, graphs3, ranks3);
            destroy(matr3, ranks3);
            destroy(matr1, ranks1);
            destroy(matr2, ranks2);
        }
        else if (matr3 == nullptr) {
            cout << "Wrong matres";
            destroy(matr2, ranks2);
            destroy(matr1, ranks1);
            exit(0);
        }
    }
    else {
        cout << "An error has occured while reading input data.";
        exit(0);
    }
}
