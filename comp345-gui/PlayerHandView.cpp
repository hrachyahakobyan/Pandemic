#include "stdafx.h"
#include "PlayerHandView.h"

PlayerHandView::PlayerHandView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//this->setStyleSheet("background-color:#0d0238;");
	cardViews.push_back(ui.card0);
	cardViews.push_back(ui.card1);
	cardViews.push_back(ui.card2);
	cardViews.push_back(ui.card3);
	cardViews.push_back(ui.card4);
	cardViews.push_back(ui.card5);
	cardViews.push_back(ui.card6);
	cardViews.push_back(ui.card7);
}

PlayerHandView::~PlayerHandView()
{
}


void PlayerHandView::update(const pan::detail::Deck<pan::CardBasePtr>& deck)
{
	for (std::size_t i = 0; i < std::min(int(deck.size()), cardViews.size()); i++){
		cardViews[i]->update(*deck[i]);
	}
}