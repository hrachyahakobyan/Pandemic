#include "stdafx.h"
#include "CityDetailsView.h"

CityDetailsView::CityDetailsView(QWidget *parent)
	: QWidget(parent), regionPixmaps(4)
{
	ui.setupUi(this);
	// blue yellow black red
	regionPixmaps[0].load("Resources\\region_blue.png");
	regionPixmaps[1].load("Resources\\region_yellow.png");
	regionPixmaps[2].load("Resources\\region_black.png");
	regionPixmaps[3].load("Resources\\region_red.png");
	ui.cubes1LabelImage->setPixmap(regionPixmaps[0]);
	ui.cubes2LabelImage->setPixmap(regionPixmaps[1]);
	ui.cubes3LabelImage->setPixmap(regionPixmaps[2]);
	ui.cubes4LabelImage->setPixmap(regionPixmaps[3]);
	researchOkPixmap.load("Resources\\station_ok.png");
	researchNoPixamp.load("Resources\\station_no.png");
}

CityDetailsView::~CityDetailsView()
{

}

void CityDetailsView::update(const pan::City& city)
{
	ui.nameLabel->setText(QString::fromStdString(city.getName()));
	ui.populationLabel->setText(QString::fromStdString(std::to_string(city.population)));
	ui.regionLabelImage->setPixmap(regionPixmaps[city.getRegion()]);
	ui.cubes1Label->setText(QString::fromStdString(std::to_string(city.getCubes(0))));
	ui.cubes2Label->setText(QString::fromStdString(std::to_string(city.getCubes(1))));
	ui.cubes3Label->setText(QString::fromStdString(std::to_string(city.getCubes(2))));
	ui.cubes4Label->setText(QString::fromStdString(std::to_string(city.getCubes(3))));
	ui.stationLabelImage->setPixmap(city.researchStation ? researchOkPixmap : researchNoPixamp);
}