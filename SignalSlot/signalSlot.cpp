#include<QApplication>
#include<QDialog>
#include<QSlider>
#include<QSpinBox>
#include<QLabel>
#include<QPushButton>


int main(int argc,char* argv[])
{
    QApplication app(argc,argv);

    QDialog parent;
    parent.resize(320,240);
    QSlider slider(Qt::Horizontal,&parent);
    slider.move(20,100);

    QSpinBox spinbox(&parent);
    spinbox.move(220,100);

    //滑块滑动让选值框数值随之改变
    slider.setRange(0,100);
    spinbox.setRange(0,100);
    QObject::connect(&slider,SIGNAL(valueChanged(int)),&spinbox,SLOT(setValue(int)));
   
    //选值框改变让滑块随之改变
    QObject::connect(&spinbox,SIGNAL(valueChanged(int)),&slider,SLOT(setValue(int)));
    parent.show();
    return app.exec();
}