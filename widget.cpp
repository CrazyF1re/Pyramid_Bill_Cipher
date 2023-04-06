#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(0,0,0,0);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    ui->graphicsView->setScene(scene);

    animationTimer = new QTimer(this);
    connect(animationTimer,SIGNAL(timeout()),this,SLOT(DrawLoop()));
    animationTimer->start(100);
    update_Matrices();



}
void Widget::update_Matrices()
{
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

    for(int i=0;i<9;i++)
    {
        for(int j=0;j<3;j++)
        {
            Changeble_Ver[i][j] = Ver[i][j];
        }
    }

}

void Widget::SKM_to_SKN()
{
  Matrix temp(T);

  temp *= S;
  temp *= Rx90;
  temp *= Ry;
  temp *= Rxw;
  V = temp;
  for(int i=0;i<9;i++)
  {
    float temp[] = {Changeble_Ver[i][0],Changeble_Ver[i][1],Changeble_Ver[i][2],1};
    Matrix tmp(1,4,temp);
    tmp*=V;
    float** new_ver = tmp.GetNumbers();
    Changeble_Ver[i][0] = new_ver[0][0];
    Changeble_Ver[i][1] = new_ver[0][1];
    Changeble_Ver[i][2] = new_ver[0][2];
  }
}

void Widget::SKN_to_SKK()
{
    float s = sqrt(x0*x0+y0*y0+z0*z0);
    for(int i=0;i<9;i++)
    {
        VerKa[i][0] = Changeble_Ver[i][0]/Changeble_Ver[i][2]*s;
        VerKa[i][1] = Changeble_Ver[i][1]/Changeble_Ver[i][2]*s;
    }
}

void Widget::SKK_to_SKEi()
{
    for(int i =0;i<9;i++)
    {
        VerEk[i][0] = VerKa[i][0]/P*xe+xc;
        VerEk[i][1] = VerKa[i][1]/P*ye+yc;
    }
}

void Widget::print_scene()
{
    for(int i =0;i<11;i++)
    {
        QLineF temp(QPointF(VerEk[Reb[i][0]-1][0],-VerEk[Reb[i][0]-1][1]),QPointF(VerEk[Reb[i][1]-1][0],-VerEk[Reb[i][1]-1][1]));
        scene->addLine(temp);
    }
}

void Widget::DrawLoop()
{
    print_Ver();
    scene->clear();
    if(flag && x0>20){
        x0--;
    }
    else if(flag && x0<=20)
    {
        x0++;
        flag=!flag;
    }
    else if (!flag && x0<100)
    {
        x0++;
    }
    else if(!flag && x0>=100)
    {
        x0--;
        flag = !flag;
    }
    update_Matrices();
    SKM_to_SKN();
    SKN_to_SKK();
    SKK_to_SKEi();
    print_scene();


}

Widget::~Widget()
{
    delete ui;
}

