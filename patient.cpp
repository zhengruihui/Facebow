#include "patient.h"
#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTime>
#include <QSqlError>
#include <QtDebug>
#include <QSqlDriver>
#include <QSqlRecord>


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
                                  "patientID VARCHAR(40) NOT NULL, "
                                  "name VARCHAR(40) NOT NULL, "
                                  "sex VARCHAR(40) NOT NULL, "
                                  "birthday VARCHAR(40) NOT NULL, "
                                  "diagnosis VARCHAR(40) NULL)");

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
bool Patient::insert(QString patientID, QString name, QString sex, QString birthday, QString diagnosis)
{
    QSqlDatabase db = QSqlDatabase::database("connection1"); //建立数据库连接
    QSqlQuery query(db);
    query.prepare("INSERT INTO patients (patientID, name, sex, birthday, diagnosis) "
                  "VALUES (:patientID, :name, :sex, :birthday, :diagnosis)");


    query.bindValue(":patientID", patientID);
    query.bindValue(":name", name);
    query.bindValue(":sex", sex);
    query.bindValue(":birthday", birthday);
    query.bindValue(":diagnosis", diagnosis );


    if(query.exec())
    {
        return true;
    }
    else{
        QSqlError lastError = query.lastError();
        qDebug() << lastError.driverText() << QString(QObject::tr("插入失败"));
        return false;
    }


}


bool Patient::searchByName(QString name)
{
    if(name==nullptr)
    {
        return false;
    }
    QSqlDatabase db = QSqlDatabase::database("connection1"); //建立数据库连接
    QSqlQuery query(db);

    QString command = "SELECT * FROM patients WHERE name Like ";
    command.append("'%" + name + "%'");
    query.exec(command);


    while(query.next())
    {

        emit searchChanged(query.value(0).toString(), query.value(1).toString(), query.value(2).toString(), query.value(3).toString(), query.value(4).toString(), query.value(5).toString());

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
bool Patient::updateById(QString id, QString patientID, QString name, QString sex, QString birthday, QString diagnosis)
{
    QSqlDatabase db = QSqlDatabase::database("connection1"); //建立数据库连接
    QSqlQuery query(db);

    query.prepare("UPDATE patients SET patientID =:patientID  name =:name sex =:sex birthday =:birthday diagnosis =:diagnosis WHERE ID =:ID ");

    query.bindValue(":patientID", patientID);
    query.bindValue(":name", name);
    query.bindValue(":sex", sex);
    query.bindValue(":birthday", birthday);
    query.bindValue(":diagnosis", diagnosis);
    query.bindValue(":ID", id);

    bool success = query.exec();











//    QString command = "UPDATE patients SET";

//    command.append(" patientID = '" + patientID);
//    command.append("' name = '" + name);
//    command.append("' sex = '" + sex);
//    command.append("' birthday = '" + birthday);
//    command.append("' diagnosis = '" + diagnosis);
//    command.append("' WHERE ID = " + id);

//    qDebug() << command;


//    bool success=query.exec(command);

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
