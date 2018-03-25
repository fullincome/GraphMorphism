#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{   
    ui->setupUi(this);
    ui->shuffleBtn->setDisabled(true);

    mStream.botRange = 0;
    mStream.topRange = 1;
    mStream.setMatrixSize(2);
    mStream.setMatrixSize(2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::printPlot(vector<long long> v) {
    vector<long long> score = v;

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

void MainWindow::randomMatrix(MatrixStream &mStream) {
    mStream.matrixText.clear();
    int n = mStream.matrixSize;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            mStream.matrixText += QString().sprintf("%d", mStream.botRange + rand() % (mStream.topRange + 1));
        }
        mStream.matrixText.push_back('\n');
    }
    mStream.setMatrix(mStream.matrixText);
    ui->matrixEdit->setText(mStream.matrixText);
}

void MainWindow::shuffleMatrix(MatrixStream &mStream) {
    mStream.matrixText.clear();
    int n = mStream.matrixSize;
    for (int i = 0; i < n - 1; ++i) {
        mStream.exchange(mStream.matrix, i, (rand() % (n - i)) + i);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            mStream.matrixText += QString().sprintf("%d", mStream.matrix[i][j]);
        }
        mStream.matrixText.push_back('\n');
    }
    mStream.setMatrix(mStream.matrixText);
    ui->matrixEdit->setText(mStream.matrixText);
}

void MainWindow::on_matrixSpinBox_valueChanged(int arg1)
{
    mStream.setMatrixSize(arg1);
}

void MainWindow::on_matrixSpinBox_2_valueChanged(int arg1)
{
    mStream.setMatrix_2Size(arg1);
}

void MainWindow::on_genRandomGraphBtn_clicked()
{
    randomMatrix(mStream);
}

void MainWindow::on_shuffleBtn_clicked()
{
    shuffleMatrix(mStream);
}

void MainWindow::on_automorphismBtn_clicked()
{
    ui->outputLabel->setText("Автоморфизмы:");
    mStream.setMatrix(ui->matrixEdit->toPlainText());

    Morphism morphism(mStream.matrixSize, mStream.matrixSize, mStream.matrix, mStream.matrix);
    morphism.getAutomorphism(ui->progressBar, mStream.resultText);
    ui->outputEdit->setPlainText(mStream.resultText);

    printPlot(morphism.getScore());
}

void MainWindow::on_isomorphismBtn_clicked()
{
    ui->outputLabel->setText("Изоморфизмы:");
    mStream.resultText.clear();
    ui->outputEdit->clear();

    //message.Simple(stroka);
    mStream.setMatrix(ui->matrixEdit->toPlainText());
    mStream.setMatrix(ui->matrix_2Edit->toPlainText());

    Morphism morphism(mStream.matrixSize, mStream.matrixSize, mStream.matrix, mStream.matrix);
    morphism.getAutomorphism(ui->progressBar, mStream.resultText);
    ui->outputEdit->setPlainText(mStream.resultText);

    printPlot(morphism.getScore());
}

void MainWindow::on_gomomorphismBtn_clicked()
{
    ui->outputLabel->setText("Гомоморфизмы:");
    mStream.resultText.clear();
    ui->outputEdit->clear();

    //message.Simple(stroka);
    mStream.setMatrix(ui->matrixEdit->toPlainText());
    mStream.setMatrix(ui->matrix_2Edit->toPlainText());

    Morphism morphism(mStream.matrixSize, mStream.matrixSize, mStream.matrix, mStream.matrix);
    morphism.getAutomorphism(ui->progressBar, mStream.resultText);
    ui->outputEdit->setPlainText(mStream.resultText);

    printPlot(morphism.getScore());
}



void MainWindow::on_matrixEdit_textChanged()
{
    ui->matrixEdit->toPlainText().isEmpty() ?
        ui->shuffleBtn->setDisabled(true):
        ui->shuffleBtn->setEnabled(true);
}

void MainWindow::on_matrix_2Edit_textChanged()
{

}

