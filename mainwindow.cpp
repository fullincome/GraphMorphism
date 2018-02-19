#include "mainwindow.h"
#include "ui_mainwindow.h"

int matrixSize = 2;
int matrixSize_2 = 2;

QString out;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->shuffleBtn->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    matrixSize = arg1;
}


void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
    matrixSize_2 = arg1;
}

void MainWindow::on_genRandomGraphBtn_clicked()
{
    QString inputMatrix;
    out.clear();
    ui->textEdit_2->clear();
    Automorphism am(matrixSize, inputMatrix);
    ui->textEdit->setPlainText(inputMatrix);
    ui->textEdit_3->setPlainText(inputMatrix);
    am.getAM(ui->progressBar, out);
    ui->textEdit_2->setPlainText(out);
    out.clear();

    vector<int> score = am.getScore();

    //ui->setupUi(this);

    int N = score.size(); //Вычисляем количество точек, которые будем отрисовывать
    QVector<double> x(N + 1), y(N + 1); //Массивы координат точек

    x[0] = y[0] = 0;
    for (int i=0; i < N; ++i)//Пробегаем по всем точкам
    {
        x[i + 1] = i + 1;
        y[i + 1] = score[i];
    }

    ui->widget->clearGraphs();//Если нужно, но очищаем все графики
    //Добавляем один график в widget
    ui->widget->addGraph();
    //Говорим, что отрисовать нужно график по нашим двум массивам x и y
    ui->widget->graph(0)->setData(x, y);
    //Подписываем оси Ox и Oy
    ui->widget->xAxis->setLabel("N");
    ui->widget->yAxis->setLabel("Size |Mn|");

    //Установим область, которая будет показываться на графике
    if (N >= 50) {
        ui->widget->xAxis->setRange(0, 30);//Для оси Ox
    }
    else {
        ui->widget->xAxis->setRange(0, N);//Для оси Ox
    }

    //Для показа границ по оси Oy сложнее, так как надо по правильному
    //вычислить минимальное и максимальное значение в векторах
    int minY = 0, maxY = static_cast<int>((*max_element(score.begin(), score.end())) * 1.2);

    ui->widget->yAxis->setRange(minY, maxY);//Для оси Oy

    ui->widget->replot();
}



void MainWindow::on_automorphismBtn_clicked()
{
    ui->label->setText("Автоморфизмы:");
    out.clear();
    ui->outputEdit->clear();
    str message;
    QString stroka = ui->matrixEdit->toPlainText();
    string texts = stroka.toStdString();

    //message.Simple(stroka);

    Automorphism am(matrixSize, texts, texts);
    am.getAM(ui->progressBar, out);
    ui->outputEdit->setPlainText(out);


    vector<int> score = am.getScore();

    //ui->setupUi(this);

    int N = score.size(); //Вычисляем количество точек, которые будем отрисовывать
    QVector<double> x(N + 1), y(N + 1); //Массивы координат точек

    x[0] = y[0] = 0;
    for (int i=0; i < N; ++i)//Пробегаем по всем точкам
    {
        x[i + 1] = i + 1;
        y[i + 1] = score[i];
    }

    ui->widget->clearGraphs();//Если нужно, но очищаем все графики
    //Добавляем один график в widget
    ui->widget->addGraph();
    //Говорим, что отрисовать нужно график по нашим двум массивам x и y
    ui->widget->graph(0)->setData(x, y);
    //Подписываем оси Ox и Oy
    ui->widget->xAxis->setLabel("N");
    ui->widget->yAxis->setLabel("Size |Mn|");

    //Установим область, которая будет показываться на графике
    if (N >= 50) {
        ui->widget->xAxis->setRange(0, 30);//Для оси Ox
    }
    else {
        ui->widget->xAxis->setRange(0, N);//Для оси Ox
    }

    //Для показа границ по оси Oy сложнее, так как надо по правильному
    //вычислить минимальное и максимальное значение в векторах
    int minY = 0, maxY = static_cast<int>((*max_element(score.begin(), score.end())) * 1.2);

    ui->widget->yAxis->setRange(minY, maxY);//Для оси Oy

    ui->widget->replot();
}


void MainWindow::on_shuffleBtn_clicked()
{
    QString shuffleString;
    shuffleString.clear();
    QString stroka = ui->textEdit->toPlainText();
    string texts = stroka.toStdString();
    Automorphism am(matrixSize, texts, texts);
    am.shuffleMatrix(shuffleString);
    ui->textEdit->setPlainText(shuffleString);
}



void MainWindow::on_isomorphismBtn_clicked()
{
    ui->label->setText("Изоморфизмы:");
    out.clear();
    ui->textEdit_2->clear();
    str message;
    QString stroka = ui->textEdit->toPlainText();
    string texts = stroka.toStdString();
    QString stroka2 = ui->textEdit_3->toPlainText();
    string texts2 = stroka2.toStdString();

    //message.Simple(stroka);

    Automorphism am(matrixSize, texts, texts2);
    am.getAM(ui->progressBar, out);
    ui->textEdit_2->setPlainText(out);


    vector<int> score = am.getScore();

    //ui->setupUi(this);

    int N = score.size(); //Вычисляем количество точек, которые будем отрисовывать
    QVector<double> x(N + 1), y(N + 1); //Массивы координат точек

    x[0] = y[0] = 0;
    for (int i=0; i < N; ++i)//Пробегаем по всем точкам
    {
        x[i + 1] = i + 1;
        y[i + 1] = score[i];
    }

    ui->widget->clearGraphs();//Если нужно, но очищаем все графики
    //Добавляем один график в widget
    ui->widget->addGraph();
    //Говорим, что отрисовать нужно график по нашим двум массивам x и y
    ui->widget->graph(0)->setData(x, y);
    //Подписываем оси Ox и Oy
    ui->widget->xAxis->setLabel("N");
    ui->widget->yAxis->setLabel("Size |Mn|");

    //Установим область, которая будет показываться на графике
    if (N >= 50) {
        ui->widget->xAxis->setRange(0, 30);//Для оси Ox
    }
    else {
        ui->widget->xAxis->setRange(0, N);//Для оси Ox
    }

    //Для показа границ по оси Oy сложнее, так как надо по правильному
    //вычислить минимальное и максимальное значение в векторах
    int minY = 0, maxY = static_cast<int>((*max_element(score.begin(), score.end())) * 1.2);

    ui->widget->yAxis->setRange(minY, maxY);//Для оси Oy

    ui->widget->replot();
}

void MainWindow::on_gomomorphismBtn_clicked()
{
    ui->label->setText("Гомоморфизмы:");
    out.clear();
    ui->textEdit_2->clear();
    str message;
    QString stroka = ui->textEdit->toPlainText();
    string texts = stroka.toStdString();
    QString stroka2 = ui->textEdit_3->toPlainText();
    string texts2 = stroka2.toStdString();

    //message.Simple(stroka);

    Automorphism am(matrixSize, matrixSize_2, texts, texts2);
    am.getAM(ui->progressBar, out);
    ui->textEdit_2->setPlainText(out);


    vector<int> score = am.getScore();

    //ui->setupUi(this);

    int N = score.size(); //Вычисляем количество точек, которые будем отрисовывать
    QVector<double> x(N + 1), y(N + 1); //Массивы координат точек

    x[0] = y[0] = 0;
    for (int i=0; i < N; ++i)//Пробегаем по всем точкам
    {
        x[i + 1] = i + 1;
        y[i + 1] = score[i];
    }

    ui->widget->clearGraphs();//Если нужно, но очищаем все графики
    //Добавляем один график в widget
    ui->widget->addGraph();
    //Говорим, что отрисовать нужно график по нашим двум массивам x и y
    ui->widget->graph(0)->setData(x, y);
    //Подписываем оси Ox и Oy
    ui->widget->xAxis->setLabel("N");
    ui->widget->yAxis->setLabel("Size |Mn|");

    //Установим область, которая будет показываться на графике
    if (N >= 50) {
        ui->widget->xAxis->setRange(0, 30);//Для оси Ox
    }
    else {
        ui->widget->xAxis->setRange(0, N);//Для оси Ox
    }

    //Для показа границ по оси Oy сложнее, так как надо по правильному
    //вычислить минимальное и максимальное значение в векторах
    int minY = 0, maxY = static_cast<int>((*max_element(score.begin(), score.end())) * 1.2);

    ui->widget->yAxis->setRange(minY, maxY);//Для оси Oy

    ui->widget->replot();
}



void MainWindow::on_matrixEdit_textChanged()
{
    ui->matrixEdit->toPlainText().isEmpty() ?
        ui->shuffleBtn->setDisabled(true):
        ui->shuffleBtn->setEnabled(true);
}
