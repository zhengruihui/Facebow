#ifndef PAGEMEASURE_H
#define PAGEMEASURE_H

#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
class PageMeasure;
}

class PageMeasure : public QWidget
{
    Q_OBJECT

public:
    explicit PageMeasure(QWidget *parent = nullptr);
    ~PageMeasure();


private slots:

    void on_toolButtonMeasureStart_clicked(bool checked);

    void on_toolButtonMeasureSetting_pressed();

    void on_toolButtonDeviceSetting_pressed();


    void on_listWidgetButton_itemPressed(QListWidgetItem *item);

    void on_toolButtonZoomOut_clicked();

private:
    Ui::PageMeasure *ui;
};

#endif // PAGEMEASURE_H
