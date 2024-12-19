#pragma once

#include <QWidget>
#include <qchart.h>
#include <qvalueaxis.h>
#include <qlineseries.h>
#include <qsplineseries.h>
#include <qchartview.h>
#include <qboxlayout.h>

class ClassicChart  : public QWidget
{
	Q_OBJECT

public:
	ClassicChart(QWidget *parent = nullptr);
	~ClassicChart();
};
