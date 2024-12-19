#pragma once
#include <qchart.h>
#include <QLineSeries>
#include <QValueAxis>
#include <QChartView>
#include <QSplineSeries>
#include <Q3DSurface>
#include <QScatterDataProxy>
#include <QtDataVisualization/Q3DScatter>
#include <QtDataVisualization/QScatterDataProxy>
#include <QtDataVisualization/QScatter3DSeries>
#include <QtDataVisualization/qscatterdataitem.h>
#include <qtimer.h>
#include <QWidget>
#include <qboxlayout.h>

class AnimatedScatter : public QWidget
{
    Q_OBJECT

public:
    ~AnimatedScatter();
    AnimatedScatter(QWidget* parent = nullptr) : QWidget(parent)
    {
        // ������ ������
        scatterGraph = new Q3DScatter();
        container = QWidget::createWindowContainer(scatterGraph);

        // ������ ����� ��� ����� �����
        dataProxy = new QScatterDataProxy();
        scatterSeries = new QScatter3DSeries(dataProxy);
        scatterSeries->setItemSize(0.2f);
        scatterSeries->setBaseColor(Qt::red);

        // ��������� �����
        QScatterDataArray* dataArray = new QScatterDataArray();
        dataArray->append(QVector3D(0.0f, 0.0f, 0.0f));
        dataProxy->resetArray(dataArray);

        scatterGraph->addSeries(scatterSeries);

        // ����������� ��� 
        QValue3DAxis *axisX = new QValue3DAxis(); 
        axisX->setRange(-3.0f, 3.0f); 
        scatterGraph->setAxisX(axisX); 
        
        QValue3DAxis *axisY = new QValue3DAxis(); 
        axisY->setRange(-3.0f, 3.0f); 
        scatterGraph->setAxisY(axisY);

        QValue3DAxis *axisZ = new QValue3DAxis(); 
        axisZ->setRange(-3.0f, 3.0f); 
        scatterGraph->setAxisZ(axisZ);

        // ����� ��� ���������� �������
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->addWidget(container);

        // ��������� �������
        direction = QVector3D(1.0f, 1.0f, 1.0f); // ����������� ��������

        // ������ ��� ��������
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &AnimatedScatter::updatePosition);
        timer->start(10);
    }

private slots:
    void updatePosition()
    {
        // �������� ������� ������� �����
        const QScatterDataArray* constDataArray = dataProxy->array(); 
        
        if (!constDataArray || constDataArray->isEmpty()) 
            return;
        
        QScatterDataArray* dataArray = new QScatterDataArray(*constDataArray);
        QScatterDataItem &item = (*dataArray)[0]; 
        QVector3D currentPosition = item.position();

        // ��������� �������
        float x = currentPosition.x() + direction.x() * 0.1f;
        float y = currentPosition.y() + direction.y() * 0.1f;
		float z = currentPosition.z() + direction.z() * 0.1f;

        // ������ �����������, ���� ����� ��������� ������
        if (x > 3.0f || x < -3.0f)
        {
            direction.setX(-direction.x());
        }

        if (y > 3.0f || y < -3.0f)
        {
            direction.setY(-direction.y());
        } 

        if (z > 3.0f || z < -3.0f)
        {
            direction.setZ(-direction.z());
        }

        // ������������� ����� �������
        item.setPosition(QVector3D(x, y, z));
        
        dataProxy->resetArray(dataArray);
    }

private:
    Q3DScatter* scatterGraph;
    QWidget* container;
    QScatterDataProxy* dataProxy;
    QScatter3DSeries* scatterSeries;
    QTimer* timer;
    QVector3D direction;
};
