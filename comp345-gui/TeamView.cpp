#include "stdafx.h"
#include "TeamView.h"
#include "Resources.h"

TeamView::TeamView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	selectedPalette = palette();
	deselectedPalette = palette();
	selectedPalette.setColor(QPalette::Background, Qt::blue);
	deselectedPalette.setColor(QPalette::Background, Qt::darkBlue);
	playerWidgets.push_back(ui.p1Label);
	playerWidgets.push_back(ui.p2Label);
	playerWidgets.push_back(ui.p3Label);
	playerWidgets.push_back(ui.p4Label);
}

TeamView::~TeamView()
{

}

void TeamView::update(const std::vector<pan::PlayerPtr>& players)
{
	indexMap.clear();
	for (auto pair : playerWidgets){
		pair->clear();
		pair->setAutoFillBackground(true);
	}
	for (int i = 0; i < players.size(); i++){
		indexMap[playerWidgets[i]] = players[i]->index;
		playerWidgets[i]->setPixmap(Resources::cardForRole(players[i]->getRole().role).scaled(playerWidgets[i]->width(), playerWidgets[i]->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	}
}

void TeamView::mousePressEvent(QMouseEvent *event)
{
	for (auto widget : playerWidgets){
		QPointF localpos = event->localPos();
		QRect g = widget->geometry();
		bool contains = g.contains(QPoint(localpos.x(), localpos.y()));
		if (contains && indexMap.find(widget) != indexMap.end()){
			widget->setPalette(selectedPalette);
			Q_EMIT playerSelected(indexMap[widget]);
			return;
		}
	}
}

void TeamView::mouseReleaseEvent(QMouseEvent *event)
{
	for (auto widget : playerWidgets){
		QPointF localpos = event->localPos();
		QRect g = widget->geometry();
		bool contains = g.contains(QPoint(localpos.x(), localpos.y()));
		if (contains && indexMap.find(widget) != indexMap.end()){
			widget->setPalette(deselectedPalette);
			return;
		}
	}
}