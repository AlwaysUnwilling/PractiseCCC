#include<QApplication>
#include<QLabel>
#include<QPushButton>


int main(int argc,char** argv)
{
    QApplication app(argc,argv);
    QLabel label("我是标签");
    label.show();
    
    QPushButton qbutton("我是按钮");
    qbutton.show();
    return app.exec();
}