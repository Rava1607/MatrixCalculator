#include <QString>
#include <QVector>
#include <iostream>
#include <cmath>
#include <QDebug>
#include <QtGlobal>
#include "matrix.h"

Matrix::Matrix()
{

}

Matrix::Matrix(int line, int column)
{
    this->line = line;
    this->column = column;
    this->multiple = 1;

    for(int i=0; i<line; i++)
    {
        this->coefficients.append(QVector<double>());

        for(int j=0; j<column; j++)
            this->coefficients[i].append(0);
    }
}

Matrix::Matrix(Matrix &copie)
{
    this->line = copie.getLine();
    this->column = copie.getColumn();
    this->multiple = copie.getMultiple();

    for(int i=0; i<line; i++)
    {
        this->coefficients.append(QVector<double>());

        for(int j=0; j<column; j++)
            this->coefficients[i].append(0);
    }

    for(int i=0; i<this->getLine(); i++)
    {
        for(int j=0; j<this->getColumn(); j++)
        {
            this->fill(i,j,copie.getCoef(i,j));
        }
    }
}

void Matrix::removeLine()
{
    this->coefficients.removeLast();
    this->line--;
}

void Matrix::removeColumn()
{
    for(int i=0; i<this->coefficients.count(); ++i)
        this->coefficients[i].removeLast();

    this->column--;
}

void Matrix::addLine()
{
    this->coefficients.append(QVector<double>());

    for(int i=0; i<column; i++)
        this->coefficients[this->coefficients.size()-1].append(0);

    this->line++;
}

void Matrix::addColumn()
{
    for(int i=0; i<this->coefficients.count(); ++i)
        this->coefficients[i].append(0);

    this->column++;
}

void Matrix::fill(int numline, int numcolumn, double coefficients)
{
    this->coefficients[numline][numcolumn] = coefficients;
}

Matrix* Matrix::sum(Matrix *source)
{
    if(this->getLine() != source->getLine() || this->getColumn() != source->getColumn())
        return nullptr;

    Matrix *newMatrix = new Matrix(this->getLine(),this->getColumn());

    for(int i=0; i<this->getLine(); i++)
    {
        for(int j=0; j<this->getColumn(); j++)
        {
            newMatrix->fill(i,j,((this->coefficients[i][j]/this->getMultiple()) + (source->getCoef(i,j)/source->getMultiple())));
        }
    }

    return newMatrix;
}

Matrix* Matrix::mplication(Matrix *source)
{
    if(this->getColumn() != source->getLine())
        return nullptr;

    Matrix *newMatrix = new Matrix(this->getLine(),source->getColumn());

    for(int i=0; i<newMatrix->getLine(); i++)
    {
        for(int j=0; j<newMatrix->getColumn(); j++)
        {
            double coefTemp=0;

            for(int k=0; k<this->getColumn(); k++)
            {
                coefTemp += this->coefficients[i][k]*source->getCoef(k,j);
            }

            newMatrix->fill(i,j,coefTemp);
        }
    }

    newMatrix->setMultiple(this->getMultiple()*source->getMultiple());

    newMatrix->round();

    return newMatrix;
}

Matrix* Matrix::mplicationReel(double reel)
{
    Matrix *newMatrice = new Matrix(this->getLine(),this->getColumn());

    double reel2 = reel/this->getMultiple();

    for(int i=0; i<this->getLine(); i++)
    {
        for(int j=0; j<this->getColumn(); j++)
        {
            newMatrice->fill(i,j,(reel2*this->coefficients[i][j]));
        }
    }

    return newMatrice;
}

double Matrix::determinant()
{
    this->setMultiple(1);

    if(this->getLine() != this->getColumn())
        return 0;

    if(this->getLine() == 1)
        return coefficients[0][0]*multiple;

    if(this->getLine() == 2)
        return determinant2x2()*multiple;

    if(this->getLine() == 3)
        return determinant3x3()*multiple;

    double determinant = 0;

    for(int i=0; i<this->getColumn(); i++)
    {
        if(i%2==0){
            determinant += this->coefficients[0][i]*this->matWithoutLinCol(0,i).determinant();
        }
        else{
            determinant -= this->coefficients[0][i]*this->matWithoutLinCol(0,i).determinant();
        }
    }

    return determinant;
}

double Matrix::determinant2x2()
{
    if(this->getLine()!=2 || this->getColumn()!=2)
        return 0;

    return coefficients[0][0]*coefficients[1][1]-coefficients[0][1]*coefficients[1][0];
}

double Matrix::determinant3x3()
{
    if(this->getLine()!=3 || this->getColumn()!=3)
        return 0;

    double determinant = coefficients[0][0]*coefficients[1][1]*coefficients[2][2];
    determinant += coefficients[0][1]*coefficients[1][2]*coefficients[2][0];
    determinant += coefficients[0][2]*coefficients[1][0]*coefficients[2][1];
    determinant -= coefficients[2][0]*coefficients[1][1]*coefficients[0][2];
    determinant -= coefficients[1][0]*coefficients[0][1]*coefficients[2][2];
    determinant -= coefficients[0][0]*coefficients[2][1]*coefficients[1][2];

    return determinant;
}

Matrix Matrix::matWithoutLinCol(int line,int column)
{
    Matrix newMatrix(this->getLine()-1,this->getColumn()-1);

    int counterL = -1;
    int counterC = -1;

    for(int i=0; i<this->getLine(); i++)
    {
        if(i != line)
        {
            counterL++;

            for(int j=0; j<this->getColumn(); j++)
            {
                if(j != column)
                {
                    counterC++;
                    newMatrix.fill(counterL,counterC,this->coefficients[i][j]);
                }
            }

            counterC = -1;
        }
    }

    return newMatrix;
}

Matrix* Matrix::algAdd()
{
    if(this->getLine() != this->getColumn())
        return nullptr;

    Matrix *algAdd = new Matrix(this->getLine(), this->getColumn());

    for(int i=0; i<this->getLine(); i++)
    {
        for(int j=0; j<this->getColumn(); j++)
        {
            if(((i+j)%2)==0)
                algAdd->fill(i,j,(matWithoutLinCol(i,j).determinant()));
            if(((i+j)%2)==1)
                algAdd->fill(i,j,-(matWithoutLinCol(i,j).determinant()));
        }
    }

    return algAdd;
}

Matrix* Matrix::reverse()
{
    double determinant = this->determinant();

    if(determinant==0)
        return nullptr;

    Matrix *newMatrix = new Matrix(this->getLine(),this->getColumn());

    newMatrix = algAdd()->transpose()->mplicationReel((1.0/determinant));

    newMatrix = newMatrix->mplicationReel(this->getMultiple());

    return newMatrix;
}

Matrix* Matrix::transpose()
{
    Matrix *newMatrix = new Matrix(this->getLine(),this->getColumn());

    for(int i=0; i<this->getColumn(); i++)
    {
        for(int j=0; j<this->getLine(); j++)
        {
            newMatrix->fill(i,j,this->coefficients[j][i]);
        }
    }

    newMatrix->setMultiple(this->getMultiple());

    return newMatrix;
}

void Matrix::round()
{
    bool divparmultiple = true;

    for(int a=0; a<this->getLine(); a++)
    {
        for(int b=0; b<this->getColumn(); b++)
        {
            coefficients[a][b] = qRound(coefficients[a][b]);

            if(fmod(coefficients[a][b],multiple)!=0)
                divparmultiple = false;
        }
    }

    if(divparmultiple)
    {
        for(int a=0; a<line; a++)
        {
            for(int b=0; b<column; b++)
            {
                if(coefficients[a][b] != 0)
                coefficients[a][b] = coefficients[a][b]/multiple;
            }
        }

        multiple = 1;
    }
}

int Matrix::getLine()
{
    return line;
}

void Matrix::setLine(int line)
{
    this->line = line;
}

int Matrix::getColumn()
{
    return column;
}

void Matrix::setColumn(int column)
{
    this->column = column;
}

QVector<QVector<double> > Matrix::getcoef()
{
    return coefficients;
}

double Matrix::getCoef(int line, int column)
{
    return coefficients[line][column];
}

void Matrix::setCoefficients(QVector<QVector<double> > coefficients)
{
    this->coefficients = coefficients;
}
double Matrix::getMultiple()
{
    return multiple;
}

void Matrix::setMultiple(double multiple)
{
    this->multiple = multiple;
}


