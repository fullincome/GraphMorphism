#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <algorithm>
#include "automorphism.h"
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

private slots:
    void on_genRandomGraphBtn_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_shuffleBtn_clicked();

    void on_automorphismBtn_clicked();

    void on_isomorphismBtn_clicked();

    void on_gomomorphismBtn_clicked();

    void on_spinBox_2_valueChanged(int arg1);

    void on_matrixEdit_textChanged();

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
