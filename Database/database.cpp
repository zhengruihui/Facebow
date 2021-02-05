#include "database.h"
#include <QTextCodec>
#include <QSqlDatabase>
#include <QTime>
#include <QSqlError>
#include <QtDebug>
#include <QSqlDriver>
#include <QSqlRecord>
#include <QList>
#include <QDateTime>
#include <QThread>

Database::Database()
{
    dataBase = QSqlDatabase::addDatabase("QSQLITE", "connection");
    dataBase.setDatabaseName("Patient.db");
    if(dataBase.open())
    {
        QSqlQuery query(dataBase);

        QString command = QString("CREATE TABLE PATIENTS ("
                                  "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                                  "TIMESTAMP INTEGER NOT NULL, "
                                  "PID VARCHAR(40) NOT NULL, "
                                  "PNAME VARCHAR(40) NOT NULL, "
                                  "PSEX VARCHAR(40) NOT NULL, "
                                  "PBIRTHDAY VARCHAR(40) NOT NULL, "
                                  "PDIAGNOSIS VARCHAR(40) NOT NULL)");



        if(query.exec(command))
        {
            //qDebug() << QObject::tr("数据库表创建成功！\n");
        }
        else
        {
            //qDebug() << QObject::tr("CREATE TABLE FALIED！\n");
        }

    }
    else
    {
        //qDebug() << QObject::tr("数据库连接失败！\n");
    }

    QObject::connect(this, &Database::queryByNameThread, this, &Database::on_queryByNameThread, Qt::QueuedConnection);

    QObject::connect(this, &Database::queryAllThread, this, &Database::on_queryAllThread, Qt::QueuedConnection);

    QObject::connect(this, &Database::queryPosThread, this, &Database::on_queryPosThread, Qt::QueuedConnection);
}

Database::~Database()
{
    dataBase.setDatabaseName("Patient.db");
    dataBase.close();
}


//向数据库中插入记录
bool Database::insert(long timestamp, QString num, QString name, QString sex, QString birthday)
{
    QSqlQuery query(dataBase);
    QString ID;

    QString command = QString("INSERT INTO PATIENTS (TIMESTAMP, PID, PNAME, PSEX, PBIRTHDAY, PDIAGNOSIS) "
                              "VALUES ('%1', '%2', '%3', '%4', '%5', '%6')")
                              .arg(timestamp)
                              .arg(num)
                              .arg(name)
                              .arg(sex)
                              .arg(birthday)
                              .arg("");



    if(query.exec(command))
    {
        query.exec("select last_insert_rowid() patients");
        if(query.exec())
        {
            while(query.next())
            {
                ID = query.value(0).toString();
            }

            for(int i=1; i<8; i++)
            {

                query.prepare(QString("CREATE TABLE STEP%1_%2 ("
                                      "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                                      "X REAL NOT NULL, "
                                      "Y REAL NOT NULL, "
                                      "Z REAL NOT NULL, "
                                      "C REAL NOT NULL, "
                                      "P REAL NOT NULL, "
                                      "R REAL NOT NULL)").arg(ID).arg(i));
                if(query.exec())
                {
                    //qDebug() << "创建位置表成功";
                }
                else
                {
                    qDebug() << "创建位置表失败";
                }

            }




            return true;
        }

    }
    else{
        QSqlError lastError = query.lastError();
        qDebug() << lastError.driverText() << QString(QObject::tr("插入失败"));
        return false;
    }
    return false;

}


bool Database::insertPosition(int userID, int step, float x, float y, float z, float c, float p, float r)
{
    QSqlQuery query(dataBase);

    QString command = QString("INSERT INTO STEP%1_%2 (X, Y, Z, C, P, R) "
                              "VALUES ('%3', '%4', '%5', '%6', '%7', '%8')")
                              .arg(userID)
                              .arg(step)
                              .arg(x)
                              .arg(y)
                              .arg(z)
                              .arg(c)
                              .arg(p)
                              .arg(r);

    //qDebug() << command;

    if(query.exec(command))
    {
        return true;
    }
    else
    {
        return false;
    }

}

void Database::queryAll()
{


}


void Database::queryByName(QString name)
{
    emit queryByNameThread(name);
}

void Database::queryPos(int userID, int step)
{
    emit queryPosThread(userID, step);
}


//根据ID删除记录
bool Database::deleteById(int id)
{
    QSqlDatabase db = QSqlDatabase::database("connection"); //建立数据库连接
    QSqlQuery query(db);
    query.prepare(QString("delete from automobil where id = %1").arg(id));
    if(!query.exec())
    {
        qDebug() << "删除记录失败！";
        return false;
    }
    return true;
}

void Database::queryByStep(int userID, int step)
{

}

void Database::on_queryByNameThread(QString name)
{
    QSqlQuery query(dataBase);
    if(name.data())
    {

        QString command =QString("SELECT * FROM PATIENTS WHERE PNAME LIKE '%%1%' ORDER BY TIMESTAMP DESC LIMIT 50").arg(name);

        if(query.exec(command))
        {
            emit queryByNameChanged(query);
        }

    }
    else
    {

        QString command =QString("SELECT * FROM PATIENTS ORDER BY TIMESTAMP DESC LIMIT 50").arg(name);

        if(query.exec(command))
        {
            emit queryByNameChanged(query);
        }



    }

}

void Database::on_queryAllThread()
{
    QSqlQuery query(dataBase);

    QString command = QString("SELECT * FROM PATIENTS ORDER BY TIMESTAMP DESC LIMIT 50");

    if(query.exec(command))
    {
        emit queryAllChanged(query);
    }
}

void Database::on_queryPosThread(int userID, int step)
{
    QSqlQuery query(dataBase);
    QString command =QString("SELECT * FROM STEP%1_%2").arg(userID).arg(step);

    if(query.exec(command))
    {
        emit queryPosChanged(step, query);
    }
}

//根据ID更新记录
bool Database::updateById(QString id, long timestamp, QString num, QString name, QString sex, QString birthday)
{
    QSqlQuery query(dataBase);

    query.prepare(QString("UPDATE patients SET TIMESTAMP = '%1', PID= '%2' , PNAME = '%3' , PSEX = '%4' , PBIRTHDAY = '%5'  WHERE ID = %6")
                  .arg(timestamp)
                  .arg(num)
                  .arg(name)
                  .arg(sex)
                  .arg(birthday)
                  .arg(id));

    if(query.exec())
    {
        return true;
    }
    else
    {
        QSqlError lastError = query.lastError();
        qDebug() << lastError.driverText() << QString(QObject::tr("更新失败"));
        return false;
    }

}

bool Database::updateDiagnosisById(QString id, long timestamp, QString diagnosis)
{
    QSqlQuery query(dataBase);

    QString command = QString("UPDATE patients SET TIMESTAMP = '%1', PDIAGNOSIS = '%2' WHERE ID = %3")
            .arg(timestamp)
            .arg(diagnosis)
            .arg(id);


    if(query.exec(command))
    {
        return true;
    }
    else
    {
        QSqlError lastError = query.lastError();
        qDebug() << lastError.driverText() << QString(QObject::tr("更新失败"));
        return false;
    }

}

QString Database::birthdayToAge(QString birthday)
{
    QDateTime startDateTime = QDateTime::fromString(birthday, "yyyy-MM-dd");

    QDateTime endDateTime = QDateTime::currentDateTime();

    int year = (endDateTime.toTime_t() - startDateTime.toTime_t()) / (365*24*60*60) + 1;

    return QString::number(year);
}
