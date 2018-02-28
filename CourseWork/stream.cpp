#include <stream.h>

QString MatrixStream::setMatrix(QString text) {
    matrixText = text;
    int row = 0;
    int col = 0;
    int i = 0;
    while (matrixText[i] != '\0')
        if (botRange < matrixText[i] - '0' < topRange) {
                if (col == size || row == size) return "Wrong input (long line)";
                matrix[row][col] = static_cast<unsigned char>(matrixText[i] - '0');
                ++i;
                ++col;
                continue;
        }
        if (col == size) {
            if (matrixText[i] == ' ') {
                ++i;
                continue;
            } else if (matrixText[i] == '\n'){
                ++row;
                ++i;
                continue;
            } else {
                return "Wrong input";
            }
            row++;
    }
    if (row * col != (size - 1)*(size - 1)) {
        return "Wrong input";
    } else {
        return "Ok";
    }
}

QString MatrixStream::setMatrix_2(QString text) {
    matrix_2Text = text;
    int row = 0;
    int col = 0;
    int i = 0;
    while (matrix_2Text[i] != '\0')
        if (botRange < matrix_2Text[i] - '0' < topRange) {
                if (col == size || row == size) return "Wrong input (long line)";
                matrix[row][col] = static_cast<unsigned char>(matrix_2Text[i] - '0');
                ++i;
                ++col;
                continue;
        }
        if (col == size) {
            if (matrix_2Text[i] == ' ') {
                ++i;
                continue;
            } else if (matrix_2Text[i] == '\n'){
                ++row;
                ++i;
                continue;
            } else {
                return "Wrong input";
            }
            row++;
    }
    if (row * col != (size - 1)*(size - 1)) {
        return "Wrong input";
    } else {
        return "Ok";
    }
}

void MatrixStream::setMatrixSize(int size) {
    matrixSize = size;
    matrix = vector<vector<unsigned char>> (matrixSize, vector<unsigned char>(matrixSize));
}

void MatrixStream::setMatrix_2Size(int size) {
    matrix_2Size = size;
    matrix_2 = vector<vector<unsigned char>> (matrix_2Size, vector<unsigned char>(matrix_2Size));
}
