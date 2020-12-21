#ifndef INFORMATION_H
#define INFORMATION_H

#include <QObject>
#include <QSqlDatabase>


class Patient : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE bool connect();  //创建一个连接
    Q_INVOKABLE bool disConnect();  //取消一个连接
    Q_INVOKABLE bool createTable();       //创建数据库表
    Q_INVOKABLE bool insert();            //出入数据
    Q_INVOKABLE bool queryAll();          //查询所有信息
    Q_INVOKABLE bool updateById(int id);  //更新
    bool deleteById(int id);  //删除
    bool sortById();

private:

signals:

};

#endif // INFORMATION_H
