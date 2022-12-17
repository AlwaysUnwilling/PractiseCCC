#ifndef KEYDIALOG_H
#define KEYDIALOG_H

#include <QDialog>
#include <QKeyEvent>
#include <QDebug>


QT_BEGIN_NAMESPACE
namespace Ui { class KeyDialog; }
QT_END_NAMESPACE

class KeyDialog : public QDialog
{
    Q_OBJECT

public:
    KeyDialog(QWidget *parent = nullptr);
    ~KeyDialog();
    virtual void keyPressEvent(QKeyEvent* e);
    void translatePos(QPoint& pos);
private:
    Ui::KeyDialog *ui;
};
#endif // KEYDIALOG_H
