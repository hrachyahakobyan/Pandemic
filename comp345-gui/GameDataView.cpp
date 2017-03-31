#include "stdafx.h"
#include "GameDataView.h"
#include "Resources.h"

GameDataView::GameDataView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.region1Image->setPixmap(Resources::pixmapForRegion(0).scaled(ui.region1Image->width(), ui.region1Image->height(), Qt::KeepAspectRatio));
	ui.region2Image->setPixmap(Resources::pixmapForRegion(1).scaled(ui.region2Image->width(), ui.region2Image->height(), Qt::KeepAspectRatio));
	ui.region3Image->setPixmap(Resources::pixmapForRegion(2).scaled(ui.region3Image->width(), ui.region3Image->height(), Qt::KeepAspectRatio));
	ui.region4Image->setPixmap(Resources::pixmapForRegion(3).scaled(ui.region4Image->width(), ui.region4Image->height(), Qt::KeepAspectRatio));
	ui.outbreakImage->setPixmap(Resources::outbreakPixmap().scaled(ui.outbreakImage->width(), ui.outbreakImage->height(), Qt::KeepAspectRatio));
	ui.infectionImage->setPixmap(Resources::infectionPixmap().scaled(ui.infectionImage->width(), ui.infectionImage->height(), Qt::KeepAspectRatio));
	ui.stationImage->setPixmap(Resources::stationPixmap().scaled(ui.stationImage->width(), ui.stationImage->height(), Qt::KeepAspectRatio));
}

GameDataView::~GameDataView()
{
}

void GameDataView::update(const pan::GameData& data)
{
	ui.infectionLabel->setText(QString::fromStdString(std::to_string(data.settings.infectionRates[data.infectionRateMarker])));
	ui.outbreakLabel->setText(QString::fromStdString(std::to_string(data.outbreakMarker)));
	ui.stationLabel->setText(QString::fromStdString(std::to_string(data.researchStations)));
	ui.region1Label->setText(QString::fromStdString(std::to_string(data.diseaseCubes[0])));
	ui.region2Label->setText(QString::fromStdString(std::to_string(data.diseaseCubes[1])));
	ui.region3Label->setText(QString::fromStdString(std::to_string(data.diseaseCubes[2])));
	ui.region4Label->setText(QString::fromStdString(std::to_string(data.diseaseCubes[3])));
}
