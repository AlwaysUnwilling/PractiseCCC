#include"cal1.h"
#include<QString>

CalculatorDialog::CalculatorDialog(void)
{
    //界面初始化
    setWindowTitle("计算器"); //继承于QDialog的函数
    
    //左操作数
    m_edit_x=new QLineEdit(this);
    m_edit_x->setAlignment(Qt::AlignRight); //设置文本对齐方式为右对齐，默认左对齐
    //设置数字验证器，只能输入数字形式内容
    m_edit_x->setValidator(new QDoubleValidator(this));
    //右操作数
    m_edit_y=new QLineEdit(this);
    m_edit_y->setAlignment(Qt::AlignRight); //设置文本对齐方式为右对齐，默认左对齐
    //设置数字验证器，只能输入数字形式内容
    m_edit_y->setValidator(new QDoubleValidator(this));

    //显示结果
    m_edit_z=new QLineEdit(this);
    m_edit_z->setAlignment(Qt::AlignRight);
    m_edit_z->setReadOnly(true);  //设置显示控件为只读

    //"+"
    m_label=new QLabel("+",this);
    //"="
    m_button=new QPushButton("=",this);
    m_button->setEnabled(false);  //设置使能状态(可用或不可用)

    //创建布局器：自动调整每个控件的大小和位置
    QHBoxLayout* layout=new QHBoxLayout(this);
    layout->addWidget(m_edit_x);
    layout->addWidget(m_label);
    layout->addWidget(m_edit_y);
    layout->addWidget(m_button);
    layout->addWidget(m_edit_z);
    //设置布局器
    setLayout(layout);

    //信号和槽函数连接
    //左右操作数文本改变时，发送信号textChanged(QString qString)
    QObject::connect(m_edit_x,SIGNAL(textChanged(QString)),this,SLOT(enableButton(void)));
    QObject::connect(m_edit_y,SIGNAL(textChanged(QString)),this,SLOT(enableButton(void)));

    //点击按钮，发送信号clicked
    QObject::connect(m_button,SIGNAL(clicked(void)),this,SLOT(calClicked(void)));
}

void CalculatorDialog::enableButton(void)
{
    bool bXok,bYok;
    //.text()函数获取输入文本(QString类型)
    //.toDouble(bool)函数QString转换为double，参数保存转换是否成果的结果
    m_edit_x->text().toDouble(&bXok);
    m_edit_y->text().toDouble(&bYok);
    //当左右操作数都输入了有效数据，则使能等号可用，否则不可用
    m_button->setEnabled(bXok && bYok);
}

void CalculatorDialog::calClicked(void)
{
    double res=m_edit_x->text().toDouble()+m_edit_y->text().toDouble();
    //将数字转换为QString类型
    QString str=QString::number(res);
    m_edit_z->setText(str);
}