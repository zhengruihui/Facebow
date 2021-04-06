#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QWidget>
#include <QWebEngineView>
#include <QMouseEvent>
#include <QChart>
#include <QChartView>
#include <QtCharts>
#include <QTimer>

namespace Ui {
class WebView;
}

class WebView : public QWebEngineView
{
    Q_OBJECT

public:
    explicit WebView(QWidget *parent = nullptr);
    ~WebView();

    void loadHtml();

public slots:
    void on_timeout();

    void on_loadFinished();

    void on_loadProgress(int progress);

    void on_loadImage(int step);


private:
    Ui::WebView *ui;

    QByteArray html;

    QTimer *timer;
};

#endif // WEBVIEW_H
