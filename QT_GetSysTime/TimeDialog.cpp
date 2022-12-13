#include"TimeDialog.h"
#include<QFont>

TimeDialog::TimeDialog(void)
{
    //初始化界面
    m_label=new QLabel(this);
    //设置label边框效果：QFrame::Panel面板效果|QFrame::Sunken凹陷效果
    m_label->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    //设置label文本对齐方式：水平/垂直居中
    m_label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    //设置文本字体大小
    QFont font;
    font.setPointSize(20);
    m_label->setFont(font);

    //获取系统时间的按钮
    m_button=new QPushButton("点击获取系统时间",this);
    m_button->setFont(font);
    //创建垂直布局器
    QVBoxLayout* layout=new QVBoxLayout(this);
    layout->addWidget(m_label);
    layout->addWidget(m_button);
    setLayout(layout);

    //信号和槽函数
    QObject::connect(m_button,SIGNAL(clicked(void)),this,SLOT(getTime()));

    //通过自定义信号，触发label的setText槽函数执行
    connect(this,SIGNAL(mySignals(const QString&)),m_label,SLOT(setText(QString)));
}

void TimeDialog::getTime(void)
{
    //打印信息
    qDebug("getTime_c");
    qDebug()<<"getTime_cpp";

    //获取当前系统时间
    QTime time=QTime::currentTime();
    //将时间对象转换成字符串
    QString str=time.toString("h:m:s ap");
    //显示当前时间
   // m_label->setText(str);

   //emit 是QT关键字！标记当前是发射信号操作！
   emit mySignals(str);  //发射信号！
}