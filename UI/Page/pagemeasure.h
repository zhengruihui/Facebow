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

    void on_toolButtonZoomIn_clicked();

    void on_toolButtonNormal_clicked();

    void on_toolButtonLeft_clicked(bool checked);

    void on_toolButtonRight_clicked(bool checked);

    void on_toolButtonForward_clicked(bool checked);

    void on_toolButtonTop_clicked(bool checked);

    void on_toolButtonOblique_clicked(bool checked);

private:
    Ui::PageMeasure *ui;
};

#endif // PAGEMEASURE_H
