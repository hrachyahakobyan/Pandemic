#include "stdafx.h"
#include "Pandemic.h"
#include "MapView.h"
#include "CityDetailsView.h"
#include "Resources.h"
#include "ActionSelectView.h"
#include <core\detail\Observer.h>

Pandemic::Pandemic(QWidget *parent)
	: QMainWindow(parent), menu(NULL), initialized(false)
{
	using namespace pan;
	ui.setupUi(this);
	//this->setStyleSheet("background-color:#0d0238;");
	connect(ui.mapView, SIGNAL(cityItemSelected(pan::CityIndex)), this, SLOT(on_cityItemSelected(pan::CityIndex)));
	connect(ui.actionSelectView, SIGNAL(actionSelected(pan::ActionType)), this, SLOT(on_actionSelectViewSelected(pan::ActionType)));
	connect(ui.teamView, SIGNAL(playerSelected(pan::PlayerIndex)), this, SLOT(on_teamViewPlayerSelected(pan::PlayerIndex)));
	connect(ui.handView, SIGNAL(cardSelected(int)), this, SLOT(on_handViewCardSelected(int)));
	connect(ui.diseaseDetailsView, SIGNAL(diseaseSelected(pan::DiseaseType)), this, SLOT(on_diseaseViewDiseaseSelected(pan::DiseaseType)));
}

Pandemic::~Pandemic()
{
	if (menu)
		delete menu;
}

void Pandemic::start()
{
	menu = new MainMenu(this);
	connect(menu, SIGNAL(constructedGame(pan::Game&)), this, SLOT(on_mainMenuConstructedGame(pan::Game&)));
	int status = menu->exec();
	delete menu;
	menu = NULL;
}

void Pandemic::on_mainMenuConstructedGame(pan::Game& g)
{
	initialize(std::move(g));
}

void Pandemic::initialize(pan::Game&& g)
{
	if (initialized)
		return;
	initialized = true;
	using namespace pan;
	game = std::move(g);
	game.initialize();
	ui.mapView->update(this->game.getMap());
	ui.gameDataView->update(this->game.getGameData());
	ui.gameDataView->update(this->game.getDeckData());
	ui.teamView->update(game.getPlayerData().players);
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
	logger.reset(new GlobalLogger("log.txt"));
}

void Pandemic::on_cityItemSelected(pan::CityIndex index)
{
	qDebug() << "Selected city index " << index;
	actionBuilder.selectCity(index);
	executeAction();
}

void Pandemic::on_teamViewPlayerSelected(pan::PlayerIndex index)
{
	actionBuilder.selectPlayer(index);
	qDebug() << "Selected player index " << index;
	executeAction();
}

void Pandemic::on_handViewCardSelected(int card)
{
	actionBuilder.selectCard(card);
	qDebug() << "Selected card " << card;
	executeAction();
}

void Pandemic::updateActiveUser()
{
	ui.activeUserAvatar->setPixmap(Resources::avatarForRole(game.getActivePlayer().getRole().role).scaled(ui.activeUserAvatar->width(), ui.activeUserAvatar->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	ui.activeUserActions->setText(QString::fromStdString(std::to_string(game.getPlayerData().actionCounter)));
	ui.activeUserName->setText(QString::fromStdString(game.getActivePlayer().getName()));
	ui.handView->update(this->game.getActivePlayer().getCards());
	ui.stageLabel->setText(playerStageToString(game.getStage()));
}

void Pandemic::on_actionSelectViewSelected(pan::ActionType type)
{
	actionBuilder.selectAction(type);
	actionBuilder.selectPlayer(game.getActivePlayerIndex());
	qDebug() << "Selected action " << pan::ActionTypeDescriptions.at(type).c_str();
	executeAction();
}

void Pandemic::on_diseaseViewDiseaseSelected(pan::DiseaseType type)
{
	actionBuilder.selectDisease(type);
	qDebug() << "Selected disease " << type;
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
	ui.diseaseDetailsView->update(n->data.diseases);
}

void Pandemic::handleDeckDataUpdateNotification(std::shared_ptr<pan::DeckDataUpdateNotification> data)
{
	ui.gameDataView->update(data->data);
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

QString Pandemic::playerStageToString(pan::PlayerStage s) const
{
	using pan::PlayerStage;
	if (s == PlayerStage::Act)
		return QString("Act");
	if (s == PlayerStage::Discard)
		return QString("Discard");
	if (s == PlayerStage::Draw)
		return QString("Draw");
	return QString("Infect");
}

void Pandemic::closeEvent(QCloseEvent *event)
{
	QMessageBox::StandardButton resBtn = QMessageBox::question(this, "Pandemic",
		tr("Are you sure?\n"),
		QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
		QMessageBox::Yes);
	if (resBtn != QMessageBox::Yes) {
		event->ignore();
	}
	else {
		game.save("Autosave");
		event->accept();
	}
}