#include "stdafx.h"
#include "ActionSelectView.h"

ActionSelectView::ActionSelectView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
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
			widgetActions[key].first->setStyleSheet("border: 3px solid green");
			Q_EMIT actionSelected(widgetActions[key].second);
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
			widgetActions[key].first->setStyleSheet("border: 0px solid green");
			return;
		}
	}
}