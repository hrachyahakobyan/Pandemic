#include "stdafx.h"
#include "CardDetailsView.h"
#include "Resources.h"

CardDetailsView::CardDetailsView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

CardDetailsView::~CardDetailsView()
{
}


void CardDetailsView::update(const pan::CardBase& card)
{
	ui.label->setPixmap(Resources::pixmapForCard(card).scaled(ui.label->width(), ui.label->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void CardDetailsView::update(pan::Roles role)
{
	ui.label->setPixmap(Resources::cardForRole(role).scaled(ui.label->width(), ui.label->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void CardDetailsView::on_okButton_clicked()
{
	this->hide();
}