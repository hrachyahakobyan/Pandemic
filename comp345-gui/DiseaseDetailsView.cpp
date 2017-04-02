#include "stdafx.h"
#include "DiseaseDetailsView.h"
#include "Resources.h"

DiseaseDetailsView::DiseaseDetailsView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setStyleSheet("background-color:#0d0238;");
	vialLabels.push_back(ui.d0Vial);
	vialLabels.push_back(ui.d1Vial);
	vialLabels.push_back(ui.d2Vial);
	vialLabels.push_back(ui.d3Vial);
	ui.d0Image->setPixmap(Resources::diseaseIcon(RegionDiseaseBlue).scaled(ui.d0Image->width(), ui.d0Image->height(), Qt::KeepAspectRatio));
	ui.d1Image->setPixmap(Resources::diseaseIcon(RegionDiseaseYellow).scaled(ui.d1Image->width(), ui.d1Image->height(), Qt::KeepAspectRatio));
	ui.d2Image->setPixmap(Resources::diseaseIcon(RegionDiseaseBlack).scaled(ui.d2Image->width(), ui.d2Image->height(), Qt::KeepAspectRatio));
	ui.d3Image->setPixmap(Resources::diseaseIcon(RegionDiseaseRed).scaled(ui.d3Image->width(), ui.d3Image->height(), Qt::KeepAspectRatio));
}

DiseaseDetailsView::~DiseaseDetailsView()
{

}

void DiseaseDetailsView::update(const std::vector<pan::Disease>& diseases)
{
	std::size_t index = 0;
	for (const auto& d : diseases){
		if (d.getIsCured() == false){
			vialLabels[index]->clear();
			index++;
			continue;
		}
		vialLabels[index]->setPixmap(d.getIsEradicated() ? Resources::diseaseVialEradicated(index).scaled(vialLabels[index]->width(), vialLabels[index]->height(), Qt::KeepAspectRatio) 
			: Resources::diseaseVialCured(index).scaled(vialLabels[index]->width(), vialLabels[index]->height(), Qt::KeepAspectRatio));
	}
}