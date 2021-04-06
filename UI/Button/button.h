#ifndef BUTTON_H
#define BUTTON_H

#include <QWidget>


namespace Ui {
class Button;
}

class Button : public QWidget
{
    Q_OBJECT

public:
    explicit Button(QWidget *parent = nullptr);
    ~Button();

    void setImage(QString path);
    void setStep(QString step);
    QString getStep(void);

    void setText(QString text);




signals:
    void button_pressed(int step);
private:
    Ui::Button *ui;
    int step;
};

#endif // BUTTON_H
