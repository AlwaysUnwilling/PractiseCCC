#include"TimeDialog.h"


int main(int argc,char* argv[])
{
    QApplication app(argc,argv);

    TimeDialog td;
    td.show();

    return app.exec();
}