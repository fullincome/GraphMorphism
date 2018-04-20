#ifndef STREAM
#define STREAM

#include <QString>
#include <vector>

class MatrixStream {
public:
    int matrixSize;
    int matrix_2Size;
    char topRange = 1;
    char botRange = 0;
    QString matrixText;
    QString matrix_2Text;
    std::vector<std::vector<unsigned char> > matrix;
    std::vector<std::vector<unsigned char> > matrix_2;
    QString resultText;

    void exchange(std::vector<std::vector<unsigned char> > &matrix, int i, int j);
    QString setRandomMatrix(std::vector<std::vector<unsigned char> > matrix);
    QString setMatrix(QString text);
    QString setMatrix_2(QString text);
    void setMatrixSize(int size);
    void setMatrix_2Size(int size);
    QString setResult(QString text);
};

#endif // STREAM
