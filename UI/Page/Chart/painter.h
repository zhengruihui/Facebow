#ifndef PAINTER_H
#define PAINTER_H

#include <QWidget>
#include <QPainter>
#include <QThread>

namespace Ui {
class Painter;
}

class Painter : public QWidget
{
    Q_OBJECT

public:
    explicit Painter(QWidget *parent = nullptr);
    ~Painter();

private:
    void paintEvent(QPaintEvent *event);
signals:
    void paintE();

private:
    Ui::Painter *ui;
    QThread *paintThread;



private slots:
    void paint();
};

#endif // PAINTER_H
