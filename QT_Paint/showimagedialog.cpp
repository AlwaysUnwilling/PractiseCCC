#include "showimagedialog.h"
#include "ui_showimagedialog.h"

ShowImageDialog::ShowImageDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ShowImageDialog)
{
    ui->setupUi(this);
    m_maxPic=2;
    m_index=0;
    index2pic[0]="prettygirl";
    index2pic[1]="sexgirl";
    index2pic[2]="sex2girl";
}

ShowImageDialog::~ShowImageDialog()
{
    delete ui;
}

//“上一张”按钮相匹配的参汉书按钮
void ShowImageDialog::on_m_btnPrev_clicked()
{
    if(--m_index<0)
    {
        m_index=m_maxPic;
    }
    update();  //触发绘图事件
}

//“下一张”按钮相匹配的参汉书按钮
void ShowImageDialog::on_m_btnNext_clicked()
{
    if(++m_index>m_maxPic)
        m_index=0;
    update();

}

//绘图是事件处理函数(虚函数)
void ShowImageDialog::paintEvent(QPaintEvent*)
{
    qDebug("paintEvent");
    //1、创建画家对象
    QPainter painter(this);
    //2、获取绘图所在的矩形区域
    QRect rect=ui->frame->frameRect();
    //坐标值平移，画图类的绘画坐标系是窗口的客户去左上角,需要转换坐标
    qDebug()<<"平移前："<<rect;
    rect.translate(ui->frame->pos());
    qDebug()<<"平移后："<<rect;
    //3、构建要绘制图形对象
    QImage image(":/images/"+index2pic[m_index]+".jpg");
    //4、使用painter画家将image图片画到rect
    painter.drawImage(rect,image);
}

