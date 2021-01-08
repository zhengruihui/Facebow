#ifndef PAGEINFO_H
#define PAGEINFO_H

#include <QWidget>

namespace Ui {
class PageInfo;
}

class PageInfo : public QWidget
{
    Q_OBJECT

public:
    explicit PageInfo(QWidget *parent = nullptr);
    ~PageInfo();

private:
    Ui::PageInfo *ui;
};

#endif // PAGEINFO_H
