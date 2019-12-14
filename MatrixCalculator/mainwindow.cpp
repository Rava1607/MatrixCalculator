#include <QVector>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QListWidget>
#include <QList>
#include <QTextStream>
#include "systeme.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->menuBar->hide();
    ui->mainToolBar->hide();
    ui->statusBar->hide();
    ui->listWidget->setFixedWidth(150);
    ui->spinBox->setFixedWidth(40);
    ui->spinBox_2->setFixedWidth(40);

    ui->listWidget->addItem("1. Сумма");
    ui->listWidget->addItem("2. Произведение");
    ui->listWidget->addItem("3. Произведение на число");
    ui->listWidget->addItem("4. Детерминант");
    ui->listWidget->addItem("5. Алгебраические дополнения");
    ui->listWidget->addItem("6. Обратная матрица");
    ui->listWidget->addItem("7. Транспонированная матрица");
    ui->listWidget->addItem("8. Система уравнений");
    ui->listWidget->setCurrentRow(0);
    ui->listWidget->item(0)->setSelected(true);

    actionActive = ui->listWidget->currentRow();
    nameMatrixActive = "Matrix1";

    initialisation();
    afficherMatrix(*mapMatrix[actionActive].value(nameMatrixActive));

    loadData();
}

MainWindow::~MainWindow()
{
    saveData();

    for(QMap<QString,Matrix*> item : mapMatrix.values())
        for(Matrix *matrix : item.values())
            delete matrix;

    for(Matrix *matrix : listMatrixSave.values())
            delete matrix;

    clearMatrix(ui->gridLayout_4);

    delete ui;
}

void MainWindow::initialisation()
{
    // sum
    mapMatrix[0].insert("Matrix1",new Matrix(3,3));
    mapMatrix[0].insert("Matrix2",new Matrix(3,3));
    mapMatrix[0].insert("Matrix3",new Matrix(3,3));

    // Multiplication
    mapMatrix[1].insert("Matrix1",new Matrix(3,3));
    mapMatrix[1].insert("Matrix2",new Matrix(3,3));
    mapMatrix[1].insert("Matrix3",new Matrix(3,3));


    mapMatrix[2].insert("Matrix1",new Matrix(3,3));
    mapMatrix[2].insert("Matrix2",new Matrix(1,1));
    mapMatrix[2].insert("Matrix3",new Matrix(3,3));

    // Determinant
    mapMatrix[3].insert("Matrix1",new Matrix(3,3));
    mapMatrix[3].insert("Matrix3",new Matrix(1,1));

    // algAdd
    mapMatrix[4].insert("Matrix1",new Matrix(3,3));
    mapMatrix[4].insert("Matrix3",new Matrix(3,3));

    // reverse
    mapMatrix[5].insert("Matrix1",new Matrix(3,3));
    mapMatrix[5].insert("Matrix3",new Matrix(3,3));

    // Transpose
    mapMatrix[6].insert("Matrix1",new Matrix(3,3));
    mapMatrix[6].insert("Matrix3",new Matrix(3,3));

    // Systeme
    mapMatrix[7].insert("Matrix1",new Matrix(3,3));
    mapMatrix[7].insert("Matrix2",new Matrix(3,1));
    mapMatrix[7].insert("Matrix3",new Matrix(3,1));
}

void MainWindow::afficherMatrix(Matrix &matrix)
{
    ui->spinBox_2->setValue(matrix.getLine());
    ui->spinBox->setValue(matrix.getColumn());

    if(ui->gridLayout_4->count() != 0)
        clearMatrix(ui->gridLayout_4);

    for(int row=0; row<matrix.getLine(); ++row)
    {
        for(int column=0; column<matrix.getColumn(); ++column)
        {
            auto coef = new QLineEdit(this);
            coef->setFixedWidth(50);

            ui->gridLayout_4->addWidget(coef, row, column);
            coef->setText(QString::number(matrix.getCoef(row,column)));
        }
    }
}

void MainWindow::clearMatrix(QLayout *layout)
{
    if (!layout)
       return;

    while(auto item = layout->takeAt(0))
    {
        delete item->widget();
        clearMatrix(item->layout());
    }
}

int MainWindow::additionner()
{
    Matrix *matrix = mapMatrix[0].value("Matrix1")->sum(mapMatrix[0].value("Matrix2"));

    if(matrix == nullptr)
    {
        QMessageBox::critical(this, "Ошибка", "Матрицы не одинакового размера.");
        return 0;
    }

    nameMatrixActive = "Matrix3";
    mapMatrix[actionActive].insert(nameMatrixActive,matrix);

    return 1;
}

int MainWindow::mplication()
{
    Matrix *matrix = mapMatrix[1].value("Matrix1")->mplication(mapMatrix[1].value("Matrix2"));

    if(matrix == nullptr)
    {
        QMessageBox::critical(this, "Ошибка... ", "Матрицы несовместимы");
        return 0;
    }

    nameMatrixActive = "Matrix3";
    mapMatrix[actionActive].insert(nameMatrixActive,matrix);

    return 1;
}

int MainWindow::mplicationReel()
{
    Matrix *matrix = mapMatrix[2].value("Matrix1")->mplicationReel(mapMatrix[2].value("Matrix2")->getCoef(0,0));

    if(matrix == nullptr)
    {
        QMessageBox::critical(this, "Ошибка... ", "Невозможно выполнить операцию.");
        return 0;
    }

    nameMatrixActive = "Matrix3";
    mapMatrix[actionActive].insert(nameMatrixActive,matrix);

    return 1;
}

int MainWindow::determinant()
{
    Matrix *matrix = new Matrix(1,1);

    double determinant = mapMatrix[3].value("Matrix1")->determinant();

    matrix->fill(0,0,determinant);

    nameMatrixActive = "Matrix3";
    mapMatrix[actionActive].insert(nameMatrixActive,matrix);

    return 1;
}

int MainWindow::algAdd()
{
    Matrix *matrix = mapMatrix[4].value("Matrix1")->algAdd();

    if(matrix == nullptr)
    {
        QMessageBox::critical(this, "Ошибка... ", "Невозможно выполнить операцию.");
        return 0;
    }

    nameMatrixActive = "Matrix3";
    mapMatrix[actionActive].insert(nameMatrixActive,matrix);

    return 1;
}

int MainWindow::reverse()
{
    Matrix *matrix = mapMatrix[5].value("Matrix1")->reverse();

    if(matrix == nullptr)
    {
        QMessageBox::critical(this, "Ошибка... ", "Невозможно выполнить операцию.");
        return 0;
    }

    nameMatrixActive = "Matrix3";
    mapMatrix[actionActive].insert(nameMatrixActive,matrix);

    return 1;
}

int MainWindow::transpose()
{
    Matrix *matrix = mapMatrix[6].value("Matrix1")->transpose();

    if(matrix == nullptr)
    {
        QMessageBox::critical(this, "Ошибка... ", "Невозможно выполнить операцию.");
        return 0;
    }

    nameMatrixActive = "Matrix3";
    mapMatrix[actionActive].insert(nameMatrixActive,matrix);

    return 1;
}

int MainWindow::systemeHomogene()
{
    if(mapMatrix[7].value("Matrix1")->getLine() != mapMatrix[7].value("Matrix2")->getLine())
    {
        QMessageBox::critical(this, "Ошибка...", "Невозможно выполнить операцию.");
        return 0;
    }

    Matrix *matrix = nullptr;

    matrix = mapMatrix[7].value("Matrix1");

    Systeme *syst = new Systeme(matrix->getLine(), matrix->getColumn());

    for(int i=0; i<matrix->getLine(); i++)
        for(int j=0; j<matrix->getColumn(); j++)
            syst->setCoef(i,j,matrix->getCoef(i,j));

    matrix = mapMatrix[7].value("Matrix2");

    for(int i=0; i<matrix->getLine(); i++)
        syst->setEgalites(i,matrix->getCoef(i,0));

    QVector<double> solution = syst->getSolution();

    Matrix *newMatrix = new Matrix(matrix->getLine(),matrix->getColumn());

    for(int i=0; i<solution.count(); ++i)
        newMatrix->fill(i,0,solution[i]);

    nameMatrixActive = "Matrix3";
    mapMatrix[actionActive].insert(nameMatrixActive,newMatrix);

    return 1;
}

void MainWindow::on_listWidget_clicked()
{
    if(!ui->gridLayout_4->isEmpty())
        saveMatrixActive();

    actionActive = ui->listWidget->currentRow();
    nameMatrixActive = "Matrix1";

    afficherMatrix(*mapMatrix[actionActive].value("Matrix1"));

    disabledGui();
}

void MainWindow::on_listWidget_2_doubleClicked()
{

    Matrix *temp = mapMatrix[actionActive][nameMatrixActive];
    delete temp;

}

void MainWindow::on_pushButton_clicked()
{
    Matrix *matrix = mapMatrix[actionActive].value(nameMatrixActive);

    for(int row=0; row<matrix->getLine(); ++row)
    {
        for(int column=0; column<matrix->getColumn(); ++column)
        {
            QLineEdit *qle = qobject_cast<QLineEdit *>(ui->gridLayout_4->itemAtPosition(row,column)->widget());
            qle->setText("0");
        }
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if(!ui->gridLayout_4->isEmpty())
        saveMatrixActive();

    nameMatrixActive = "Matrix1";

    afficherMatrix(*mapMatrix[actionActive].value(nameMatrixActive));

    disabledGui();
}

void MainWindow::on_pushButton_3_clicked()
{
    if(!ui->gridLayout_4->isEmpty())
        saveMatrixActive();

    nameMatrixActive = "Matrix2";

    afficherMatrix(*mapMatrix[actionActive].value(nameMatrixActive));

    disabledGui();
}

int MainWindow::on_pushButton_4_clicked()
{
    if(!ui->gridLayout_4->isEmpty())
        saveMatrixActive();

    switch(actionActive)
    {
        case 0: if(!additionner()) return 1;
            break;
        case 1: if(!mplication()) return 1;
            break;
        case 2: if(!mplicationReel()) return 1;
            break;
        case 3: if(!determinant()) return 1;
            break;
        case 4: if(!algAdd()) return 1;
            break;
        case 5: if(!reverse()) return 1;
            break;
        case 6: if(!transpose()) return 1;
            break;
        case 7: if(!systemeHomogene()) return 1;
            break;
        default:
            break;
    }

    afficherMatrix(*mapMatrix[actionActive].value(nameMatrixActive));

    disabledGui();

    return 0;
}

int MainWindow::on_pushButton_5_clicked()
{
    //QString nameMatrix = ui->listWidget_2->findItems(ui->lineEdit->text(), Qt::MatchExactly);




    if(!ui->gridLayout_4->isEmpty())
        saveMatrixActive();

    Matrix *matrix = new Matrix(*mapMatrix[actionActive].value(nameMatrixActive));

    return 0;
}



void MainWindow::saveMatrixActive()
{
    Matrix *matrix = mapMatrix[actionActive].value(nameMatrixActive);

    for(int row=0; row<matrix->getLine(); ++row)
    {
        for(int column=0; column<matrix->getColumn(); ++column)
        {
            QLineEdit *qle = qobject_cast<QLineEdit *>(ui->gridLayout_4->itemAtPosition(row,column)->widget());
            matrix->fill(row,column,qle->text().toDouble());
        }
    }
}

void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
    Matrix *matrix = mapMatrix[actionActive].value(nameMatrixActive);

    if(matrix->getLine() != arg1)
    {
        if(!ui->gridLayout_4->isEmpty())
            saveMatrixActive();

        if(matrix->getLine() < arg1)
            matrix->addLine();
        else if(matrix->getLine() > arg1)
            matrix->removeLine();

        afficherMatrix(*matrix);
    }
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    Matrix *matrix = mapMatrix[actionActive].value(nameMatrixActive);

    if(matrix->getColumn() != arg1)
    {
        if(!ui->gridLayout_4->isEmpty())
            saveMatrixActive();

        if(matrix->getColumn() < arg1)
            matrix->addColumn();
        else if(matrix->getColumn() > arg1)
            matrix->removeColumn();

        afficherMatrix(*matrix);
    }
}

void MainWindow::disabledGui()
{
    ui->spinBox->setEnabled(true);
    ui->spinBox_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);

    if(nameMatrixActive == "Matrix3")
    {
        ui->spinBox->setEnabled(false);
        ui->spinBox_2->setEnabled(false);
    }

    if(actionActive == 2 && nameMatrixActive == "Matrix2")
    {
        ui->spinBox->setEnabled(false);
        ui->spinBox_2->setEnabled(false);
    }

    if(actionActive == 7 && nameMatrixActive == "Matrix2")
    {
        ui->spinBox->setEnabled(false);
    }

    if(actionActive == 3 || actionActive == 4 || actionActive == 5 || actionActive == 6)
    {
        ui->pushButton_3->setEnabled(false);
    }
}

int MainWindow::saveData()
{
    QFile saveMatrix("saveMatrix.save");

    if(saveMatrix.open(QIODevice::WriteOnly | QIODevice::Text) == false)
        return 1;

    QTextStream flux(&saveMatrix);
    flux << listMatrixSave.count() << endl;

    int pos = 0;

    for(Matrix *matrix : listMatrixSave.values())
    {
        flux << matrix->getLine() << endl;
        flux << matrix->getColumn() << endl;
        flux << matrix->getMultiple() << endl;

        for(QVector<double> item : matrix->getcoef())
        {
            for(double nbr : item)
            {
                flux << nbr << endl;
            }
        }

        pos++;
    }

    return 0;
}

int MainWindow::loadData()
{
    QFile saveMatrix("saveMatrix.save");

    if(saveMatrix.open(QIODevice::ReadOnly | QIODevice::Text) == false)
        return 1;

    QTextStream flux(&saveMatrix);
    int size;
    size = flux.readLine().toInt();

    QString nameMatrix;
    int line = 0;
    int column = 0;
    int multiple = 0;
    double coefTemp = 0;

    for(int i=0; i<size; i++)
    {
        nameMatrix = flux.readLine();
        line = flux.readLine().toInt();
        column = flux.readLine().toInt();
        multiple = flux.readLine().toInt();

        Matrix *matrix = new Matrix(line,column);
        matrix->setMultiple(multiple);


        for(int i=0; i<line; i++)
        {
            for(int j=0; j<column; j++)
            {
                coefTemp = flux.readLine().toDouble();
                matrix->fill(i,j,coefTemp);
            }
        }

        listMatrixSave.insert(nameMatrix,matrix);
    }

    return 0;
}
