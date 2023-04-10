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
    int ver_numb = 9;
    int reb_numb = 11;
    int gran_numb = 5;

    double angle = -3.1415926535/54;

    float x0 = 50;
    float y0 = 0;
    float z0 = 50;

    int xc = 160;
    int yc = 80;
    int xe = 100;
    int ye = 100;

    bool flag = 1;
    Matrix T;
    Matrix S;
    Matrix Rx90;
    Matrix Ry;
    Matrix Rxw;
    Matrix V;
    float** Ver;
    float** Changeble_Ver;
    int** Reb;
    int  Gran[5][6] = {{5,6,7,8,1,0},
                       {5,6,9,5,0,0},
                       {6,7,9,6,0,0},
                       {7,8,9,7,0,0},
                       {5,8,9,5,0,0}
                        };

    float GravityCenter[3];
    float** W;
    float** VerKa;
    float** VerEk;
    int P = 5;
    bool* isVisibleFace;

    QTimer *animationTimer;

    void update_Matrices();
    void InitGravityCenter();
    void Init_W_Matrix();
    void updateVisibleFaces();
public:
    Widget(QWidget *parent = nullptr);
    void SKM_to_SKN();
    void SKN_to_SKK();
    void SKK_to_SKEi();
    void SKEi_to_SKEf();
    void print_Ver()
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
    void printMatrices()
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
    void print_scene();

    ~Widget();

private:
    Ui::Widget *ui;
    QGraphicsScene *scene;

public slots:
    void DrawLoop();
};
#endif // WIDGET_H
