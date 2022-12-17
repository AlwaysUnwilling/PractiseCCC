#ifndef MOUSEDIALOG_H
#define MOUSEDIALOG_H

#include <QDialog>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MouseDialog; }
QT_END_NAMESPACE

class MouseDialog : public QDialog
{
    Q_OBJECT

public:
    MouseDialog(QWidget *parent = nullptr);
    ~MouseDialog();
private:
    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
private:
    Ui::MouseDialog *ui;
    bool m_drag;   //标记是否可以拖拽  --要求只有当鼠标左键点击时才能拖拽
    QPoint m_pos;  //QRect(x,y,w,h) QPoint(x,y),QSize(w,h);
};
#endif // MOUSEDIALOG_H
