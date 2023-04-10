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
    float Ver[9][3] = {{0,0,0},{0,5,0},{5,0,0},{0,0,5},{10,-5,0},{-10,-5,0},{-10,5,0},{10,5,0},{0,0,20}};
    float Changeble_Ver[9][3] = {{0,0,0},{0,5,0},{5,0,0},{0,0,5},{10,-5,0},{-10,-5,0},{-10,5,0},{10,5,0},{0,0,20}};
    int Reb[11][2] = {{1,2},{1,3},{1,4},{5,6},{6,7},{5,8},{8,7},{9,5},{9,6},{9,7},{9,8}};
    float VerKa[9][2];
    float VerEk[9][2];
    int  Gran[5][6] = {{5,6,7,8,1,0},
                         {5,6,9,5,0,0},
                         {6,7,9,6,0,0},
                         {7,8,9,7,0,0},
                         {5,8,9,5,0,0}
                        };
    float GravityCenter[3];
    Matrix V;
    float W[4][5];
    int P = 5;
    bool isVisibleFace[5];
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
        for(int i =0;i<9;i++)
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
