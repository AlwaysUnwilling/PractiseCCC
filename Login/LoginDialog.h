#ifndef __LOGINDIALOG_H__
#define __LOGINDIALOG_H__

#include "ui_LoginDialog.h"
#include<QMessageBox>    //消息提示框
#include<QDebug>   //打印提示

class LoginDialog:public QDialog , public Ui::LoginDialog
{
Q_OBJECT
public:
    LoginDialog(void);
public slots:
    void onAccepted(void);//用于处理OK按钮的槽函数
    void onRejected(void); //处理cancel按钮的槽函数
private:
};




#endif //__LOGINDIALOG_H__