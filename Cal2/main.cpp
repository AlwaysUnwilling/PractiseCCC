#include"cal1.h"


int main(int argc,char* argv[])
{
    QApplication app(argc,argv);

    CalculatorDialog cal;
    cal.show();

    return app.exec();
}