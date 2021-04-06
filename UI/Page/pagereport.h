#ifndef PAGEREPORT_H
#define PAGEREPORT_H

#include <QWidget>
#include <QWebEngineView>
#include <QMouseEvent>
#include <QChart>
#include <QChartView>
#include <QtCharts>
#include <QTimer>


namespace Ui {
class PageReport;
}

class PageReport : public QWidget
{
    Q_OBJECT

public:
    explicit PageReport(QWidget *parent = nullptr);
    ~PageReport();

    void loadReport();



private slots:

    void on_pdfPrintingFinished();

    void on_toolButtonZoomIn_clicked();

    void on_toolButtonZoomOut_clicked();

    void on_toolButtonNormal_clicked();

    void on_toolButtonPDF_clicked();

    void on_toolButtonPrint_clicked();


    void on_toolButton1_1_clicked();

    void on_toolButtonhorizontal_clicked();

    void on_toolButtonFill_clicked();

    void on_toolButtonLayout_clicked();

private:
    Ui::PageReport *ui;

    QWebEngineView *view;

    QByteArray html;

    QSplineSeries *series1;

    QChart *m_chart;

    QChartView *chartView;

    QVector<float> vertex;

    QString currentPath;

};

#endif // PAGEREPORT_H
