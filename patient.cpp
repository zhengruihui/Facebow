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
    db = QSqlDatabase::addDatabase("QSQLITE", "connection");
    db.setDatabaseName("Patient.db");
    if(db.open())
    {
        qDebug() << QObject::tr("数据库连接成功！\n");

        QSqlQuery query(db);

        QString command = QString("CREATE TABLE PATIENTS ("
                                  "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                                  "PID VARCHAR(40) NOT NULL, "
                                  "PNAME VARCHAR(40) NOT NULL, "
                                  "PSEX VARCHAR(40) NOT NULL, "
                                  "PBIRTHDAY VARCHAR(40) NOT NULL, "
                                  "PDIAGNOSIS VARCHAR(40) NOT NULL)");



        if(query.exec(command))
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
    db.setDatabaseName("Patient.db");
    db.close();
}


//向数据库中插入记录
QString Patient::insert(QString num, QString name, QString sex, QString birthday)
{
    QSqlQuery query(db);
    QString ID;

    QString command = QString("INSERT INTO PATIENTS (PID, PNAME, PSEX, PBIRTHDAY, PDIAGNOSIS) "
                              "VALUES ('%1', '%2', '%3', '%4', '%5')")
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

            for(char i='1'; i<'1'+8; i++)
            {

                query.prepare(QString("CREATE TABLE POSITION%1_%2 ("
                                      "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                                      "X VARCHAR(40) NOT NULL, "
                                      "Y VARCHAR(40) NOT NULL, "
                                      "Z VARCHAR(40) NOT NULL, "
                                      "EX VARCHAR(40) NOT NULL, "
                                      "EY VARCHAR(40) NOT NULL, "
                                      "EZ VARCHAR(40) NOT NULL)").arg(ID).arg(i));
                if(query.exec())
                {
                    qDebug() << "创建位置表成功";

                }

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


bool Patient::insertPosition(QString userID, QString step, QString x, QString y, QString z, QString ex, QString ey, QString ez)
{
    QSqlQuery query(db);

    QString command = QString("INSERT INTO POSITION%1_%2 (X, Y, Z, EX, EY, EZ) "
                              "VALUES ('%3', '%4', '%5', '%6', '%7', '%8')")
                              .arg(userID)
                              .arg(step)
                              .arg(x)
                              .arg(y)
                              .arg(z)
                              .arg(ex)
                              .arg(ey)
                              .arg(ez);

    qDebug() << command;



    if(query.exec(command))
    {
        return true;
    }
    else
    {
        return false;
    }

}


bool Patient::queryByName(QString name)
{
    QSqlQuery query(db);
    if(name.data())
    {
        QString command = QString(QString("SELECT ID, PID, PNAME, PSEX, PBIRTHDAY, PDIAGNOSIS FROM PATIENTS WHERE PNAME LIKE '%%1%' ORDER BY ID DESC LIMIT 50").arg(name));


        if(query.exec(command))
        {
            while(query.next())
            {

                emit searchChanged(query.value(0).toString(), query.value(1).toString(), query.value(2).toString(), query.value(3).toString(), query.value(4).toString(), query.value(5).toString());

            }
            return true;
        }
        else
        {
            return false;
        }


    }
    else
    {

        query.prepare(QString("SELECT * FROM PATIENTS ORDER BY ID DESC LIMIT 50"));
        query.exec();

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

//根据ID更新记录
bool Patient::updateById(QString id, QString num, QString name, QString sex, QString birthday)
{
    QSqlQuery query(db);

    query.prepare(QString("UPDATE patients SET PID= '%1' , PNAME = '%2' , PSEX = '%3' , PBIRTHDAY = '%4'  WHERE ID = %5")
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

bool Patient::updateDiagnosisById(QString id, QString diagnosis)
{
    QSqlQuery query(db);

    QString command = QString("UPDATE patients SET PDIAGNOSIS = '%1' WHERE ID = %2")
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

QString Patient::birthdayToAge(QString birthday)
{

    QDateTime startDateTime = QDateTime::fromString(birthday, "yyyy-MM-dd");

    QDateTime endDateTime = QDateTime::currentDateTime();

    int year = (endDateTime.toTime_t() - startDateTime.toTime_t()) / (365*24*60*60) + 1;

    return QString::number(year);
}
