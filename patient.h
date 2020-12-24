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
    Q_INVOKABLE QString insert(QString num, QString name, QString sex, QString birthday, QString diagnosis);            //出入数据
    Q_INVOKABLE bool searchByName(QString name);          //查询患者信息（关键字为名字）
    Q_INVOKABLE bool updateById(QString id, QString num, QString name, QString sex, QString birthday, QString diagnosis);  //更新
    bool deleteById(int id);  //删除
    bool sortById();

private:

signals:
    void searchChanged(QString id, QString num, QString name, QString sex, QString birthday, QString diagnosis);


};

#endif // INFORMATION_H
