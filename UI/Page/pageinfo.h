#ifndef PAGEINFO_H
#define PAGEINFO_H

#include <QWidget>
#include <QListWidgetItem>
#include "Dialog/dialoginfo.h"
#include <QSqlQuery>
namespace Ui {
class PageInfo;
}



class PageInfo : public QWidget
{
    Q_OBJECT

public:
    explicit PageInfo(QWidget *parent = nullptr);
    ~PageInfo();


private slots:
    void on_pushButtonAdd_clicked();

    void on_pushButtonEditInfo_clicked();

    void on_listWidget_itemPressed(QListWidgetItem *item);


    void on_lineEdit_textChanged(const QString &arg1);

    void updateListWidget(QSqlQuery query);

    void on_pushButtonSaveDiagnosis_clicked();

    void dialogPushButtonOK_clicked();

    void dialogPushButtonCancel_clicked();

private:
    Ui::PageInfo *ui;
    DialogInfo *dialogInfo;

    bool isAdd;
};

#endif // PAGEINFO_H
