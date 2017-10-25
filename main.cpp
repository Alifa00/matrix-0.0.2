#include <iostream>
#include <sstream>
using namespace std;
struct mtrx {
        bool Succes = false;
        int Row;
        int Column;
        float ** Matrix;
};
mtrx InitZero(int columns, int rows) {
        mtrx result;
        float ** matrix;
        matrix = new float * [rows];
        for (int i = 0; i < rows; ++i) {
                matrix[i] = new float[columns];
                for (int j = 0; j < columns; ++j) {
                        matrix[i][j] = 0.0 f;
                }
        }
        result.Succes = true;
        result.Matrix = matrix;
        result.Column = columns;
        result.Row = rows;
        return result;
}
float det(mtrx Mat) {
        float result;
        if (Mat.Column == Mat.Row) {
                if (Mat.Column == 1) {
                        result = Mat.Matrix[0][0];
                }
                else if (Mat.Column == 2) {
                        result = Mat.Matrix[0][0] * Mat.Matrix[1][1] - Mat.Matrix[0][1] * Mat.Matrix[1][0];
                }
                else {
                        for (int j = 0; j < Mat.Column; j++) {
                                mtrx minor = InitZero(Mat.Row - 1, Mat.Column - 1);
                                for (int y = 0; y < Mat.Row - 1; ++y) {
                                        int k = 0;
                                        for (int x = 0; x < Mat.Column - 1; ++x) {
                                                if (x == j) {
                                                        k = 1;
                                                }
                                                minor.Matrix[y][x] = Mat.Matrix[y + 1][x + k];
                                        }
                                }
                                switch (j % 2) {
                                        case 0:
                                                result += Mat.Matrix[0][j] * det(minor);
                                                break;
                                        case 1:
                                                result += (-Mat.Matrix[0][j]) * det(minor);
                                                break;
                                }
                        }
                }
                return result;
        }
        else {
                return 0;
        }
}
mtrx AlgdopMatrix(mtrx Mat) {
        mtrx result;
        result = InitZero(Mat.Column, Mat.Row);
        for (int j = 0; j < Mat.Row; j++) {
                for (int i = 0; i < Mat.Column; i++) {
                        mtrx minor = InitZero(Mat.Row - 1, Mat.Column - 1);
                        int k1 = 0;
                        for (int y = 0; y < Mat.Row - 1; ++y) {
                                int k = 0;
                                for (int x = 0; x < Mat.Column - 1; ++x) {
                                        if (x == i) {
                                                k = 1;
                                        }
                                        if (y == j) {
                                                k1 = 1;
                                        }
                                        minor.Matrix[y][x] = Mat.Matrix[y + k1][x + k];
                                }
                        }
                        switch ((j + i) % 2) {
                                case 0:
                                        result.Matrix[j][i] = det(minor);
                                        break;
                                case 1:
                                        result.Matrix[j][i] = (-det(minor));
                                        break;
                        }
                }
        }
        return result;
}
mtrx sum(mtrx Mat1, mtrx Mat2) {
        mtrx result;
        result = InitZero(Mat1.Column, Mat1.Row);
        if ((Mat1.Row == Mat2.Row) && (Mat1.Column == Mat2.Column)) {
                for (int j = 0; j < Mat1.Row; j++) {
                        for (int i = 0; i < Mat1.Column; i++) {
                                result.Matrix[j][i] = Mat1.Matrix[j][i] + Mat2.Matrix[j][i];
                        }
                }
        }
        else {
                result.Succes = false;
        }
        return result;
}
mtrx sub(mtrx Mat1, mtrx Mat2) {
        mtrx result;
        result = InitZero(Mat1.Column, Mat1.Row);
        if ((Mat1.Row == Mat2.Row) && (Mat1.Column == Mat2.Column)) {
                for (int j = 0; j < Mat1.Row; j++) {
                        for (int i = 0; i < Mat1.Column; i++) {
                                result.Matrix[j][i] = Mat1.Matrix[j][i] - Mat2.Matrix[j][i];
                        }
                }
        }
        else {
                result.Succes = false;
        }
        return result;
}
mtrx mul(mtrx Mat1, mtrx Mat2) {
        mtrx result;
        result = InitZero(Mat2.Column, Mat1.Row);
        if (Mat1.Column == Mat2.Row) {
                for (int j = 0; j < Mat1.Row; j++) {
                        for (int i = 0; i < Mat2.Column; i++) {
                                float y = 0;
                                for (int z = 0; z < Mat1.Column; z++) {
                                        y += Mat1.Matrix[j][z] * Mat2.Matrix[z][i];
                                }
                                result.Matrix[j][i] = y;
                        }
                }
        }
        else {
                result.Succes = false;
        }
        return result;
}
mtrx Tr(mtrx Mat) {
        mtrx result;
        result = InitZero(Mat.Row, Mat.Column);
        for (int j = 0; j < Mat.Column; j++) {
                for (int i = 0; i < Mat.Row; i++) {
                        result.Matrix[j][i] = Mat.Matrix[i][j];
                }
        }
        return result;
}
mtrx R(mtrx Mat) {
        mtrx result;
        if (det(Mat) != 0) {
                result = InitZero(Mat.Row, Mat.Column);
                mtrx A = AlgdopMatrix(Mat);
                A = Tr(A);
                for (int j = 0; j < Mat.Column; j++) {
                        for (int i = 0; i < Mat.Row; i++) {
                                result.Matrix[j][i] = A.Matrix[j][i] * (1 / (det(Mat)));
                        }
                }
                return result;
        }
        else {
                result.Succes = false;
                return result;
        }
}
bool getMatrix(float ** matrix, int ncolumns, int nrows) {
        for (int j = 0; j < nrows; j++) {
                string newrow;
                getline(cin, newrow);
                istringstream stream(newrow);
                for (int i = 0; i < ncolumns; i++) {
                        if (!(stream >> matrix[j][i])) {
                                return false;
                        }
                }
        }
        return true;
}
void coutMatrix(mtrx Matsign) {
        for (int j = 0; j < Matsign.Row; j++) {
                for (int i = 0; i < Matsign.Column; i++) {
                        if (Matsign.Matrix[j][i] == -0) {
                                Matsign.Matrix[j][i] = 0;
                        }
                        cout << Matsign.Matrix[j][i] << "\t";
                }
                cout << "\n";
        }
}
mtrx getfullMatrix() {
        mtrx result;
        float ** matrix;
        string header;
        int rows;
        int columns;
        char razdel;
        getline(cin, header);
        istringstream str(header);
        if ((str >> rows) && (str >> razdel) && (str >> columns) && (razdel == ',')) {
                matrix = new float * [rows];
                for (int i = 0; i < rows; ++i) {
                        matrix[i] = new float[columns];
                        for (int j = 0; j < columns; ++j) {
                                matrix[i][j] = 0.0 f;
                        }
                }
                result.Succes = getMatrix(matrix, columns, rows);
                result.Row = rows;
                result.Column = columns;
                result.Matrix = matrix;
                return result;
        }
        result.Succes = false;
        return result;
}
int main() {
        mtrx Mat3sign;
        mtrx Mat1sign;
        mtrx Mat2sign;
        string strop;
        char op;
        Mat1sign = getfullMatrix();
        getline(cin, strop);
        istringstream streamop(strop);
        streamop >> op;
        if (Mat1sign.Succes) {
                switch (op) {
                        case 'T':
                                Mat3sign = Tr(Mat1sign);
                                break;
                        case 'R':
                                Mat3sign = R(Mat1sign);
                                if (!Mat3sign.Succes) {
                                        cout << "There is no such matrix";
                                        exit(0);
                                }
                                break;
                        default:
                                if ((op != '+') && (op != '-') && (op != '*')) {
                                        cout << "An error ocured while reading numbers";
                                        exit(0);
                                }
                                break;
                }
        }
        else {
                cout << "An error ocurred while reading numbers";
                exit(0);
        }
        if (Mat3sign.Succes) {
                coutMatrix(Mat3sign);
                exit(0);
        }
        Mat2sign = getfullMatrix();
        if (Mat2sign.Succes) {
                switch (op) {
                        case '+':
                                Mat3sign = sum(Mat1sign, Mat2sign);
                                break;
                        case '*':
                                Mat3sign = mul(Mat1sign, Mat2sign);
                                if (!Mat3sign.Succes) {
                                        cout << "Wrong matrixes";
                                        exit(0);
                                }
                                break;
                        case '-':
                                Mat3sign = sub(Mat1sign, Mat2sign);
                                break;
                }
        }
        else {
                cout << "An error ocurred while reading numbers";
                exit(0);
        }
        if ((Mat1sign.Succes) && (Mat2sign.Succes) && (Mat3sign.Succes)) {
                coutMatrix(Mat3sign);
        }
        else {
                exit(0);
        }
}
