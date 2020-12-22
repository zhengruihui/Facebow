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

    Q_INVOKABLE bool connect();  //创建一个连接
    Q_INVOKABLE bool disConnect();  //取消一个连接
    Q_INVOKABLE bool insert(QString patientID, QString name, QString sex, QString birthday, QString age);            //出入数据
    Q_INVOKABLE bool searchByName(QString name);          //查询患者信息（关键字为名字）
    Q_INVOKABLE bool updateById(int id);  //更新
    bool deleteById(int id);  //删除
    bool sortById();

private:

signals:
    void searchChanged(QString patientID, QString name, QString sex, QString birthday, QString age);


};

#endif // INFORMATION_H
