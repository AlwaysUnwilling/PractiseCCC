#ifndef __CAL1_H__
#define __CAL1_H__

#include"ui_CalculatorDialog.h"
#include<QApplication>
#include<QPushButton>
#include<QLabel>
#include<QDialog>
#include<QLineEdit>  //行编辑控件
#include<QHBoxLayout>  //水平布局器
#include<QDoubleValidator> //验证器

//1继承> 注意继承顺序！先继承QDialog，后继承UI类，否则在初始化时可能出现问题

//class CalculatorDialog:public QDialog,public Ui::CalculatorDialog
class CalculatorDialog:public QDialog
{
    Q_OBJECT   //moc 源对象编辑器
public:
    CalculatorDialog();
public slots:
    //是能等号按钮的槽操作函数
    void enableButton(void);
    //计算结果和显示的槽函数
    void calClicked(void);
private:
  /*  QLineEdit* m_edit_x;   //做操作数
    QLineEdit* m_edit_y;   //右操作数
    QLineEdit* m_edit_z;    //计算结果
    
    QLabel* m_label;  //"+"
    QPushButton* m_button; //"="
    */
    Ui::CalculatorDialog* ui;
};




#endif  //END __CAL1_H__