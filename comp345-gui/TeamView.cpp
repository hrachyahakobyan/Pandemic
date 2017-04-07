#include "stdafx.h"
#include "TeamView.h"
#include "Resources.h"

TeamView::TeamView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	playerWidgets.push_back(qMakePair(ui.p1Widget, ui.p1Label));
	playerWidgets.push_back(qMakePair(ui.p2Widget, ui.p2Label));
	playerWidgets.push_back(qMakePair(ui.p3Widget, ui.p3Label));
	playerWidgets.push_back(qMakePair(ui.p4Widget, ui.p4Label));
}

TeamView::~TeamView()
{

}

void TeamView::update(const std::vector<pan::PlayerPtr>& players)
{
	indexMap.clear();
	for (auto pair : playerWidgets){
		pair.second->clear();
	}
	for (int i = 0; i < players.size(); i++){
		indexMap[playerWidgets[i].first] = players[i]->index;
		playerWidgets[i].second->setPixmap(Resources::avatarForRole(players[i]->getRole().role).scaled(100, 100, Qt::KeepAspectRatio));
	}
}

void TeamView::mousePressEvent(QMouseEvent *event)
{
	for (auto widget : playerWidgets){
		QPointF localpos = event->localPos();
		QRect g = widget.first->geometry();
		bool contains = g.contains(QPoint(localpos.x(), localpos.y()));
		if (contains && indexMap.find(widget.first) != indexMap.end()){
			widget.second->setStyleSheet("border: 3px solid green");
			Q_EMIT playerSelected(indexMap[widget.first]);
			return;
		}
	}
}

void TeamView::mouseReleaseEvent(QMouseEvent *event)
{
	for (auto widget : playerWidgets){
		QPointF localpos = event->localPos();
		QRect g = widget.first->geometry();
		bool contains = g.contains(QPoint(localpos.x(), localpos.y()));
		if (contains && indexMap.find(widget.first) != indexMap.end()){
			widget.second->setStyleSheet("border: 0px solid black");
			return;
		}
	}
}