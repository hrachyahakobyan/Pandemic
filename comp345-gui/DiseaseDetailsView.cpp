#include "stdafx.h"
#include "DiseaseDetailsView.h"
#include "Resources.h"

DiseaseDetailsView::DiseaseDetailsView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	selectedPalette = palette();
	deselectedPalette = palette();
	selectedPalette.setColor(QPalette::Background, Qt::blue);
	deselectedPalette.setColor(QPalette::Background, Qt::darkBlue);
	labels.push_back(std::make_tuple(0, ui.d0Image, ui.d0Vial));
	labels.push_back(std::make_tuple(1, ui.d1Image, ui.d1Vial));
	labels.push_back(std::make_tuple(2, ui.d2Image, ui.d2Vial));
	labels.push_back(std::make_tuple(3, ui.d3Image, ui.d3Vial));
	ui.d0Image->setPixmap(Resources::diseaseIcon(RegionDiseaseBlue).scaled(ui.d0Image->width(), ui.d0Image->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	ui.d1Image->setPixmap(Resources::diseaseIcon(RegionDiseaseYellow).scaled(ui.d1Image->width(), ui.d1Image->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	ui.d2Image->setPixmap(Resources::diseaseIcon(RegionDiseaseBlack).scaled(ui.d2Image->width(), ui.d2Image->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	ui.d3Image->setPixmap(Resources::diseaseIcon(RegionDiseaseRed).scaled(ui.d3Image->width(), ui.d3Image->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

DiseaseDetailsView::~DiseaseDetailsView()
{

}

void DiseaseDetailsView::update(const std::vector<pan::Disease>& diseases)
{
	for (auto t : labels){
		std::get<1>(t)->clear();
		std::get<1>(t)->setAutoFillBackground(true);
		std::get<2>(t)->clear();
	}
	std::size_t index = 0;
	for (const auto& d : diseases){
		auto type = d.getDiseaeType();
		std::get<0>(labels[index]) = type;
		auto label = std::get<1>(labels[index]);
		auto vial = std::get<2>(labels[index]);
		label->setPixmap(Resources::diseaseIcon(type).scaled(label->width(), label->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
		if (d.getIsCured()){
			vial->setPixmap(d.getIsEradicated() ? Resources::diseaseVialEradicated(type).scaled(vial->width(),
				vial->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation)
				: Resources::diseaseVialCured(type).scaled(vial->width(), vial->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
		}
		index++;
	}
}

void DiseaseDetailsView::mousePressEvent(QMouseEvent *event)
{
	for (auto t : labels){
		QPointF localpos = event->localPos();
		auto label = std::get<1>(t);
		QRect g = label->geometry();
		bool contains = g.contains(QPoint(localpos.x(), localpos.y()));
		if (contains){
			label->setPalette(selectedPalette);
			Q_EMIT diseaseSelected(std::get<0>(t));
			Resources::playClick();
			return;
		}
	}
}

void DiseaseDetailsView::mouseReleaseEvent(QMouseEvent *event)
{
	for (auto t : labels){
		QPointF localpos = event->localPos();
		auto label = std::get<1>(t);
		QRect g = label->geometry();
		bool contains = g.contains(QPoint(localpos.x(), localpos.y()));
		if (contains){
			label->setPalette(deselectedPalette);
			return;
		}
	}
}