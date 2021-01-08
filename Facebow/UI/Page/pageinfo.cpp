#include "pageinfo.h"
#include "ui_pageinfo.h"

PageInfo::PageInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageInfo)
{
    ui->setupUi(this);
}

PageInfo::~PageInfo()
{
    delete ui;
}
