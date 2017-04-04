#include "stdafx.h"
#include "Pandemic.h"
#include "MapView.h"
#include "CityDetailsView.h"
#include "Resources.h"
#include "ActionSelectView.h"
#include <core\detail\Observer.h>

Pandemic::Pandemic(pan::Game&& g, QWidget *parent)
	: QMainWindow(parent), game(std::move(g))
{
	ui.setupUi(this);
	//this->setStyleSheet("background-color:#0d0238;");
	connect(ui.mapView, SIGNAL(cityItemSelected(pan::CityIndex)), this, SLOT(on_cityItemSelected(pan::CityIndex)));
	connect(ui.actionSelectView, SIGNAL(actionSelected(pan::ActionType)), this, SLOT(on_actionSelectViewSelected(pan::ActionType)));
	ui.mapView->update(this->game.getMap());
	ui.gameDataView->update(this->game.getGameData());
	updateActiveUser();

	pan::detail::Observer<Pandemic, pan::CityUpdateNotification> cityObserver(*this, &Pandemic::handleCityUpdateNotification);
	pan::detail::Observer<Pandemic, pan::DeckDataUpdateNotification> deckObserver(*this, &Pandemic::handleDeckDataUpdateNotification);
	pan::detail::Observer<Pandemic, pan::GameDataUpdateNotification> gameObserver(*this, &Pandemic::handleGameDataUpdateNotification);
	pan::detail::Observer<Pandemic, pan::PlayerDataUpdateNotification> playersObserver(*this, &Pandemic::handlePlayerDataUpdateNotification);
	pan::detail::Observer<Pandemic, pan::PlayerUpdateNotification> playerObserver(*this, &Pandemic::handlePlayerUpdateNotification);
	pan::detail::NotificationCenter::defaultCenter().addObserver(cityObserver);
	pan::detail::NotificationCenter::defaultCenter().addObserver(deckObserver);
	pan::detail::NotificationCenter::defaultCenter().addObserver(gameObserver);
	pan::detail::NotificationCenter::defaultCenter().addObserver(playersObserver);
	pan::detail::NotificationCenter::defaultCenter().addObserver(playerObserver);
}

void Pandemic::on_cityItemSelected(pan::CityIndex index)
{
	actionBuilder.selectCity(index);
	executeAction();
}

void Pandemic::updateActiveUser()
{
	ui.activeUserAvatar->setPixmap(Resources::avatarForRole(game.getActivePlayer().getRole().role).scaled(ui.activeUserAvatar->width(), ui.activeUserAvatar->height(), Qt::KeepAspectRatio));
	ui.activeUserActions->setText(QString::fromStdString(std::to_string(game.getPlayerData().actionCounter)));
	ui.activeUserName->setText(QString::fromStdString(game.getActivePlayer().getName()));
	ui.handView->update(this->game.getPlayer(0).getCards());
}

void Pandemic::on_actionSelectViewSelected(pan::ActionType type)
{
	actionBuilder.selectAction(type);
	actionBuilder.selectPlayer(game.getActivePlayerIndex());
	executeAction();
}

void Pandemic::executeAction()
{
	if (actionBuilder.isReady()){
		game.addAction(actionBuilder.getAction());
		actionBuilder.reset();
		game.execute();
	}
}

void Pandemic::handleCityUpdateNotification(std::shared_ptr<pan::CityUpdateNotification> n)
{
	ui.mapView->update(n->city, n->index);
}

void Pandemic::handleGameDataUpdateNotification(std::shared_ptr<pan::GameDataUpdateNotification> n)
{
	ui.gameDataView->update(n->data);
}

void Pandemic::handleDeckDataUpdateNotification(std::shared_ptr<pan::DeckDataUpdateNotification>)
{

}

void Pandemic::handlePlayerDataUpdateNotification(std::shared_ptr<pan::PlayerDataUpdateNotification>)
{
	this->updateActiveUser();
}

void Pandemic::handlePlayerUpdateNotification(std::shared_ptr<pan::PlayerUpdateNotification> n)
{
	if (n->player.index == game.getActivePlayerIndex()){
		this->updateActiveUser();
	}
}