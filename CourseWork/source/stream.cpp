#include <stream.h>

void MatrixStream::exchange(std::vector<std::vector<unsigned char> > &matrix, int i, int j) {
    unsigned char tmp;
    int n = matrix.size();
    for (int k = 0; k < n; ++k) {
        tmp = matrix[i][k];
        matrix[i][k] = matrix[j][k];
        matrix[j][k] = tmp;
    }
    for (int k = 0; k < n; ++k) {
        tmp = matrix[k][i];
        matrix[k][i] = matrix[k][j];
        matrix[k][j] = tmp;
    }
}

QString MatrixStream::setMatrix(QString text) {
    matrixText = text;
    std::string std_text = matrixText.toStdString();
    int row = 0;
    int col = 0;
    unsigned int i = 0;
    while (std_text.size() != i) {
        if ((botRange <= (std_text[i] - '0')) &&
            (std_text[i] - '0') <= topRange) {
                if (col == matrixSize || row == matrixSize) return "Wrong input (long line)";
                matrix[row][col] = static_cast<unsigned char>(std_text[i] - '0');
                ++i;
                ++col;
        } else {
            if (std_text[i] == ' ') {
                ++i;
                continue;
            } else if (std_text[i] == '\n') {
                ++row;
                col = 0;
                ++i;
                continue;
            }
            return "Wrong input";
        }
    }
    if (row * col != (matrixSize - 1)*(matrixSize - 1)) {
        return "Wrong input";
    } else {
        return "ok";
    }
}

QString MatrixStream::setMatrix_2(QString text) {
    matrix_2Text = text;
    std::string std_text = matrixText.toStdString();
    int row = 0;
    int col = 0;
    unsigned int i = 0;
    while (std_text.size() != i) {
        if ((botRange <= (std_text[i] - '0')) &&
            (std_text[i] - '0') <= topRange) {
                if (col == matrix_2Size || row == matrix_2Size) return "Wrong input (long line)";
                matrix_2[row][col] = static_cast<unsigned char>(std_text[i] - '0');
                ++i;
                ++col;
        } else {
            if (std_text[i] == ' ') {
                ++i;
                continue;
            } else if (std_text[i] == '\n') {
                ++row;
                col = 0;
                ++i;
                continue;
            }
            return "Wrong input";
        }
    }
    if (row * col != (matrixSize - 1)*(matrixSize - 1)) {
        return "Wrong input";
    } else {
        return "ok";
    }
}

void MatrixStream::setMatrixSize(int size) {
    matrixSize = size;
    matrix = std::vector<std::vector<unsigned char> > (matrixSize, std::vector<unsigned char>(matrixSize));
}

void MatrixStream::setMatrix_2Size(int size) {
    matrix_2Size = size;
    matrix_2 = std::vector<std::vector<unsigned char> > (matrix_2Size, std::vector<unsigned char>(matrix_2Size));
}
