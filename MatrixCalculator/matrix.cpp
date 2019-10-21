#include <string>
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

void Matrix::fill(int numligne, int numcolonne, double coefficients)
{
    this->coefficients[numligne][numcolonne] = coefficients;
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
            newMatrix->fill(i,j,((this->coefficients[i][j]) + (source->getCoef(i,j))));
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



    return newMatrix;
}

Matrix* Matrix::mplicationReel(double reel)
{
    Matrix *newMatrice = new Matrix(this->getLine(),this->getColumn());

    for(int i=0; i<this->getLine(); i++)
    {
        for(int j=0; j<this->getColumn(); j++)
        {
            newMatrice->fill(i,j,(reel*this->coefficients[i][j]));
        }
    }

    return newMatrice;
}

double Matrix::determinant()
{

    if(this->getLine() != this->getColumn())
        return 0;

    if(this->getLine() == 1)
        return coefficients[0][0];

    if(this->getLine() == 2)
        return determinant2x2();

    if(this->getLine() == 3)
        return determinant3x3();

    double determinant = 0;

//если больше 3?

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
                algAdd->fill(i,j,determinant());
            if(((i+j)%2)==1)
                algAdd->fill(i,j,-determinant());
        }
    }

    return algAdd;
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

    return newMatrix;
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
