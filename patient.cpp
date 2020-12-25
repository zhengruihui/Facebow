#include "patient.h"
#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTime>
#include <QSqlError>
#include <QtDebug>
#include <QSqlDriver>
#include <QSqlRecord>
#include <QList>
#include <QDateTime>

Patient::Patient()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "connection1");
    db.setDatabaseName("Patient.db");
    if(db.open())
    {
        qDebug() << QObject::tr("数据库连接成功！\n");

        QSqlQuery query(db);
        bool success = query.exec("CREATE TABLE patients ("
                                  "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                  "pID VARCHAR(40) NOT NULL, "
                                  "pName VARCHAR(40) NOT NULL, "
                                  "pSex VARCHAR(40) NOT NULL, "
                                  "pBirthday VARCHAR(40) NOT NULL, "
                                  "pDiagnosis VARCHAR(40) NULL)");

        if(success)
        {
            qDebug() << QObject::tr("数据库表创建成功！\n");
        }
        else
        {
            qDebug() << QObject::tr("数据库表创建失败！\n");
        }

    }else{
        qDebug() << QObject::tr("数据库连接失败！\n");
    }

}

Patient::~Patient()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "connection1");
    db.setDatabaseName("Patient.db");
    db.close();
}

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



//向数据库中插入记录
QString Patient::insert(QString num, QString name, QString sex, QString birthday, QString diagnosis)
{
    QSqlDatabase db = QSqlDatabase::database("connection1"); //建立数据库连接
    QSqlQuery query(db);
    QString ID;
    query.prepare("INSERT INTO patients (pID, pName, pSex, pBirthday, pDiagnosis) "
                  "VALUES (:pID, :pName, :pSex, :pBirthday, :pDiagnosis)");


    query.bindValue(":pID", num);
    query.bindValue(":pName", name);
    query.bindValue(":pSex", sex);
    query.bindValue(":pBirthday", birthday);
    query.bindValue(":pDiagnosis", diagnosis );




    if(query.exec())
    {
        query.exec("select last_insert_rowid() patients");
        if(query.exec())
        {
            while(query.next())
            {
                ID = query.value(0).toString();
            }
            return ID;
        }

    }
    else{
        QSqlError lastError = query.lastError();
        qDebug() << lastError.driverText() << QString(QObject::tr("插入失败"));
        return "error";
    }
    return "error";

}


bool Patient::queryByName(QString name)
{
    QSqlDatabase db = QSqlDatabase::database("connection1"); //建立数据库连接
    QSqlQuery query(db);
    if(name.data())
    {
        QString command = "SELECT * FROM patients WHERE pName Like ";
        command.append("'%" + name + "%'");
        query.exec(command);


        while(query.next())
        {

            emit searchChanged(query.value(0).toString(), query.value(1).toString(), query.value(2).toString(), query.value(3).toString(), query.value(4).toString(), query.value(5).toString());

        }
        return true;
    }
    else
    {
        QString command = "SELECT * FROM patients ORDER BY ID DESC";
        query.exec(command);

        while(query.next())
        {

            emit searchChanged(query.value(0).toString(), query.value(1).toString(), query.value(2).toString(), query.value(3).toString(), query.value(4).toString(), query.value(5).toString());

        }
        return true;

    }
}

bool Patient::queryAll(QString name)
{
    QSqlDatabase db = QSqlDatabase::database("connection1"); //建立数据库连接
    QSqlQuery query(db);
    if(name.data())
    {
        QString command = "SELECT * FROM patients WHERE pName Like ";
        command.append("'%" + name + "%'");
        query.exec(command);


        while(query.next())
        {

            emit searchChanged(query.value(0).toString(), query.value(1).toString(), query.value(2).toString(), query.value(3).toString(), query.value(4).toString(), query.value(5).toString());

        }
        return true;
    }
    else
    {
        QString command = "SELECT * FROM patients";
        query.exec(command);

        while(query.next())
        {

            emit searchChanged(query.value(0).toString(), query.value(1).toString(), query.value(2).toString(), query.value(3).toString(), query.value(4).toString(), query.value(5).toString());

        }
        return true;

    }
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
bool Patient::updateById(QString id, QString num, QString name, QString sex, QString birthday, QString diagnosis)
{
    QSqlDatabase db = QSqlDatabase::database("connection1"); //建立数据库连接
    QSqlQuery query(db);

    QString command = QString("UPDATE patients SET pID= '%1' , pName = '%2' , pSex = '%3' , pBirthday = '%4' , pDiagnosis = '%5' WHERE ID = %6")
            .arg(num)
            .arg(name)
            .arg(sex)
            .arg(birthday)
            .arg(diagnosis)
            .arg(id);

    bool success = query.exec(command);


    if(!success)
    {
      QSqlError lastError = query.lastError();
      qDebug() << lastError.driverText() << QString(QObject::tr("更新失败"));
    }
    return true;
}

QString Patient::birthdayToAge(QString birthday)
{

    QDateTime startDateTime = QDateTime::fromString(birthday, "yyyy-MM-dd");

    QDateTime endDateTime = QDateTime::currentDateTime();

    int year = (endDateTime.toTime_t() - startDateTime.toTime_t()) / (365*24*60*60) + 1;

    return QString::number(year);
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
