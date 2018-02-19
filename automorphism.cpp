﻿// Automorphism.cpp: определяет точку входа для консольного приложения.
//

#include "automorphism.h"

using namespace std;

static unsigned short matrix_elem[500000][400];
static unsigned short matrix_elem2[500000][400];

int Automorphism::eq(unsigned short *elem, int column, int size) {
    for (int i = 0; i < size; ++i) {
        if ((matrix[column][elem[i]] != matrix_2[size][i]) || (matrix[elem[i]][column] != matrix_2[i][size])) {
            return 0;
        }
    }
    if (matrix_2[size][size] != matrix[column][column]) {
        return 0;
    }
    return 1;
}

int Automorphism::check(unsigned short *elem, int i, int size) {
    for (int k = 0; k < size; ++k) {
        if (elem[k] == i) {
            return 0;
        }
    }
    return 1;
}

void Automorphism::Simple(const QString str)
{
    QMessageBox msg;
    msg.setText(str);
    msg.exec();
}


Automorphism::Automorphism(int k, QString &outs) {
    n = k;
    n2 = k;
    matrix = new unsigned char* [n];
    matrix_2 = new unsigned char* [n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new unsigned char[n];
        matrix_2[i] = new unsigned char[n];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix_2[i][j] = matrix[i][j] = static_cast<int>(rand() % 2);
            outs += QString().sprintf("%d", matrix[i][j]);
        }
        outs.push_back('\n');
    }
}


Automorphism::Automorphism(int k, string text, string text2) {
    n = k;
    n2 = k;
    int l = 0;
    matrix = new unsigned char* [n];
    matrix_2 = new unsigned char* [n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new unsigned char[n];
        matrix_2[i] = new unsigned char[n];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = static_cast<unsigned char>(text[i*n + j + l] - '0');
            matrix_2[i][j] = static_cast<unsigned char>(text2[i*n + j + l] - '0');
        }
        l += 1;
    }
}

Automorphism::Automorphism(int k, int k2, string text, string text2) {
    n = k;
    n2 = k2;
    int l = 0;
    matrix = new unsigned char* [n];
    matrix_2 = new unsigned char* [n2];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new unsigned char[n];
        matrix_2[i] = new unsigned char[n2];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = static_cast<unsigned char>(text[i*n + j + l] - '0');
        }
        l += 1;
    }
    l = 0;
    for (int i = 0; i < n2; ++i) {
        for (int j = 0; j < n2; ++j) {
            matrix_2[i][j] = static_cast<unsigned char>(text2[i*n2 + j + l] - '0');
        }
        l += 1;
    }
}

Automorphism::~Automorphism() {
    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
    for (int i = 0; i < n2; ++i) {
        delete[] matrix_2[i];
    }
    delete[] matrix_2;
}

int Automorphism::getAM(QProgressBar *progress, QString &outs) {
    int ident = 1;
    new_size = 0;
    for (int i = 0; i < n; ++i) {
        if (matrix_2[0][0] == matrix[i][i]) {
            matrix_elem[new_size][0] = i;
            new_size++;
        }
    }
    score.push_back(new_size);
    size_elem = new_size;
    new_size = 0;

    for (int p = 0; p < n2 - 1; ++p) {
        for (int k = 0; k < size_elem; ++k) {
            for (int i = 0; i < n; ++i) {
                if (Automorphism::check(matrix_elem[k], i, p + 1)) {
                    if (Automorphism::eq(matrix_elem[k], i, p + 1)) {
                        for (int z = 0; z < p + 1; ++z) {
                            matrix_elem2[new_size][z] = matrix_elem[k][z];
                        }
                        matrix_elem2[new_size][p + 1] = i;
                        new_size++;
                    }
                }
            }
        }
        // if ((p >= (log(static_cast<double>(n))/log(2.0))) && new_size > 1 && ident == 1) {
        //     Automorphism::Simple("Автоморфизмы найдены");
        //     ident = 0;
        // }
        //    if ((p >= (log(static_cast<double>(n))/log(2.0))) && new_size == 1 && ident == 1) {
        //        Automorphism::Simple("Автоморфизмов нет");
        //        ident = 0;
        // }
               size_elem = new_size;
        for (int i = 0; i < size_elem; ++i) {
            for (int z = 0; z < p + 2; ++z) {
                matrix_elem[i][z] = matrix_elem2[i][z];
            }
        }
        score.push_back(size_elem);
        if ((((p + 1) * 100 / log2(n)) + p * 3) < 90)
            progress->setValue((p + 1) * 100 / log2(n) + p * 3);
        new_size = 0;
    }
    progress->setValue(100);
    for (int i = 0; i < size_elem; ++i) {
        for (int z = 0; z < n2; ++z) {
            //outs.push_back(matrix_elem2[i][z]);
            outs += QString().sprintf("%d", matrix_elem2[i][z]);
            outs.push_back(' ');
        }
        outs.push_back('\n');
    }
    return 0;
}

void Automorphism::Exchange(int i, int j) {
	unsigned char tmp;
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

void Automorphism::shuffleMatrix(QString &outs) {
	for (int i = 0; i < n - 1; ++i) {
        Exchange(i, (rand() % (n - i)) + i);
	}
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            //matrix_2[i][j] = matrix[i][j];
            outs += QString().sprintf("%d", matrix[i][j]);
        }
        outs.push_back('\n');
    }
}

vector<int> Automorphism::getScore() {
    return score;
}

