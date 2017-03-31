#include "stdafx.h"
#include "CityDetailsView.h"
#include "Resources.h"

CityDetailsView::CityDetailsView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.cubes1LabelImage->setPixmap(Resources::pixmapForRegion(0));
	ui.cubes2LabelImage->setPixmap(Resources::pixmapForRegion(1));
	ui.cubes3LabelImage->setPixmap(Resources::pixmapForRegion(2));
	ui.cubes4LabelImage->setPixmap(Resources::pixmapForRegion(3));
	researchOkPixmap.load("Resources\\station_ok.png");
	researchNoPixamp.load("Resources\\station_no.png");
	setStyleSheet("background-color:white;");
}

CityDetailsView::~CityDetailsView()
{

}

void CityDetailsView::update(const pan::City& city)
{
	ui.nameLabel->setText(QString::fromStdString(city.getName()));
	ui.populationLabel->setText(QString::fromStdString(std::to_string(city.population)));
	ui.regionLabelImage->setPixmap(Resources::pixmapForRegion(city.getRegion()));
	ui.cubes1Label->setText(QString::fromStdString(std::to_string(city.getCubes(0))));
	ui.cubes2Label->setText(QString::fromStdString(std::to_string(city.getCubes(1))));
	ui.cubes3Label->setText(QString::fromStdString(std::to_string(city.getCubes(2))));
	ui.cubes4Label->setText(QString::fromStdString(std::to_string(city.getCubes(3))));
	ui.stationLabelImage->setPixmap(city.researchStation ? researchOkPixmap : researchNoPixamp);
}

void CityDetailsView::on_okButton_clicked()
{
	this->hide();
}