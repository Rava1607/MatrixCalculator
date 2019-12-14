#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
    public:
        Matrix();
        Matrix(int,int);
        Matrix(Matrix &copie);

        void removeLine();
        void removeColumn();
        void addLine();
        void addColumn();

        void fill(int numline, int numcolumn, double coefficients);
        Matrix *sum(Matrix *source);
        Matrix* mplication(Matrix *source);
        Matrix* mplicationReel(double reel);
        double determinant();
        double determinant2x2();
        double determinant3x3();
        Matrix matWithoutLinCol(int line,int column);
        Matrix* algAdd();
        Matrix* reverse();
        Matrix* transpose();
        void round();

        int getLine();
        void setLine(int line);
        int getColumn();
        void setColumn(int column);
        double getMultiple();
        void setMultiple(double multiple);
        QVector<QVector<double> > getcoef();
        double getCoef(int line, int column);
        void setCoefficients(QVector<QVector<double> > coefficients);


    private:
        int line;
        int column;
        int multiple;
        QVector<QVector<double> > coefficients;

};

#endif // MATRICE_H
