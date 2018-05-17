#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{   
    ui->setupUi(this);
    ui->shuffleBtn->setDisabled(true);
    ui->shuffle_2Btn->setDisabled(true);
    ui->automorphismBtn->setDisabled(true);
    ui->isomorphismBtn->setDisabled(true);
    ui->gomomorphismBtn->setDisabled(true);
    ui->copyMatrixBtn->setDisabled(true);

    mStream.botRange = 0;
    mStream.topRange = 1;
    mStream.setMatrixSize(2);
    mStream.setMatrix_2Size(2);
}

MainWindow::~MainWindow()
{
    delete ui;
}


/*---------------------------------------------------*/
/*-----------------  ФУНКЦИИ  -----------------------*/
/*---------------------------------------------------*/
void MainWindow::printPlot(vector<long long> v) {
    vector<long long> score = v;

    int N = score.size(); //Вычисляем количество точек, которые будем отрисовывать
    QVector<double> x(N + 1), y(N + 1); //Массивы координат точек

    x[0] = y[0] = 0;
    for (int i=0; i < N; ++i)//Пробегаем по всем точкам
    {
        x[i + 1] = i + 1;
        y[i + 1] = score[i];
    }

    ui->widget->clearGraphs(); //Если нужно, то очищаем все графики
    ui->widget->addGraph(); //Добавляем один график в widget
    ui->widget->graph(0)->setData(x, y); //Говорим, что отрисовать нужно график по нашим двум массивам x и y
    ui->widget->xAxis->setLabel("N"); //Подписываем оси Ox и Oy
    ui->widget->yAxis->setLabel("Size |Mn|");

    //Установим область, которая будет показываться на графике
    if (N >= 30) {
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
            mStream.matrixText += QString().sprintf("%d", mStream.botRange + rand() % (mStream.topRange + 1)) += QString(" ");
        }
        mStream.matrixText.push_back('\n');
    }
    QString retstr = mStream.setMatrix(mStream.matrixText);
    if (retstr != "ok") {

    } else {
        ui->matrixEdit->setText(mStream.matrixText);
    }
}

void MainWindow::shuffleMatrix(MatrixStream &mStream) {
    mStream.matrixText.clear();
    int n = mStream.matrixSize;
    for (int i = 0; i < n - 1; ++i) {
        mStream.exchange(mStream.matrix, i, (rand() % (n - i)) + i);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            mStream.matrixText += QString().sprintf("%d", mStream.matrix[i][j]) += QString(" ");
        }
        mStream.matrixText.push_back('\n');
    }
    mStream.setMatrix(mStream.matrixText);
    ui->matrixEdit->setText(mStream.matrixText);
}

void MainWindow::shuffle_2Matrix(MatrixStream &mStream) {
    mStream.matrix_2Text.clear();
    int n = mStream.matrix_2Size;
    for (int i = 0; i < n - 1; ++i) {
        mStream.exchange(mStream.matrix_2, i, (rand() % (n - i)) + i);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            mStream.matrix_2Text += QString().sprintf("%d", mStream.matrix_2[i][j]) += QString(" ");
        }
        mStream.matrix_2Text.push_back('\n');
    }
    mStream.setMatrix(mStream.matrix_2Text);
    ui->matrix_2Edit->setText(mStream.matrix_2Text);
}
/*---------------------------------------------------*/
/*---------------------------------------------------*/
/*---------------------------------------------------*/












/*---------------------------------------------------*/
/*-------------   СЛОТЫ КНОПОК  ---------------------*/
/*---------------------------------------------------*/
void MainWindow::on_genRandomGraphBtn_clicked()
{
    randomMatrix(mStream);
}

void MainWindow::on_shuffleBtn_clicked()
{
    shuffleMatrix(mStream);
}

void MainWindow::on_shuffle_2Btn_clicked()
{
    shuffle_2Matrix(mStream);
}

void MainWindow::on_copyMatrixBtn_clicked()
{
    ui->matrix_2Edit->setText(ui->matrixEdit->toPlainText());
    mStream.setMatrix_2(ui->matrix_2Edit->toPlainText());
}

void MainWindow::on_automorphismBtn_clicked()
{
    ui->outputEdit->clear();
    ui->outputLabel->setText("Автоморфизмы:");
    mStream.resultText.clear();
    mStream.setMatrix(ui->matrixEdit->toPlainText());
    mStream.setMatrix_2(ui->matrixEdit->toPlainText());

    Morphism morphism(mStream.matrixSize, mStream.matrixSize, mStream.matrix, mStream.matrix);
    morphism.getAutomorphism(ui->progressBar, mStream.resultText);
    ui->outputEdit->setPlainText(mStream.resultText);

    printPlot(morphism.getScore());
}

void MainWindow::on_isomorphismBtn_clicked()
{
    ui->outputEdit->clear();
    ui->outputLabel->setText("Изоморфизмы:");
    mStream.resultText.clear();

    //message.Simple(stroka);
    mStream.setMatrix(ui->matrixEdit->toPlainText());
    mStream.setMatrix_2(ui->matrix_2Edit->toPlainText());

    if (mStream.matrixSize != mStream.matrix_2Size) {
        messageWarning(this, "Размеры матриц должны совпадать!");
    } else {
        Morphism morphism(mStream.matrixSize, mStream.matrix_2Size, mStream.matrix, mStream.matrix_2);
        morphism.getIsomorphism(ui->progressBar, mStream.resultText);
        ui->outputEdit->setPlainText(mStream.resultText);

        printPlot(morphism.getScore());
    }
}

void MainWindow::on_gomomorphismBtn_clicked()
{
    ui->outputEdit->clear();
    ui->outputLabel->setText("Гомоморфизмы:");
    mStream.resultText.clear();

    mStream.setMatrix(ui->matrixEdit->toPlainText());
    mStream.setMatrix_2(ui->matrix_2Edit->toPlainText());

    if (mStream.matrixSize < mStream.matrix_2Size) {
        messageWarning(this, "Размер первой матрицы должен быть не меньше размера второй!");
    } else {
        Morphism morphism(mStream.matrixSize, mStream.matrix_2Size, mStream.matrix, mStream.matrix_2);
        morphism.getGomomorphism(ui->progressBar, mStream.resultText);
        ui->outputEdit->setPlainText(mStream.resultText);

        printPlot(morphism.getScore());
    }
}
/*---------------------------------------------------*/
/*---------------------------------------------------*/
/*---------------------------------------------------*/









/*---------------------------------------------------*/
/*------------- ТРИГЕРЫ СПИН-БОКСОВ  ----------------*/
/*-----------------  И ТЕКСТОВ  ---------------------*/
/*---------------------------------------------------*/
void MainWindow::on_rangeSpinBox_valueChanged(int arg1)
{
    mStream.topRange = arg1;
}
void MainWindow::on_matrixSpinBox_valueChanged(int arg1)
{
    mStream.setMatrixSize(arg1);
}
void MainWindow::on_matrix_2SpinBox_valueChanged(int arg1)
{
    mStream.setMatrix_2Size(arg1);
}

/*---------------------------------------------------*/
void MainWindow::on_matrixEdit_textChanged()
{
    if (ui->matrixEdit->toPlainText().isEmpty()) {
        ui->shuffleBtn->setDisabled(true);
        ui->copyMatrixBtn->setDisabled(true);
        ui->automorphismBtn->setDisabled(true);
    } else {
        ui->shuffleBtn->setEnabled(true);
        ui->copyMatrixBtn->setEnabled(true);
        ui->automorphismBtn->setEnabled(true);
    }
    if (ui->matrix_2Edit->toPlainText().isEmpty() ||
        ui->matrixEdit->toPlainText().isEmpty()) {
        ui->isomorphismBtn->setDisabled(true);
        ui->gomomorphismBtn->setDisabled(true);
    } else {
        ui->isomorphismBtn->setEnabled(true);
        ui->gomomorphismBtn->setEnabled(true);
    }
}

void MainWindow::on_matrix_2Edit_textChanged()
{
    if (ui->matrix_2Edit->toPlainText().isEmpty()) {
        ui->shuffle_2Btn->setDisabled(true);
    } else {
        ui->shuffle_2Btn->setEnabled(true);
    }
    if (ui->matrix_2Edit->toPlainText().isEmpty() ||
        ui->matrixEdit->toPlainText().isEmpty()) {
        ui->isomorphismBtn->setDisabled(true);
        ui->gomomorphismBtn->setDisabled(true);
    } else {
        ui->isomorphismBtn->setEnabled(true);
        ui->gomomorphismBtn->setEnabled(true);
    }
}
/*---------------------------------------------------*/
/*---------------------------------------------------*/
/*---------------------------------------------------*/






/*---------------------------------------------------*/
/*------------ ИНФОРМАЦИОННЫЕ СООБЩЕНИЯ -------------*/
/*---------------------------------------------------*/
void MainWindow::messageError(QWidget *window, QString message)
{
    QMessageBox::critical(window, tr("Ошибка"), message);
}
// Сообщение предупреждение
void MainWindow::messageWarning(QWidget *window, QString message)
{
    QMessageBox::warning(window, tr("Предупреждение"), message);
}
// Сообщение об успехе
void MainWindow::messageSuccess(QWidget *window, QString message)
{
    QMessageBox::information(window, tr("Успешно"), message);
}
/*---------------------------------------------------*/
/*---------------------------------------------------*/
/*---------------------------------------------------*/
