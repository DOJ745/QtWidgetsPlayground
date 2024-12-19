#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <qchart.h>
#include <QLineSeries>
#include <QValueAxis>
#include <QChartView>
#include <QSplineSeries>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // Создаём график
    QChart* chart = new QChart();
    chart->setTitle("Movement chart");

    // Создаём оси
    QValueAxis* axisX = new QValueAxis();
    axisX->setTitleText("X (time or position)");
    axisX->setRange(0, 12);

    QValueAxis* axisY = new QValueAxis();
    axisY->setTitleText("Y (bonding head position)");
    axisY->setRange(0, 12);

    // Добавляем оси на график
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    // Создаём разноцветные линии (секции графика)
    QLineSeries* line1 = new QLineSeries();
    line1->setName("Movement 1");
    line1->setColor(Qt::GlobalColor::red);
    line1->append(0, 0);
    line1->append(1, 2);
    line1->append(2, 4);
    line1->append(3, 3);
    line1->append(4, 5);

    QLineSeries* line2 = new QLineSeries();
    line2->setName("Movement 2");
    line2->setColor(Qt::GlobalColor::blue);
    line2->append(4, 5);
    line2->append(5, 6);
    line2->append(6, 3);
    line2->append(7, 4);
    line2->append(8, 2);

    QLineSeries* line3 = new QLineSeries();
    line3->setName("Movement 3");
    line3->setColor(Qt::GlobalColor::green);
    line3->append(8, 2);
    line3->append(9, 3);
    line3->append(10, 4);
    line3->append(11, 5);
    line3->append(12, 6);

    QSplineSeries* spline3 = new QSplineSeries();
    spline3->setName("Spline Movement 3");
    spline3->setColor(Qt::GlobalColor::darkYellow);
    spline3->append(8, 2);
    spline3->append(9, 5);
    spline3->append(10, 1);
    spline3->append(11, 5);
    spline3->append(12, 6);

    // Добавляем линии на график
    chart->addSeries(line1);
    chart->addSeries(line2);
    chart->addSeries(line3);
    chart->addSeries(spline3);

    // Привязываем линии к текущим осям координат
    line1->attachAxis(axisX);
    line1->attachAxis(axisY);

    line2->attachAxis(axisX);
    line2->attachAxis(axisY);

    line3->attachAxis(axisX);
    line3->attachAxis(axisY);

	spline3->attachAxis(axisX);
	spline3->attachAxis(axisY);

    // Включаем легенду и убираем фон
    chart->legend()->setVisible(true);
    chart->setBackgroundBrush(Qt::GlobalColor::white);

    // Создаём виджет для отображения графика
    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Добавляем график в главное окно
    QWidget* centralWidget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);
    layout->addWidget(chartView);

    w.setCentralWidget(centralWidget);
    w.show();

    return a.exec();
}
