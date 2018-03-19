#ifndef Morphism_H
#define Morphism_H

#endif // Morphism_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <QProgressBar>
#include <QMessageBox>
#include <stream.h>

using namespace std;


class Morphism
{
    vector<vector<unsigned char> > matrix;
    vector<vector<unsigned char> > matrix_2;
    int n;
    int n_2;
    vector<int> lens_set;
    int size_elem, new_size;
    vector<int> score;

    int eq(unsigned short *elem, int column, int size);
    int check(unsigned short *elem, int i, int size);

    void Simple(QString str);
public:

    Morphism(int k, int k_2, vector<vector<unsigned char> > matrix, vector<vector<unsigned char> > matrix_2);

    int getAutomorphism(QProgressBar *progress, QString &outs);
    int getIsomorphism(QProgressBar *progress, QString &outs);
    int getGomomorphism(QProgressBar *progress, QString &outs);

    void Exchange(int i, int j);
    void shuffleMatrix(QString &outs);
    vector<int> getScore();

};
