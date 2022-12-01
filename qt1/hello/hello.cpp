#include<QApplication>
#include<QLabel>

int main(int argc,char** argv)
{
    //创建QT应用程序对象
    QApplication app(argc,argv);
    //创建标签控件
    QLabel label("hello QT!");

    //显示标签控件
    label.show();
    //让应用程序进入事件循环
    return app.exec();
}
