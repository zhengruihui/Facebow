#ifndef PATIENTITEM_H
#define PATIENTITEM_H

#include <QWidget>
#include <QLabel>
namespace Ui {
class PatientItem;
}

class PatientItem : public QWidget
{
    Q_OBJECT

public:
    explicit PatientItem(QWidget *parent = nullptr);
    ~PatientItem();

    void setID(QString value);
    void setPID(QString value);
    void setPName(QString value);
    void setPSex(QString value);
    void setPBirthday(QString value);
    void setPDiagnosis(QString value);
    void setPTimestamp(long long value);

    QString getID();
    QString getPID();
    QString getPName();
    QString getPSex();
    QString getPBirthday();
    QString getPDiagnosis();
    long long getPTimestamp();




private:
    Ui::PatientItem *ui;

    QString ID;
    QString pID;
    QString pDiagnosis;
    long long timestamp;

};

#endif // PATIENTITEM_H
