#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Pandemic.h"

class Pandemic : public QMainWindow
{
	Q_OBJECT

public:
	Pandemic(QWidget *parent = Q_NULLPTR); 
	void update(pan::Game&& game);
public Q_SLOTS:
	void on_cityItemSelected(pan::CityIndex);
private:
	Ui::PandemicClass ui;
	pan::Game game;
};
