#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Pandemic.h"

class Pandemic : public QMainWindow
{
	Q_OBJECT

public:
	Pandemic(QWidget *parent = Q_NULLPTR);

private:
	Ui::PandemicClass ui;
};
