#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    float numbT[] = {1,0,0,0,
                   0,1,0,0,
                   0,0,1,0,
                   -x0,-y0,-z0,1};
    float numbS[] = {-1,0,0,0,
                    0,1,0,0,
                    0,0,1,0,
                    0,0,0,1};
    float numbRx90[] = {1,0,0,0,
                      0,0,-1,0,
                      0,1,0,0,
                      0,0,0,1};
    float d = sqrt(x0*x0+y0*y0);
    float numbRy[] = {y0/d,0,x0/d,0,
                       0,1,0,0,
                     -x0/d,0,y0/d,0,
                       0,0,0,1};
    float s = sqrt(x0*x0+y0*y0+z0*z0);
    float numbRxw[] = {1,0,0,0,
                       0,d/s,-z0/s,0,
                       0,z0/s,d/s,0,
                       0,0,0,1};
    T = Matrix(4,4,numbT);
    S = Matrix(4,4,numbS);
    Rx90= Matrix(4,4,numbRx90);
    Ry = Matrix(4,4,numbRy);
    Rxw = Matrix(4,4,numbRxw);

}

void Widget::SKM_to_SKN()
{
  Matrix temp(T);

  temp *= S;
  temp *= Rx90;
  temp *= Ry;
  temp *= Rxw;
  V = temp;
  for(int i=0;i<8;i++)
  {
    float temp[] = {Ver[i][0],Ver[i][1],Ver[i][2],1};
    Matrix tmp(1,4,temp);
    tmp*=V;
    float** new_ver = tmp.GetNumbers();
    Ver[i][0] = new_ver[0][0];
    Ver[i][1] = new_ver[0][1];
    Ver[i][2] = new_ver[0][2];
  }
}

void Widget::SKN_to_SKK()
{
    for(int i=0;i<8;i++)
    {
        VerKa[i][0] = Ver[i][0];
        VerKa[i][1] = Ver[i][1];
    }
}

Widget::~Widget()
{
    delete ui;
}

