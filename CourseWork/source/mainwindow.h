#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <algorithm>
#include "morphism.h"
#include <QString>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    MatrixStream mStream;

    void printPlot(vector<long long> v);

    void randomMatrix(MatrixStream &mStream);
    void shuffleMatrix(MatrixStream &mStream);
    void shuffle_2Matrix(MatrixStream &mStream);

private slots:
    void on_shuffleBtn_clicked();
    void on_genRandomGraphBtn_clicked();

    void on_automorphismBtn_clicked();
    void on_isomorphismBtn_clicked();
    void on_gomomorphismBtn_clicked();

    void on_matrixSpinBox_valueChanged(int arg1);
    void on_matrixSpinBox_2_valueChanged(int arg1);

    void on_matrixEdit_textChanged();
    void on_matrix_2Edit_textChanged();

    void on_rangeSpinBox_valueChanged(int arg1);

    void on_copyMatrixBtn_clicked();

    void on_shuffle_2Btn_clicked();

private:
    Ui::MainWindow *ui;
};

class str: public QMainWindow
{
    Q_OBJECT
public:
    void Simple(QString str)
    {
        QMessageBox msg;
        msg.setText(str);
        msg.exec();
    }
};


#endif // MAINWINDOW_H
