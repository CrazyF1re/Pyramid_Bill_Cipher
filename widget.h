#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include "matrix.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
    int ver_numb = 9;//количество вершин
    int reb_numb = 11;//количество ребер
    int gran_numb = 5;//количество граней

    double angle = -3.1415926535/54;//угол поворота

    float x0 = 50;//координаты наблюдателя
    float y0 = 0;
    float z0 = 50;

    int xc = 160;
    int yc = 80;
    int xe = 100;
    int ye = 100;

    Matrix T;//
    Matrix S;
    Matrix Rx90;
    Matrix Ry;
    Matrix Rxw;
    Matrix V;

    float** Ver;
    float** Changeble_Ver;
    int** Reb;
    int**  Gran;

    float GravityCenter[3];//центр тяжести
    float** W;//матрица тела
    float** VerKa;
    float** VerEk;
    int P = 5;//коэффициет
    bool* isVisibleFace;//матрица с видимыми гранями

    QTimer *animationTimer;//таймер

    void update_Matrices();//обновление матриц при каждом изменении координат наблюдателя
    void InitGravityCenter();//нахождение центра тяжести
    void Init_W_Matrix();//нахождение матрицы тела
    void updateVisibleFaces();//обновление видимых граней при каждом изменении координат наблюдателя
public:
    Widget(QWidget *parent = nullptr);
    void SKM_to_SKN();//очевидно
    void SKN_to_SKK();//очевидно + очевидно
    void SKK_to_SKEi();//суперочевидно
    void print_Ver()//вывод вершин
    {
        for(int i =0;i<ver_numb;i++)
        {
            for(int j =0;j<3;j++)
            {
                std::cout<<Ver[i][j]<<' ';
            }
            std::cout<<'\n';
        }
        std::cout<<"---------\n";
    }
    void printMatrices()//вывод матриц
    {
        std::cout<<"T\n";
        T.print();
        std::cout<<"S\n";
        S.print();
        std::cout<<"Rx90\n";
        Rx90.print();
        std::cout<<"Ry\n";
        Ry.print();
        std::cout<<"Rxw\n";
        Rxw.print();
    }
    void print_scene();//вывод всех нужных ребер

    ~Widget();//деструктор

private:
    Ui::Widget *ui;
    QGraphicsScene *scene;

public slots:
    void DrawLoop();//основной цикл
};
#endif // WIDGET_H
