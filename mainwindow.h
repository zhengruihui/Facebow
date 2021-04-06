#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_buttonInfo_pressed();

    void on_buttonMeasure_pressed();

    void on_buttonTrack_pressed();

    void on_buttonReport_pressed();

    void on_buttonHelp_pressed();

    void on_buttonMin_clicked();

    void on_buttonMax_clicked(bool checked);

    void on_buttonClose_clicked();

    void on_pushButtonLogo_clicked();

protected:
    void mousePressEvent(QMouseEvent *event)override;
    void mouseMoveEvent(QMouseEvent *event)override;
    void mouseReleaseEvent(QMouseEvent *event)override;
    void mouseDoubleClickEvent(QMouseEvent *event)override;


private:
    Ui::MainWindow *ui;

    bool m_leftButtonPressed;

    QPoint m_start;
};
#endif // MAINWINDOW_H
