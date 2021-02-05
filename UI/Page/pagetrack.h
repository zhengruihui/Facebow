#ifndef PageTrack_H
#define PageTrack_H

#include <QWidget>

namespace Ui {
class PageTrack;
}

class PageTrack : public QWidget
{
    Q_OBJECT

public:
    explicit PageTrack(QWidget *parent = nullptr);
    ~PageTrack();


    void paintChart();

private slots:

    void on_toolButtonMeasureStart_clicked(bool checked);

    void on_toolButtonDeviceSetting_pressed();

    void updateDisplay();

    void on_toolButtonPlay_clicked(bool checked);


private:
    Ui::PageTrack *ui;
};

#endif // PageTrack_H
