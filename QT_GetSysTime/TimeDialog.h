#ifndef __TDIALOG_H__
#define __TDIALOG_H__

#include<QApplication>
#include<QPushButton>
#include<QLabel>
#include<QDialog>
#include<QVBoxLayout>    //垂直布局器
#include<QTime>              //时间头文件
#include<QDebug>              //用于打印调试的头文件
 
class TimeDialog:public QDialog
{
    Q_OBJECT
public:
    TimeDialog(void);
public slots:
    //获取系统时间的槽函数
    void getTime(void);

//自定义信号声明
signals:
    //自定义信号函数，只需要写声明，不用也不能写定义！！！
    void mySignals(const QString&);
private:
    QLabel* m_label;   //  显示时间的label
    QPushButton* m_button;  //获取时间的button
};


#endif   //END __TDIALOG_H__