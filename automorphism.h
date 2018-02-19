#ifndef AUTOMORPHISM_H
#define AUTOMORPHISM_H

#endif // AUTOMORPHISM_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <QProgressBar>
#include <QMessageBox>

using namespace std;


class Automorphism
{
    unsigned char **matrix;
    unsigned char **matrix_2;
    int n;
    int n2;
    vector<int> lens_set;
    int size_elem, new_size;
    vector<int> score;

    int eq(unsigned short *elem, int column, int size);

    int check(unsigned short *elem, int i, int size);

    void Simple(QString str);
public:

    Automorphism(int k, QString &outs);
    Automorphism(int k, string text, string text2);
    Automorphism(int k, int k2, string text, string text2);

    ~Automorphism();

    int getAM(QProgressBar *progress, QString &outs);

    void Exchange(int i, int j);
    void shuffleMatrix(QString &outs);
    vector<int> getScore();

};
