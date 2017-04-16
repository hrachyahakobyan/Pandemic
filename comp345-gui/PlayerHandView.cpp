#include "stdafx.h"
#include "PlayerHandView.h"
#include "Resources.h"

PlayerHandView::PlayerHandView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	selectedPalette = palette();
	deselectedPalette = palette();
	selectedPalette.setColor(QPalette::Background, Qt::blue);
	deselectedPalette.setColor(QPalette::Background, Qt::darkBlue);
	cardViews.push_back(ui.card0);
	cardViews.push_back(ui.card1);
	cardViews.push_back(ui.card2);
	cardViews.push_back(ui.card3);
	cardViews.push_back(ui.card4);
	cardViews.push_back(ui.card5);
	cardViews.push_back(ui.card6);
	cardViews.push_back(ui.card7);
	cardViews.push_back(ui.card8);
}

PlayerHandView::~PlayerHandView()
{
}


void PlayerHandView::update(const pan::detail::Deck<pan::CardBasePtr>& deck)
{
	for (auto card : cardViews){
		card->clear();
		card->setAutoFillBackground(true);
	}
	indexMap.clear();
	for (std::size_t i = 0; i < std::min(int(deck.size()), cardViews.size()); i++){
		cardViews[i]->setPixmap(Resources::pixmapForCard(*deck[i]).scaled(cardViews[i]->width(), cardViews[i]->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
		indexMap[cardViews[i]] = int(i);
	}
}


void PlayerHandView::mousePressEvent(QMouseEvent *event)
{
	for (auto w : cardViews){
		QPointF localpos = event->localPos();
		QRect g = w->geometry();
		bool contains = g.contains(QPoint(localpos.x(), localpos.y()));
		if (contains && indexMap.find(w) != indexMap.end()){
			if (event->button() == Qt::RightButton){
				Q_EMIT cardDetailsSelected(indexMap[w]);
			}
			else {
				w->setPalette(selectedPalette);
				Q_EMIT cardSelected(indexMap[w]);
			}
			return;
		}
	}
}

void PlayerHandView::mouseReleaseEvent(QMouseEvent *event)
{
	for (auto key : cardViews){
		QPointF localpos = event->localPos();
		QRect g = key->geometry();
		bool contains = g.contains(QPoint(localpos.x(), localpos.y()));
		if (contains){
			key->setPalette(deselectedPalette);
			return;
		}
	}
}