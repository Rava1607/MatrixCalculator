#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QLayout>
#include <QMap>
#include "matrix.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initialisation();
    void afficherMatrix(Matrix &matrix);
    void clearMatrix(QLayout *layout);
    int additionner();
    int mplication();
    int mplicationReel();
    int determinant();
    int algAdd();
    int reverse();
    int transpose();
    int systemeHomogene();

    void saveMatrixActive();
    void disabledGui();
    int saveData();
    int loadData();

private slots:
    void on_listWidget_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    int on_pushButton_4_clicked();
    int on_pushButton_5_clicked();
    void on_spinBox_2_valueChanged(int arg1);
    void on_spinBox_valueChanged(int arg1);
    void on_listWidget_2_doubleClicked();

private:
    Ui::MainWindow *ui;
    QMap<int,QMap<QString,Matrix*> > mapMatrix;
    QMap<QString,Matrix*> listMatrixSave;
    QString nameMatrixActive;
    int actionActive;
};

#endif // MAINWINDOW_H
