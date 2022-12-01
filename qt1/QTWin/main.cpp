#include<QApplication>
#include<QLabel>
#include<QPushButton>
#include<QWidget>
#include<QDialog>
#include<QMainWindow>


int main(int argc,char** argv)
{
    QApplication app(argc,argv);
    //QWidget parent;
    QDialog parent;
   // QMainWindow parent;

   parent.move(50,50);
   parent.resize(320,240);

    //创建标签控件，停靠在父窗口上面
    QLabel label("我是标签",&parent);
    label.move(20,40);
    //创建按钮控件,停靠在父窗口上面
    QPushButton button("我是按钮",&parent);
    button.move(20,100);
    button.resize(80,80);
    //new对象如果指定了父窗口指针，可以不写delete，在父窗口对象销毁时，它会自动销毁；
    //当然如果有需求在某时需要手动销毁，也不会出现任何问题
    QPushButton* button2=new QPushButton("我也是按钮",&parent);
    button2->move(120,100);
    button2->resize(80,80);
    parent.show();
    return app.exec();
}