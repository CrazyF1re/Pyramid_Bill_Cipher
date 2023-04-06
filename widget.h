#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "matrix.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
    int x0 = 3;
    int y0 = 4;
    int z0 = 6;
    Matrix T;
    Matrix S;
    Matrix Rx90;
    Matrix Ry;
    Matrix Rxw;
    float Ver[8][3] = {{0,0,0},{4,0,0},{0,4,0},{0,0,4},{2,0,1},{-2,0,1},{2,1,0},{-2,1,0}};
    float Reb[5][2] = {{1,2},{1,3},{1,4},{5,6},{7,8}};
    float VerKa[8][2];
    Matrix V;

public:
    Widget(QWidget *parent = nullptr);
    void SKM_to_SKN();
    void SKN_to_SKK();
    void SKK_to_SKEi();
    void SKEi_to_SKEf();
    void print_Ver()
    {
        for(int i =0;i<8;i++)
        {
            for(int j =0;j<3;j++)
            {
                std::cout<<Ver[i][j]<<' ';
            }
            std::cout<<'\n';
        }
        std::cout<<"---------\n";
    }

    ~Widget();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
