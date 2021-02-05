#ifndef DIALOGINFO_H
#define DIALOGINFO_H

#include <QDialog>

namespace Ui {
class DialogInfo;
}

class DialogInfo : public QDialog
{
    Q_OBJECT

public:
    explicit DialogInfo(QWidget *parent = nullptr);
    ~DialogInfo();

    void setPID(QString value);
    void setPSex(QString value);
    void setPBirthday(QString value);
    void setPName(QString value);

    QString getPID();
    QString getPSex();
    QString getPBirthday();
    QString getPName();

signals:

    void pushButtonOK_clicked();

    void pushButtonCancel_clicked();

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::DialogInfo *ui;
};

#endif // DIALOGINFO_H
