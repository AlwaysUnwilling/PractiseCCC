#ifndef __CAL1_H__
#define __CAL1_H__

#include<QApplication>
#include<QPushButton>
#include<QLabel>
#include<QDialog>
#include<QLineEdit>  //行编辑控件
#include<QHBoxLayout>  //水平布局器
#include<QDoubleValidator> //验证器

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
    QLineEdit* m_edit_x;   //做操作数
    QLineEdit* m_edit_y;   //右操作数
    QLineEdit* m_edit_z;    //计算结果
    
    QLabel* m_label;  //"+"
    QPushButton* m_button; //"="
};




#endif  //END __CAL1_H__