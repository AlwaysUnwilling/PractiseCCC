#include "mousedialog.h"
#include "ui_mousedialog.h"

MouseDialog::MouseDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MouseDialog)
{
    ui->setupUi(this);
    m_drag=false;
}

MouseDialog::~MouseDialog()
{
    delete ui;
}

void MouseDialog::mousePressEvent(QMouseEvent* e)
{
    //是否鼠标左键
    if(e->button()==Qt::LeftButton)
    {
        //获取label所在的举行区域
        QRect rect=ui->label->frameRect();
        //转换坐标系
        rect.translate(ui->label->pos());

        //判断鼠标点击位置是否在rect矩形区域中
        if(rect.contains(e->pos()))
        {
            m_drag=true;
            //记录鼠标与label的相对位置，当拖拽后要保持相对位置不变
            m_pos=ui->label->pos()-e->pos();
        }
    }
}
void MouseDialog::mouseReleaseEvent(QMouseEvent* e)
{
    if(e->button()==Qt::LeftButton)
    {
        m_drag=false;
    }
}
void MouseDialog::mouseMoveEvent(QMouseEvent* e)
{
    if(m_drag)
    {
        //计算label要移动的新位置
        QPoint newPos=e->pos()+m_pos;
        //限制label移动的范围，否则会移动到父窗口外，之后无法再选中
        //获取副窗口大小
        QSize s1=size();
        //获取label大小
        QSize s2=ui->label->size();
        //x:0～窗口宽-label宽
        if(newPos.x()<0)
            newPos.setX(0);
        if(newPos.x()>s1.width()-s2.width())
        {
            newPos.setX(s1.width()-s2.width());
        }
        //y:0~窗口高-label高
        if(newPos.y()<0)
            newPos.setY(0);
        if(newPos.y()>s1.height()-s2.height())
        {
            newPos.setY(s1.height()-s2.height());
        }
        //移动label到新位置
        ui->label->move(newPos);
    }
}
