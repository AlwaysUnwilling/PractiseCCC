#include "keydialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    KeyDialog w;
    w.show();
    return a.exec();
}
