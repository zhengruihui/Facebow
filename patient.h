#ifndef INFORMATION_H
#define INFORMATION_H

#include <QObject>
#include <QSqlDatabase>


class Patient : public QObject
{
    Q_OBJECT
public:
    bool createConnection();  //创建一个连接
    bool createTable();       //创建数据库表
    bool insert();            //出入数据
    bool queryAll();          //查询所有信息
    bool updateById(int id);  //更新
    bool deleteById(int id);  //删除
    bool sortById();

private:

signals:

};

#endif // INFORMATION_H
