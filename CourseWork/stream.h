#ifndef STREAM
#define STREAM

#include <QString>

class MatrixStream {
    int matrixSize;
    int matrix_2Size;
    char topRange;
    char botRange;
    QString matrixText;
    QString matrix_2Text;
    vector<vector<unsigned char>> matrix;
    vector<vector<unsigned char>> matrix_2;
    QString resultText;
    QString setMatrix(QString text);
    QString setMatrix_2(QString text);
    void setMatrixSize(int size);
    void setMatrix_2Size(int size);
    QString setResult(QString text);
};

#endif // STREAM