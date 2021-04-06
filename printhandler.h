#ifndef PRINTHANDLER_H
#define PRINTHANDLER_H

#include <QObject>
#include <QPainter>
#include <QPrinter>
#include <QWebEnginePage>

//QT_BEGIN_NAMESPACE
//class QPainter;
//class QPrinter;
//class QWebEnginePage;
//QT_END_NAMESPACE

class PrintHandler : public QObject
{
    Q_OBJECT
public:
    PrintHandler(QObject *parent = nullptr);
    void setPage(QWebEnginePage *page);

public slots:
    void print();
    void printPreview();
    void printDocument(QPrinter *printer);

private:
    QWebEnginePage *m_page = nullptr;
    bool m_inPrintPreview = false;
};

#endif // PRINTHANDLER_H
