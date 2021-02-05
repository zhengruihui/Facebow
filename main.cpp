#include "mainwindow.h"
#include <QSqlQuery>
#include <QApplication>
#include <QMetaType>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator *qtTranslator = new QTranslator();

    if(qtTranslator->load(":/Language/English.qm")){
        a.installTranslator(qtTranslator);
    }


    qRegisterMetaType<QSqlQuery>("QSqlQuery");

    MainWindow w;
    w.show();
    return a.exec();
}
