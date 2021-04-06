#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>

namespace Ui {
class ImageWidget;
}

class ImageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ImageWidget(QWidget *parent = nullptr);
    ~ImageWidget();

    void setImage(QString value);

protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::ImageWidget *ui;
    QString imagePath;
};

#endif // IMAGEWIDGET_H
