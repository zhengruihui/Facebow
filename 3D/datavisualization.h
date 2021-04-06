#ifndef DATAVISUALIZATION_H
#define DATAVISUALIZATION_H

#include <QWidget>
#include <QtDataVisualization/q3dscatter.h>

using namespace QtDataVisualization;

namespace Ui {
class DataVisualization;
}

class DataVisualization : public QWidget
{
    Q_OBJECT

public:
    explicit DataVisualization(QWidget *parent = nullptr);
    ~DataVisualization();

private:
    Ui::DataVisualization *ui;

    Q3DScatter *m_graph;

    QScatterDataArray *dataArraySkull1;

    QScatterDataArray *dataArraySkull2;

    QScatterDataArray *dataArrayPoint;

    QScatter3DSeries *itemSkull1;

    QScatter3DSeries *itemSkull2;

    QScatter3DSeries *itemPoint;

public slots:
    void on_facebowPosChanged(float x, float y, float z, float c, float p, float r);
};

#endif // DATAVISUALIZATION_H
