#include "stdafx.h"
#include "ActionSelectView.h"

ActionSelectView::ActionSelectView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	widgetActions[ui.bResearchWidget] = pan::ActionType::BuildStation;
	widgetActions[ui.cFlightWidget] = pan::ActionType::CharterFlight;
	widgetActions[ui.dCureWidget] = pan::ActionType::DiscoverCure;
	widgetActions[ui.dFlightWidget] = pan::ActionType::DirectFlight;
	widgetActions[ui.tDiseaseWidget] = pan::ActionType::TreatDisease;
	widgetActions[ui.driveWidget] = pan::ActionType::Move;
	widgetActions[ui.sFlightWidget] = pan::ActionType::ShuttleFlight;
	widgetActions[ui.drawWidget] = pan::ActionType::Draw;
}


ActionSelectView::~ActionSelectView()
{

}

void ActionSelectView::mousePressEvent(QMouseEvent *event)
{
	for (auto key : widgetActions.keys()){
		QPointF localpos = event->localPos();
		QRect r = key->rect();
		QRect g = key->geometry();
		bool contains = g.contains(QPoint(localpos.x(), localpos.y()));
		if (contains){
			Q_EMIT actionSelected(widgetActions[key]);
			return;
		}
	}
}