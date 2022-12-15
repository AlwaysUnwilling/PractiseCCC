#ifndef SHOWIMAGEDIALOG_H
#define SHOWIMAGEDIALOG_H

#include <QDialog>
#include <QPainter>   //画家类
#include <QImage>     //图片类
#include <QDebug>
#include <iostream>
#include <map>

QT_BEGIN_NAMESPACE
namespace Ui { class ShowImageDialog; }
QT_END_NAMESPACE

class ShowImageDialog : public QDialog
{
    Q_OBJECT

public:
    ShowImageDialog(QWidget *parent = nullptr);
    ~ShowImageDialog();

private slots:
    void on_m_btnPrev_clicked();

    void on_m_btnNext_clicked();
private:
    //绘图是事件处理函数(虚函数)
    void paintEvent(QPaintEvent*);
private:
    Ui::ShowImageDialog *ui;
    int m_index; //图片
    int m_maxPic;  //图片的数量
    std::map<int,QString> index2pic;   //图片索引和图片名的映射
};
#endif // SHOWIMAGEDIALOG_H
