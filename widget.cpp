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
    animationTimer->start(1000/3);

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

}


void Widget::SKM_to_SKN()
{
  Matrix temp(T);

  temp *= S;
  temp *= Rx90;
  temp *= Ry;
  temp *= Rxw;
  V = temp;
  float temp2[] = {Ver[0],Ver[1],Ver[2],1};
  Matrix tmp(1,4,temp2);
  tmp*=V;
  float** new_ver = tmp.GetNumbers();
  Ver[0] = new_ver[0][0];
  Ver[1] = new_ver[0][1];
  Ver[2] = new_ver[0][2];
}

void Widget::SKN_to_SKK()
{
    float s = sqrt(x0*x0+y0*y0+z0*z0);
    VerKa[0] = Ver[0]/Ver[2]*s;
    VerKa[1] = Ver[1]/Ver[2]*s;
}

void Widget::SKK_to_SKEi()
{
        VerEk[0] = VerKa[0]/P*xe+xc;
        VerEk[1] = VerKa[1]/P*ye+yc;
}

void Widget::print_scene()
{
    for(float z= Zmin; z<Zmax;z+=Dz)
    {
        for (float x = Xmin; x<Xmax;x+=Dx)
        {
            Ver[0] = x;
            Ver[1] = x*x+z*z;
            Ver[2] = z;


            SKM_to_SKN();
            SKN_to_SKK();
            SKK_to_SKEi();
            scene->addEllipse(VerEk[0]-rad, VerEk[1]-rad, rad*2.0, rad*2.0,
                        QPen(), QBrush(Qt::SolidPattern));

        }
    }
}

void Widget::DrawLoop()
{
    scene->clear();
    double new_x1 = x0*cos(angle)-z0*sin(angle);
    double new_z1 = x0*sin(angle)+z0*cos(angle);
    x0 = new_x1;
    z0 = new_z1;
    update_Matrices();
    print_scene();

}

Widget::~Widget()
{
    delete ui;
}

