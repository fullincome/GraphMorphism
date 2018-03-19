#ifndef STREAM
#define STREAM

#include <QString>
#include <vector>

class MatrixStream {
public:
    int matrixSize;
    int matrix_2Size;
    char topRange;
    char botRange;
    QString matrixText;
    QString matrix_2Text;
    std::vector<std::vector<unsigned char> > matrix;
    std::vector<std::vector<unsigned char> > matrix_2;
    QString resultText;
    QString setRandomMatrix();
    QString setMatrix(QString text);
    QString setMatrix_2(QString text);
    void setMatrixSize(int size);
    void setMatrix_2Size(int size);
    QString setResult(QString text);
};

#endif // STREAM
