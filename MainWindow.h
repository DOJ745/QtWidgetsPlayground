#pragma once

#include <QtWidgets/QMainWindow>
#include <qmessagebox.h>
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onCheckBoxChanged(int state)
    {
        QMessageBox::information(NULL
            , "Checkbox"
            , QString("Checkbox changed!\nIt's state: %1").arg(state == 2 ? "Checked" : "Unchecked"));
    }

    void onRadioButtonChanged(bool state)
    {
        QMessageBox::information(NULL
            , "Radio Button"
            , QString("Radio button changed!\nIt's state: %1").arg(state));
    }

    void onCommandLinkButtonClicked()
    {
        QMessageBox::information(NULL
            , "Command Link Button"
            , QString("Command Link Button pressed!"));
    }

    void onTextChanged(const QString& text)
    {
        int pos = 0;
        QString tempText = text;
        QValidator::State state = ui.lineEdit->validator()->validate(tempText, pos);

        switch (state) 
        {
            case QValidator::Intermediate:
                ui.lineEdit->setStyleSheet("color: blue;");
                break;
            case QValidator::Invalid:
                ui.lineEdit->setStyleSheet("color: red;");
                break;
            default:
                ui.lineEdit->setStyleSheet("color: black;");
                break;
        }
    }

    void onSpinValueChanged(int number)
    {
        if (number <= ui.spinBox->minimum() / 2)
        {
            ui.spinBox->setStyleSheet("color: red;");
        }
        else if (number > ui.spinBox->minimum() / 2 && number <= 0)
        {
            ui.spinBox->setStyleSheet("color: blue;");
        }
        else
        {
            ui.spinBox->setStyleSheet("color: green;");
        }
    }

    void onSliderMoved(int num)
    {
        ui.lcdNumber->display(num);
    }

    void onHorizontalSliderChanged(int num)
    {
        ui.progressBar->setValue(num);
    }

private:
    Ui::MainWindowClass ui;
};
