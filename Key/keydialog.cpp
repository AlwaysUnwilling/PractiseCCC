#include "keydialog.h"
#include "ui_keydialog.h"

KeyDialog::KeyDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::KeyDialog)
{
    ui->setupUi(this);
}

KeyDialog::~KeyDialog()
{
    delete ui;
}
void KeyDialog::translatePos(QPoint& pos)
{
    QSize s1=size();
    QSize s2=ui->label->size();

    if(pos.x()<0)
    {
        pos.setX(0);
    }
    if(pos.x()>s1.width()-s2.width())
    {
        pos.setX(s1.width()-s2.width());
    }
    if(pos.y()<0)
    {
        pos.setY(0);
    }
    if(pos.y()>s1.height()-s2.height())
    {
        pos.setY(s1.height()-s2.height());
    }
}

void KeyDialog::keyPressEvent(QKeyEvent* e)
{
    int x=ui->label->pos().x();
    int y=ui->label->pos().y();
    QPoint pos;
    switch(e->key())
    {
    case Qt::Key_Up:
        pos.setX(x);
        pos.setY(y-10);
        translatePos(pos);
        ui->label->move(pos);
        break;
    case Qt::Key_Down:
        pos.setX(x);
        pos.setY(y+10);
        translatePos(pos);
        ui->label->move(pos);
        break;
    case Qt::Key_Left:
        pos.setX(x-10);
        pos.setY(y);
        translatePos(pos);
        ui->label->move(pos);
        break;
    case Qt::Key_Right:
        pos.setX(x+10);
        pos.setY(y);
        translatePos(pos);
        ui->label->move(pos);
        break;
    default:
        qDebug()<<"不是方向键，无法移动label!";
        break;
    }
}
