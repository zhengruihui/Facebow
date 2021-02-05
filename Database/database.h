#ifndef INFORMATION_H
#define INFORMATION_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>

class Database : public QObject
{
    Q_OBJECT
public:
    Database();
    ~Database();
    bool insert(long timestamp, QString num, QString name, QString sex, QString birthday);

    bool insertPosition(int userID, int step, float x, float y, float z, float c, float p, float r);

    void queryAll();

    void queryByName(QString name);

    void queryPos(int userID, int step);

    bool updateById(QString id, long timestamp, QString num, QString name, QString sex, QString birthday);

    bool updateDiagnosisById(QString id, long timestamp, QString diagnosis);

    QString birthdayToAge(QString birthday);

    bool deleteById(int id);  //删除



private:
    QSqlDatabase dataBase;

signals:
    void queryChanged(QSqlQuery *value);

    void signalQueryByStep(int userID, int step);

    void queryByNameThread(QString name);
    void queryAllThread();

    void queryPosThread(int userID, int step);


    //对外信号
    void queryByNameChanged(QSqlQuery query);
    void queryAllChanged(QSqlQuery query);
    void queryPosChanged(int step, QSqlQuery query);

public slots:
    void queryByStep(int userID, int step);

    void on_queryByNameThread(QString name);

    void on_queryAllThread();

    void on_queryPosThread(int userID, int step);

};

#endif // INFORMATION_H
