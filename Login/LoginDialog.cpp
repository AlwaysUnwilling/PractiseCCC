#include"LoginDialog.h"

LoginDialog::LoginDialog()
{
    //界面初始化
    setupUi(this);

    //信号和槽的连接
    //对于按钮盒中点击OK按钮发送信号是accepted(void)
    connect(m_btnBox,SIGNAL(accepted(void)),this,SLOT(onAccepted(void)));
    //对于按钮盒中点击Cancel按钮发送信号是rejected(void)
    connect(m_btnBox,SIGNAL(rejected(void)),this,SLOT(onRejected(void)));
}

//处理OK按钮的槽函数
void LoginDialog::onAccepted()
{
    //tarena/123456:提示成功，否则失败
    if(m_usernameEdit->text()=="tarena"
        && m_passwordEdit->text()=="123456")
    {
        qDebug()<<"登录成功！";     //qDebug()会默认自动添加换行符
        close();   //关闭登录窗口
    }
    else
    {
        //创建消息提示框
        QMessageBox msgBox(QMessageBox::Critical,   //消息提示框上面的图标(这里是表示错误的图标)
            "Error",                   //消息提示框的标题
            "用户名或者密码错误",    //提示消息
            QMessageBox::Ok,      //按钮
            this);           //父窗口指针
        
        //显示消息提示框，并进入事件循环--阻塞！
        msgBox.exec();
    }
}

//处理取消按钮的槽函数
void LoginDialog::onRejected()
{
    QMessageBox msgBox(
            QMessageBox::Question,  //询问图标
            "登录",
             "是否确定取消登录？",
             QMessageBox::Yes|QMessageBox::No,
             this 
        );
     //显示消息提示框，并进入事件循环,点击Yes或者No的时候都会退出循环，但是返回结果不同，
     //如果点击yes则退出登录对话框，否则返回之前的登录界面    
    if(msgBox.exec()==QMessageBox::Yes)
    {
        close();
    }
}