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
    int x0 = 50;
    int y0 = 0;
    int z0 = 50;
    int xc = 160;
    int yc = 80;
    int xe = 800;
    int ye = 800;
    Matrix T;
    Matrix S;
    Matrix Rx90;
    Matrix Ry;
    Matrix Rxw;
    Matrix V;
    int P = 5;

    double angle = -3.1415926535/54;
    double rad = 0.5;
    float Xmin = -2;
    float Xmax = 2;
    float Zmin = -2;
    float Zmax = 2;
    float Dz = 0.2;
    float Dx = 0.001;
    float Ver[3];
    float VerEk[3];
    float VerKa[3];
    QTimer *animationTimer;

public:
    Widget(QWidget *parent = nullptr);
    void SKM_to_SKN();
    void SKN_to_SKK();
    void SKK_to_SKEi();
    void SKEi_to_SKEf();
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
