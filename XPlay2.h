#ifndef XPLAY2_H
#define XPLAY2_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class XPlay2; }
QT_END_NAMESPACE

class XPlay2 : public QWidget
{
    Q_OBJECT

public:
    XPlay2(QWidget *parent = nullptr);
    ~XPlay2();

private:
    Ui::XPlay2 *ui;
};
#endif // XPLAY2_H
