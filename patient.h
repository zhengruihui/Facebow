#ifndef INFORMATION_H
#define INFORMATION_H

#include <QObject>
#include <QSqlDatabase>


class Patient : public QObject
{
    Q_OBJECT
public:
    Patient();
    ~Patient();
    Q_INVOKABLE QString insert(QString num, QString name, QString sex, QString birthday);

    Q_INVOKABLE bool insertPosition(QString userID, QString step, QString x, QString y, QString z, QString ex, QString ey, QString ez);

    Q_INVOKABLE bool queryByName(QString name);

    Q_INVOKABLE bool updateById(QString id, QString num, QString name, QString sex, QString birthday);

    Q_INVOKABLE bool updateDiagnosisById(QString id, QString diagnosis);

    Q_INVOKABLE QString birthdayToAge(QString birthday);

    bool deleteById(int id);  //删除

private:
    QSqlDatabase db;

signals:
    void searchChanged(QString id, QString num, QString name, QString sex, QString birthday, QString diagnosis);


};

#endif // INFORMATION_H
