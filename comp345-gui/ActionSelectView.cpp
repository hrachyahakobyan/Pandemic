#include "stdafx.h"
#include "ActionSelectView.h"
#include "Resources.h"

ActionSelectView::ActionSelectView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	selectedPalette = palette();
	deselectedPalette = palette();
	selectedPalette.setColor(QPalette::Background, Qt::blue);
	deselectedPalette.setColor(QPalette::Background, Qt::darkBlue);
	widgetActions[ui.bResearchWidget] = qMakePair(ui.buildResearchLabel, pan::ActionType::BuildStation);
	widgetActions[ui.cFlightWidget] = qMakePair(ui.charterFlightLabel, pan::ActionType::CharterFlight);
	widgetActions[ui.dCureWidget] = qMakePair(ui.discoverLabel, pan::ActionType::DiscoverCure);
	widgetActions[ui.dFlightWidget] = qMakePair(ui.directFlightLabel, pan::ActionType::DirectFlight);
	widgetActions[ui.tDiseaseWidget] = qMakePair(ui.treatDiseaseLabel, pan::ActionType::TreatDisease);
	widgetActions[ui.driveWidget] = qMakePair(ui.moveLabel, pan::ActionType::Move);
	widgetActions[ui.sFlightWidget] = qMakePair(ui.shuttleFlightLabel, pan::ActionType::ShuttleFlight);
	widgetActions[ui.drawWidget] = qMakePair(ui.drawLabel, pan::ActionType::Draw);
	widgetActions[ui.infectWidget] = qMakePair(ui.infectLabel, pan::ActionType::Infect);
	widgetActions[ui.discardWidget] = qMakePair(ui.discardLabel, pan::ActionType::Discard);
	widgetActions[ui.shareWidget] = qMakePair(ui.shareLabel, pan::ActionType::ShareKnowledge);

	for (auto p : widgetActions){
		p.first->setAutoFillBackground(true);
		p.first->setPixmap(Resources::getPixmapForAction(p.second).scaled(p.first->width(), p.first->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	}

	QPalette pal = palette();
	pal.setColor(QPalette::Background, Qt::darkBlue);
	this->setAutoFillBackground(true);
	this->setPalette(pal);
}


ActionSelectView::~ActionSelectView()
{

}

void ActionSelectView::mousePressEvent(QMouseEvent *event)
{
	for (auto key : widgetActions.keys()){
		QPointF localpos = event->localPos();
		QRect g = key->geometry();
		bool contains = g.contains(QPoint(localpos.x(), localpos.y()));
		if (contains){
			widgetActions[key].first->setPalette(selectedPalette);
			Q_EMIT actionSelected(widgetActions[key].second);
			Resources::playClick();
			return;
		}
	}
}

void ActionSelectView::mouseReleaseEvent(QMouseEvent *event)
{
	for (auto key : widgetActions.keys()){
		QPointF localpos = event->localPos();
		QRect g = key->geometry();
		bool contains = g.contains(QPoint(localpos.x(), localpos.y()));
		if (contains){
			widgetActions[key].first->setPalette(deselectedPalette);
			return;
		}
	}
}