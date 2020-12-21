#include "patient.h"
#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTime>
#include <QSqlError>
#include <QtDebug>
#include <QSqlDriver>
#include <QSqlRecord>


bool Patient::connect()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "connection1");
    db.setDatabaseName("Patient.db");
    if( !db.open())
    {
        qDebug() << "无法建立数据库连接";
        return false;
    }
    return true;
}

bool Patient::disConnect()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "connection1");
    db.setDatabaseName("Patient.db");
    db.close();

    return true;

}


//sqlite> CREATE TABLE COMPANY(
//   ID INT PRIMARY KEY     NOT NULL,
//   NAME           TEXT    NOT NULL,
//   AGE            INT     NOT NULL,
//   ADDRESS        CHAR(50),
//   SALARY         REAL
//);

//创建数据库表
bool Patient::createTable()
{
    QSqlDatabase db = QSqlDatabase::database("connection1"); //建立数据库连接
    QSqlQuery query(db);
    bool success = query.exec("CREATE TABLE students ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                              "name VARCHAR(40) NOT NULL, "
                              "sex VARCHAR(40) NOT NULL, "
                              "age INTEGER NULL)");

    if(success)
    {
        qDebug() << QObject::tr("数据库表创建成功！\n");
        return true;
    }
    else
    {
        qDebug() << QObject::tr("数据库表创建失败！\n");
        return false;
    }
}

//向数据库中插入记录
bool Patient::insert()
{
    QSqlDatabase db = QSqlDatabase::database("connection1"); //建立数据库连接
    QSqlQuery query(db);
    query.prepare("INSERT INTO students (name, sex,age) "
                  "VALUES (:name, :sex, :age)");

    long records = 10;
    for(int i=0; i<records; i++)
    {
        query.bindValue(":name", "zheng");
        query.bindValue(":sex", "男");
        query.bindValue(":age", 31 );


        bool success=query.exec();
        if(!success)
        {
            QSqlError lastError = query.lastError();
            qDebug() << lastError.driverText() << QString(QObject::tr("插入失败"));
            return false;
        }
    }
    return true;
}

//查询所有信息
bool Patient::queryAll()
{
    QSqlDatabase db = QSqlDatabase::database("connection1"); //建立数据库连接
    QSqlQuery query(db);
    query.exec("SELECT * FROM students WHERE age >= 20 AND age <= 80;");
    while(query.next())
    {
        QString id = query.value(0).toString();
        QString name = query.value(2).toString();
        QString sex = query.value(1).toString();
        QString age = query.value(2).toString();


        qDebug()<<name<<id<<sex<<age;
    }
    return true;
}

//根据ID删除记录
bool Patient::deleteById(int id)
{
    QSqlDatabase db = QSqlDatabase::database("connection1"); //建立数据库连接
    QSqlQuery query(db);
    query.prepare(QString("delete from automobil where id = %1").arg(id));
    if(!query.exec())
    {
        qDebug() << "删除记录失败！";
        return false;
    }
    return true;
}

//根据ID更新记录
bool Patient::updateById(int id)
{
    QSqlDatabase db = QSqlDatabase::database("connection1"); //建立数据库连接
    QSqlQuery query(db);
    query.prepare(QString("update automobil set attribute=?,type=?,"
                             "kind=?, nation=?,"
                             "carnumber=?, elevaltor=?,"
                             "distance=?, oil=?,"
                             "temperature=? where id=%1").arg(id));

     query.bindValue(0,"四轮");
     query.bindValue(1,"轿车");
     query.bindValue(2,"富康");
     query.bindValue(3,rand()%100);
     query.bindValue(4,rand()%10000);
     query.bindValue(5,rand()%300);
     query.bindValue(6,rand()%200000);
     query.bindValue(7,rand()%52);
     query.bindValue(8,rand()%100);

     bool success=query.exec();
     if(!success)
     {
          QSqlError lastError = query.lastError();
          qDebug() << lastError.driverText() << QString(QObject::tr("更新失败"));
     }
    return true;
}

//排序
bool Patient::sortById()
{
    QSqlDatabase db = QSqlDatabase::database("connection1"); //建立数据库连接
    QSqlQuery query(db);
    bool success=query.exec("select * from automobil order by id desc");
    if(success)
    {
        qDebug() << QObject::tr("排序成功");
        return true;
    }
    else
    {
        qDebug() << QObject::tr("排序失败！");
        return false;
    }
}
