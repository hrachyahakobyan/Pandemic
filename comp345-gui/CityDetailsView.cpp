#include "stdafx.h"
#include "CityDetailsView.h"
#include "Resources.h"

CityDetailsView::CityDetailsView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.cubes1LabelImage->setPixmap((Resources::pixmapForRegion(0)).scaled(ui.cubes1LabelImage->width(), ui.cubes1LabelImage->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	ui.cubes2LabelImage->setPixmap((Resources::pixmapForRegion(1)).scaled(ui.cubes2LabelImage->width(), ui.cubes2LabelImage->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	ui.cubes3LabelImage->setPixmap((Resources::pixmapForRegion(2)).scaled(ui.cubes3LabelImage->width(), ui.cubes3LabelImage->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	ui.cubes4LabelImage->setPixmap((Resources::pixmapForRegion(3)).scaled(ui.cubes4LabelImage->width(), ui.cubes4LabelImage->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	researchOkPixmap.load("Resources\\station_ok.png");
	researchNoPixamp.load("Resources\\station_no.png");
	avatarLabels.push_back(ui.pAvatar1);
	avatarLabels.push_back(ui.pAvatar2);
	avatarLabels.push_back(ui.pAvatar3);
	avatarLabels.push_back(ui.pAvatar4);
}

CityDetailsView::~CityDetailsView()
{

}

void CityDetailsView::update(const pan::City& city)
{
	for (auto p : avatarLabels){
		p->setPixmap(Resources::getAvatarBlank().scaled(p->width(), p->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	}
	ui.nameLabel->setText(QString::fromStdString(city.getName()));
	ui.populationLabel->setText(QString::fromStdString(std::to_string(city.population)));
	ui.regionLabelImage->setPixmap((Resources::pixmapForRegion(city.getRegion())).scaled(ui.regionLabelImage->width(), ui.regionLabelImage->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	ui.cubes1Label->setText(QString::fromStdString(std::to_string(city.getCubes(0))));
	ui.cubes2Label->setText(QString::fromStdString(std::to_string(city.getCubes(1))));
	ui.cubes3Label->setText(QString::fromStdString(std::to_string(city.getCubes(2))));
	ui.cubes4Label->setText(QString::fromStdString(std::to_string(city.getCubes(3))));
	ui.stationLabelImage->setPixmap((city.researchStation ? researchOkPixmap : researchNoPixamp).scaled(ui.stationLabelImage->width(), ui.stationLabelImage->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	std::size_t index = 0;
	for (const auto& p : city.getPlayers()){
		avatarLabels[index]->setPixmap(Resources::avatarForRole(p->getRole().role).scaled(avatarLabels[index]->width(), avatarLabels[index]->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
		index++;
	}
}

void CityDetailsView::on_okButton_clicked()
{
	this->hide();
}