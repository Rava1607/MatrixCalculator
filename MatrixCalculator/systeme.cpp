#include <QString>
#include <QVector>
#include <iostream>
#include "systeme.h"

using namespace std;

Systeme::Systeme(int equation, int unknown)
{
    this->nbrEquation = equation;
    this->nbrUnknown = unknown;

    this->coefficients = new Matrix(nbrEquation, nbrUnknown);
    this->egalites = new Matrix(nbrEquation, 1);

    this->multiple = 1;
}

void Systeme::resoudre()
{
    solution = QVector<double>(nbrUnknown);

    double detCoefficients = coefficients->determinant();
    bool needMultiple = false;

    for(int i=0; i<nbrEquation; i++)
    {
        Matrix *temp = new Matrix(*coefficients);
        QVector<double> temp2 = QVector<double>(nbrUnknown);

        for(int j=0; j<nbrEquation; j++)
        {
            temp2[j] = coefficients->getCoef(j,i);
            temp->fill(j,i,egalites->getCoef(j,0));
        }

        double determinant = temp->determinant();

        for(int j=0; j<nbrEquation; j++)
        {
            coefficients->fill(j,i,temp2[j]);
        }

        solution[i] = determinant/detCoefficients;

        if((int)solution[i] != solution[i])
        {
            needMultiple = true;
        }

        delete temp;
    }

    if(needMultiple)
    {
        for(int i=0; i<solution.length(); i++)
        {
            solution[i] = solution[i]*detCoefficients;
        }

        multiple = detCoefficients;
    }
}

void Systeme::setCoef(int a, int b, double coefficient)
{
    coefficients->fill(a,b,coefficient);
}

Matrix* Systeme::getCoef()
{
    return coefficients;
}

void Systeme::setEgalites(int a, double coefficient)
{
    egalites->fill(a,0,coefficient);
}

Matrix* Systeme::getEgalites()
{
    return egalites;
}

double Systeme::getMultiple()
{
    return multiple;
}

QVector<double> Systeme::getSolution()
{
    try
    {
        resoudre();
        return solution;
    }
    catch(string const& e)
    {
        throw string("Systeme impossible");
    }
}
