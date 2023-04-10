#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)//конструктор
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(0,0,0,0);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    ui->graphicsView->setScene(scene);//создание сцены

    animationTimer = new QTimer(this);//создание таймера
    connect(animationTimer,SIGNAL(timeout()),this,SLOT(DrawLoop()));//соединяем таймер с основным циклом
    animationTimer->start(1000/15);//запускаем таймер, аргумент - частота обновления
    float numbS[] = {-1,0,0,0,//матрицы
                    0,1,0,0,
                    0,0,1,0,
                    0,0,0,1};
    float numbRx90[] = {1,0,0,0,
                      0,0,-1,0,
                      0,1,0,0,
                      0,0,0,1};
    S = Matrix(4,4,numbS);
    Rx90= Matrix(4,4,numbRx90);



    isVisibleFace = new bool[gran_numb];//выделяем память под всякие массивы
    W = new float*[4];
    VerKa = new float*[ver_numb];
    VerEk = new float*[ver_numb];
    Ver = new float*[ver_numb];
    Changeble_Ver = new float*[ver_numb];
    Reb = new int*[reb_numb];
    Gran = new int*[gran_numb];

    float temp_ver[9][3] = {{0,0,0},{0,5,0},{5,0,0},{0,0,5},//тут первые 4 точки - x y z оси, остальные - точки фигуры
                            {10,-5,0},{-10,-5,0},{-10,5,0},
                            {10,5,0},{0,0,20}};

    int temp_reb[11][2] = {{1,2},{1,3},{1,4},{5,6},//тут первые три ребра - x y z оси, остальные - ребра фигуры
                           {6,7},{5,8},{8,7},{9,5},
                           {9,6},{9,7},{9,8}};

    int  temp_gran[5][6] = {{5,6,7,8,1,0},{5,6,9,5,0,0},//грани фигуры
                            {6,7,9,6,0,0},{7,8,9,7,0,0},
                            {5,8,9,5,0,0}
                           };


    for (int i =0; i<4;i++)//так же выделяем память под двумерные массивы
    {
        W[i] = new float[gran_numb];
    }

    for (int i=0;i<ver_numb;i++)
    {
        VerEk[i] = new float[2];
        VerKa[i] = new float[2];
        Ver[i] = new float[3];
        Changeble_Ver[i] = new float[3];
        for(int j=0;j<3;j++)
        {
            Ver[i][j] = temp_ver[i][j];
            Changeble_Ver[i][j]= temp_ver[i][j];
        }
    }

    for(int i =0;i<reb_numb;i++)
    {
        Reb[i] = new int[2];
        for(int j=0;j<2;j++)
        {
            Reb[i][j] = temp_reb[i][j];
        }
    }

    for(int i=0;i<gran_numb;i++)
    {
        Gran[i] = new  int[ver_numb-3];
        for (int j=0;j<ver_numb-3;j++)
        {
            Gran[i][j] = temp_gran[i][j];
        }
    }

    InitGravityCenter();//инициализируем центр тяжести
    Init_W_Matrix();//инициализируем матрицу тела
}
void Widget::update_Matrices()
{
    float numbT[] = {1,0,0,0,
                   0,1,0,0,
                   0,0,1,0,
                   -x0,-y0,-z0,1};

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
    for(int i =4;i<ver_numb;i++)
    {
        Xc+=Ver[i][0];
        Yc+=Ver[i][1];
        Zc+=Ver[i][2];
    }
    Xc/=ver_numb-4;
    Yc/=ver_numb-4;
    Zc/=ver_numb-4;
    GravityCenter[0] = Xc;
    GravityCenter[1] = Yc;
    GravityCenter[2] = Zc;
}

void Widget::Init_W_Matrix()
{
 for (int i=0;i<gran_numb;i++)
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
    for(int i=0;i<gran_numb;i++)
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
  V = temp;//перемножая все матрицы находим самую последнюю
  for(int i=0;i<ver_numb;i++)//находим новые вершины используя полученную матрицу V
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
    float s = sqrt(x0*x0+y0*y0+z0*z0);// формула для перспективной проекции
    for(int i=0;i<ver_numb;i++)
    {
        VerKa[i][0] = Changeble_Ver[i][0]/Changeble_Ver[i][2]*s;
        VerKa[i][1] = Changeble_Ver[i][1]/Changeble_Ver[i][2]*s;
    }
}

void Widget::SKK_to_SKEi()
{
    for(int i =0;i<ver_numb;i++)
    {
        VerEk[i][0] = VerKa[i][0]/P*xe+xc;
        VerEk[i][1] = VerKa[i][1]/P*ye+yc;
    }
}

void Widget::print_scene()
{
    scene->addLine(QLineF (QPointF(VerEk[0][0],-VerEk[0][1]),QPointF(VerEk[1][0],-VerEk[1][1])));//первые три линии - оси x y z
    scene->addLine(QLineF (QPointF(VerEk[0][0],-VerEk[0][1]),QPointF(VerEk[2][0],-VerEk[2][1])));//они отрисовываются всегда
    scene->addLine(QLineF (QPointF(VerEk[0][0],-VerEk[0][1]),QPointF(VerEk[3][0],-VerEk[3][1])));//чтобы понятно было как происходит движение
    for(int i =0;i<gran_numb;i++)
    {
        if (isVisibleFace[i])//если грань видима то отрисовываем ее
        {
            int j =0;
            while(j+1!=5 && Gran[i][j+1]!=0)//соединяем соседние точки граней
            {
                QLineF temp(QPointF(VerEk[Gran[i][j]-1][0],-VerEk[Gran[i][j]-1][1]),QPointF(VerEk[Gran[i][j+1]-1][0],-VerEk[Gran[i][j+1]-1][1]));
                scene->addLine(temp);
                j++;
            }
        }
    }
}

void Widget::DrawLoop()// основной цикл
{
    scene->clear();//очищаем сцену перед отрисовкой

    double new_x1 = x0*cos(angle)-y0*sin(angle);//поворот точки наблюдателя на угол
    double new_y1 = x0*sin(angle)+y0*cos(angle);
    x0 = new_x1;
    y0 = new_y1;

    update_Matrices();//обновление матриц
    SKM_to_SKN();//вычисление новых координат точек
    SKN_to_SKK();
    SKK_to_SKEi();
    print_scene();//вывод фигуры


}

Widget::~Widget()//деструктор
{
    delete ui;
    delete scene;
    delete animationTimer;
    delete isVisibleFace;
    delete Changeble_Ver;
    for (int i =0; i<4;i++)
    {
        delete W[i];
    }
    delete W;
    for (int i=0;i<ver_numb;i++)
    {
        delete VerEk[i];
        delete VerKa[i];
        delete Ver[i];
        delete Changeble_Ver[i];
    }
    delete VerEk;
    delete VerKa;
    delete Ver;
    delete Changeble_Ver;
    for(int i =0;i<reb_numb;i++)
    {
        delete Reb[i];
    }
    delete Reb;
}

