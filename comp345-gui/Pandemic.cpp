#include "stdafx.h"
#include "Pandemic.h"
#include "MapView.h"

Pandemic::Pandemic(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.mapView, SIGNAL(cityItemSelected(pan::CityIndex)), this, SLOT(on_cityItemSelected(pan::CityIndex)));
}

void Pandemic::update(pan::Game&& game)
{
	this->game = std::move(game);
	ui.mapView->update(this->game.getMap());
}

void Pandemic::on_cityItemSelected(pan::CityIndex index)
{
	ui.cityDetailsView->update(game.getMap()[index]);
}

