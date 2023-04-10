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
    animationTimer->start(1000/10);
    update_Matrices();
    InitGravityCenter();
    Init_W_Matrix();

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
    updateVisibleFaces();

}
void Widget::InitGravityCenter()
{
    float Xc=0;
    float Yc=0;
    float Zc=0;
    for(int i =4;i<9;i++)
    {
        Xc+=Ver[i][0];
        Yc+=Ver[i][1];
        Zc+=Ver[i][2];
    }
    Xc/=5;
    Yc/=5;
    Zc/=5;
    GravityCenter[0] = Xc;
    GravityCenter[1] = Yc;
    GravityCenter[2] = Zc;
}

void Widget::Init_W_Matrix()
{
 for (int i=0;i<5;i++)
 {
    float A = (Ver[Gran[i][2]-1][1]-Ver[Gran[i][0]-1][1])*(Ver[Gran[i][1]-1][2]-Ver[Gran[i][0]-1][2]) -
            (Ver[Gran[i][1]-1][1]-Ver[Gran[i][0]-1][1])*(Ver[Gran[i][2]-1][2]-Ver[Gran[i][0]-1][2]);
    float B = (Ver[Gran[i][1]-1][0]-Ver[Gran[i][0]-1][0])*(Ver[Gran[i][2]-1][2]-Ver[Gran[i][0]-1][2]) -
            (Ver[Gran[i][2]-1][0]-Ver[Gran[i][0]-1][0])*(Ver[Gran[i][1]-1][2]-Ver[Gran[i][0]-1][2]);
    float C = (Ver[Gran[i][2]-1][0]-Ver[Gran[i][0]-1][0])*(Ver[Gran[i][1]-1][1]-Ver[Gran[i][0]-1][1]) -
            (Ver[Gran[i][1]-1][0]-Ver[Gran[i][0]-1][0])*(Ver[Gran[i][2]-1][1]-Ver[Gran[i][0]-1][1]);
    float D = -(A*Ver[Gran[i][0]-1][0]+B*Ver[Gran[i][0]-1][1]+C*Ver[Gran[i][0]-1][2]);
    if (A*GravityCenter[0]+B*GravityCenter[1]+C*GravityCenter[2]+D<0)
    {
        A=-A;
        B=-B;
        C=-C;
        D=-D;
    }
    W[0][i] = A;
    W[1][i] = B;
    W[2][i] = C;
    W[3][i] = D;
 }
}

void Widget::updateVisibleFaces()
{
    for(int i=0;i<5;i++)
    {
        if(W[0][i]*x0+W[1][i]*y0+W[2][i]*z0+W[3][i]<0)
        {
            isVisibleFace[i] = true;
        }
        else
        {
            isVisibleFace[i] = false;
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
//    for(int i =0;i<11;i++)
//    {
//        QLineF temp(QPointF(VerEk[Reb[i][0]-1][0],-VerEk[Reb[i][0]-1][1]),QPointF(VerEk[Reb[i][1]-1][0],-VerEk[Reb[i][1]-1][1]));
//        scene->addLine(temp);
//    }
    scene->addLine(QLineF (QPointF(VerEk[0][0],-VerEk[0][1]),QPointF(VerEk[1][0],-VerEk[1][1])));
    scene->addLine(QLineF (QPointF(VerEk[0][0],-VerEk[0][1]),QPointF(VerEk[2][0],-VerEk[2][1])));
    scene->addLine(QLineF (QPointF(VerEk[0][0],-VerEk[0][1]),QPointF(VerEk[3][0],-VerEk[3][1])));
    for(int i =0;i<5;i++)
    {
        if (isVisibleFace[i])
        {
            int j =0;
            while(j+1!=5 && Gran[i][j+1]!=0)
            {
                QLineF temp(QPointF(VerEk[Gran[i][j]-1][0],-VerEk[Gran[i][j]-1][1]),QPointF(VerEk[Gran[i][j+1]-1][0],-VerEk[Gran[i][j+1]-1][1]));
                scene->addLine(temp);
                j++;
            }
        }
    }
}

void Widget::DrawLoop()
{
    scene->clear();
//    if(flag && x0>20){
//        x0--;
//    }
//    else if(flag && x0<=20)
//    {
//        x0++;
//        flag=!flag;
//    }
//    else if (!flag && x0<100)
//    {
//        x0++;
//    }
//    else if(!flag && x0>=100)
//    {
//        x0--;
//        flag = !flag;
//    }

    double new_x1 = x0*cos(angle)-y0*sin(angle);
    double new_y1 = x0*sin(angle)+y0*cos(angle);
    x0 = new_x1;
    y0 = new_y1;

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

