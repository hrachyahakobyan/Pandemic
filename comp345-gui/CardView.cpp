#include "stdafx.h"
#include "CardView.h"
#include "Resources.h"

CardView::CardView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

CardView::~CardView()
{
}


void CardView::update(const pan::CardBase& card)
{
	this->card.reset(card.clone());
	ui.cardImage->setPixmap(Resources::pixmapForCard(card).scaled(ui.cardImage->width(), ui.cardImage->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}