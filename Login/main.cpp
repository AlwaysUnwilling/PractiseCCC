#include <QApplication>
#include"LoginDialog.h"

int main(int argc,char* argv[])
{
    QApplication app(argc,argv);

    LoginDialog ld;
    ld.show();
    
    return app.exec();
}