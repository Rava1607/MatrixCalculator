#ifndef SYSTEME_H
#define SYSTEME_H

#include "matrix.h"

class Systeme
{
    public:
        Systeme(int equation, int unknown);

        void resoudre();
        void setCoef(int a, int b, double coefficient);
        Matrix* getCoef();
        void setEgalites(int a, double coefficient);
        Matrix* getEgalites();
        double getMultiple();
        QVector<double> getSolution();

    private:
        Matrix *coefficients;
        Matrix *egalites;
        int nbrEquation;
        int nbrUnknown;
        QVector<double> solution;
        double multiple;
};

#endif // SYSTEME_H
