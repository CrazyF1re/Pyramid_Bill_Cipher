#include "widget.h"

#include <QApplication>
#include "matrix.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.SKM_to_SKN();
    w.SKN_to_SKK();
    w.SKK_to_SKEi();
    w.show();
    return a.exec();
}
