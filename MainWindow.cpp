#include "MainWindow.h"
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include "AnimatedScatter.h"
#include "ClassicChart.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    ui.comboBox->addItem("item1", 1);
    ui.comboBox->addItem("item2", 2);
    ui.comboBox->addItem("item3", 3);
    ui.comboBox->addItem("item4", 4);
    ui.comboBox->addItem("item5", 5);

    QDoubleValidator* validator = new QDoubleValidator(-500.0, 500.0, 4, this); 
    ui.lineEdit->setValidator(validator);

    connect(ui.lineEdit, &QLineEdit::textEdited, this, &MainWindow::onTextChanged);
    connect(ui.dial, &QDial::sliderMoved, this, &MainWindow::onSliderMoved);

    ui.spinBox->setMinimum(-100);
    ui.spinBox->setMaximum(100);
    ui.spinBox->setSingleStep(1);

    ui.frame->setStyleSheet("background-color: black;");


    QGraphicsColorizeEffect* colorEffect = new QGraphicsColorizeEffect(ui.frame);
    ui.frame->setGraphicsEffect(colorEffect);

    QPropertyAnimation* animationColor = new QPropertyAnimation(colorEffect, "color");
    animationColor->setDuration(1000);
    animationColor->setStartValue(QColor(255, 255, 255)); 
    animationColor->setEndValue(QColor(255, 0, 0));
    animationColor->start(QAbstractAnimation::DeleteWhenStopped); // Автоматическое удаление после завершения

    connect(ui.horizontalSlider, &QSlider::valueChanged, this, &MainWindow::onHorizontalSliderChanged);

    // Добавляем 3D график в главное окно
    AnimatedScatter* animatedScatter = new AnimatedScatter();
    QVBoxLayout* layout3D = new QVBoxLayout(ui.threeDimensionChartWidget);
    layout3D->addWidget(animatedScatter);
    ui.threeDimensionChartWidget->setLayout(layout3D);
    
    // Добавляем 2D график в главное окно
    ClassicChart* classicChart = new ClassicChart();
    QVBoxLayout* layout2D = new QVBoxLayout(ui.classicChartWidget);
    layout2D->addWidget(classicChart);
	ui.classicChartWidget->setLayout(layout2D);
}

MainWindow::~MainWindow()
{}
