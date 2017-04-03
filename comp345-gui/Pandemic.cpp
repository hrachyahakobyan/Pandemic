#include "stdafx.h"
#include "Pandemic.h"
#include "MapView.h"
#include "CityDetailsView.h"
#include "Resources.h"
#include "ActionSelectView.h"

Pandemic::Pandemic(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->setStyleSheet("background-color:#0d0238;");
	connect(ui.mapView, SIGNAL(cityItemSelected(pan::CityIndex)), this, SLOT(on_cityItemSelected(pan::CityIndex)));
	connect(ui.actionSelectView, SIGNAL(actionSelected(pan::ActionType)), this, SLOT(on_actionSelectViewSelected(pan::ActionType)));
}

void Pandemic::update(pan::Game&& game)
{
	this->game = std::move(game);
	ui.mapView->update(this->game.getMap());
	ui.gameDataView->update(this->game.getGameData());
	updateActiveUser();
}

void Pandemic::on_cityItemSelected(pan::CityIndex index)
{
}

void Pandemic::on_actionSelectViewSelected(pan::ActionType type)
{

}

void Pandemic::updateActiveUser()
{
	ui.activeUserAvatar->setPixmap(Resources::avatarForRole(game.getActivePlayer().getRole().role).scaled(ui.activeUserAvatar->width(), ui.activeUserAvatar->height(), Qt::KeepAspectRatio));
	ui.activeUserActions->setText(QString::fromStdString(std::to_string(4 - game.getPlayerData().actionCounter)));
	ui.activeUserName->setText(QString::fromStdString(game.getActivePlayer().getName()));
	ui.handView->update(this->game.getPlayer(0).getCards());
}

