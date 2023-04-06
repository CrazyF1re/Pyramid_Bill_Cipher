#include "widget.h"

#include <QApplication>
#include "matrix.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    w.print_Ver();
    w.SKM_to_SKN();
        w.print_Ver();
    return a.exec();
}
