#include "stdafx.h"
#include "Pandemic.h"
#include "MapView.h"
#include "CityDetailsView.h"
#include "Resources.h"
#include "ActionSelectView.h"
#include <core\detail\Observer.h>

Pandemic::Pandemic(QWidget *parent)
	: QMainWindow(parent), 
	menu(NULL),
	gameOverView(NULL), 
	cardDetailsView(NULL),
	initialized(false)
{
	using namespace pan;
	ui.setupUi(this);
	QPalette pal = palette();
	pal.setColor(QPalette::Background, Qt::darkBlue);
	this->setAutoFillBackground(true);
	this->setPalette(pal);
	ui.tabWidget->setAutoFillBackground(true);
	ui.tabWidget->setPalette(pal);
	ui.tabWidget->tabBar()->setTabTextColor(0, Qt::white);
	ui.tabWidget->tabBar()->setTabTextColor(1, Qt::white);
	ui.tabWidget->tabBar()->setTabTextColor(2, Qt::white);
	QPalette labelPal = palette();
	labelPal.setColor(QPalette::WindowText, Qt::white);
	ui.activeUserName->setPalette(labelPal);
	ui.activeUserActions->setPalette(labelPal);
	ui.stageLabel->setPalette(labelPal);
	ui.label->setPalette(labelPal);
	ui.label_2->setPalette(labelPal);
	connect(ui.mapView, SIGNAL(cityItemSelected(pan::CityIndex)), this, SLOT(on_cityItemSelected(pan::CityIndex)));
	connect(ui.actionSelectView, SIGNAL(actionSelected(pan::ActionType)), this, SLOT(on_actionSelectViewSelected(pan::ActionType)));
	connect(ui.teamView, SIGNAL(playerSelected(pan::PlayerIndex)), this, SLOT(on_teamViewPlayerSelected(pan::PlayerIndex)));
	connect(ui.handView, SIGNAL(cardSelected(int)), this, SLOT(on_handViewCardSelected(int)));
	connect(ui.diseaseDetailsView, SIGNAL(diseaseSelected(pan::DiseaseType)), this, SLOT(on_diseaseViewDiseaseSelected(pan::DiseaseType)));
	connect(ui.teamView, SIGNAL(playerDetailsSelected(pan::PlayerIndex)), this, SLOT(on_teamViewPlayerDetailsSelected(pan::PlayerIndex)));
	connect(ui.handView, SIGNAL(cardDetailsSelected(int)), this, SLOT(on_handViewCardDetailsSelected(int)));
}

Pandemic::~Pandemic()
{
}

void Pandemic::start()
{
	Resources::playSoundtrack();
	if (!menu){
		menu = new MainMenu(this);
		connect(menu, SIGNAL(constructedGame(pan::Game&)), this, SLOT(on_mainMenuConstructedGame(pan::Game&)));
	}
	QGraphicsBlurEffect* blur = new QGraphicsBlurEffect();
	blur->setBlurRadius(10);
	blur->setBlurHints(QGraphicsBlurEffect::PerformanceHint);
	this->setGraphicsEffect(blur);
	int status = menu->exec();
}

void Pandemic::on_mainMenuConstructedGame(pan::Game& g)
{
	this->setGraphicsEffect(NULL);
	initialize(std::move(g));
}

void Pandemic::initialize(pan::Game&& g)
{
	if (initialized)
		return;
	initialized = true;
	using namespace pan;
	actionBuilder.reset();
	game = std::move(g);
	game.initialize();
	ui.mapView->update(this->game.getMap());
	ui.gameDataView->update(this->game.getGameData());
	ui.gameDataView->update(this->game.getDeckData());
	ui.teamView->update(game.getPlayerData().players);
	ui.diseaseDetailsView->update(game.getGameData().diseases);
	selectedUser = game.getActivePlayerIndex();
	actionBuilder.setActivePlayer(selectedUser);
	updateSelectedUser();

	static bool registeredNotifications = false;
	if (!registeredNotifications){
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
		registeredNotifications = true;
	}

	std::string dateString = pan::LoggerBase::getDateString();
	std::string fileName = "log_" + dateString + ".log";
	try{
		logger.reset();
		logger.reset(new GlobalLogger(fileName));
	}
	catch (...){
		qDebug() << "Failed to create a logger ";
	}
}

void Pandemic::on_cityItemSelected(pan::CityIndex index)
{
	if (!game.isInitialized() || game.isOver()) return;
	qDebug() << "Selected city index " << index;
	actionBuilder.selectCity(index);
	executeAction();
}

void Pandemic::on_teamViewPlayerSelected(pan::PlayerIndex index)
{
	if (!game.isInitialized() || game.isOver()) return;
	actionBuilder.selectPlayer(index);
	qDebug() << "Selected player index " << index;
	selectedUser = index;
	updateSelectedUser();
	executeAction();
}

void Pandemic::on_handViewCardSelected(int index)
{
	if (!game.isInitialized() || game.isOver()) return;
	if (selectedUser != game.getActivePlayerIndex()) return;
	const pan::CardBase& card = *game.getActivePlayer().getCards()[index];
	actionBuilder.selectCard(index, card);
	qDebug() << "Selected card " << index;
	executeAction();
}

void Pandemic::on_actionSelectViewSelected(pan::ActionType type)
{
	if (!game.isInitialized() || game.isOver()) return;
	actionBuilder.selectAction(type);
	actionBuilder.selectPlayer(game.getActivePlayerIndex());
	qDebug() << "Selected action " << pan::ActionTypeDescriptions.at(type).c_str();
	executeAction();
}

void Pandemic::on_diseaseViewDiseaseSelected(pan::DiseaseType type)
{
	if (!game.isInitialized() || game.isOver()) return;
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
	if (n->data.state == pan::GameState::Victory || n->data.state == pan::GameState::Defeat){
		if (!gameOverView){
			gameOverView = new GaveOverView(this);
			connect(gameOverView, SIGNAL(gameOverViewSelected(bool)), this, SLOT(on_gameOverViewSelected(bool)));
		}
		if (gameOverView->isActiveWindow())
			return;
		if (this->graphicsEffect() == NULL){
			QGraphicsBlurEffect* blur = new QGraphicsBlurEffect();
			blur->setBlurRadius(10);
			blur->setBlurHints(QGraphicsBlurEffect::PerformanceHint);
			this->setGraphicsEffect(blur);
		}
		gameOverView->show();
		gameOverView->setStatus(n->data.state == pan::GameState::Victory ? true : false);
	}
}

void Pandemic::on_gameOverViewSelected(bool newGame)
{
	if (newGame){
		initialized = false;
		this->start();
	}
	else {
		this->close();
	}
}

void Pandemic::handleDeckDataUpdateNotification(std::shared_ptr<pan::DeckDataUpdateNotification> data)
{
	ui.gameDataView->update(data->data);
}

void Pandemic::handlePlayerDataUpdateNotification(std::shared_ptr<pan::PlayerDataUpdateNotification>)
{
	this->selectedUser = game.getActivePlayerIndex();
	actionBuilder.setActivePlayer(this->selectedUser);
	this->updateSelectedUser();
}

void Pandemic::handlePlayerUpdateNotification(std::shared_ptr<pan::PlayerUpdateNotification> n)
{
	if (n->player.index == this->selectedUser){
		this->updateSelectedUser();
	}
}

void Pandemic::updateSelectedUser()
{
	bool isActive = (selectedUser == game.getActivePlayerIndex());
	ui.activeUserAvatar->setPixmap(Resources::avatarForRole(game.getPlayer(selectedUser).getRole().role).scaled(ui.activeUserAvatar->width(), ui.activeUserAvatar->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	ui.activeUserActions->setText(isActive ? QString::fromStdString(std::to_string(game.getPlayerData().actionCounter)) : QString("-"));
	ui.activeUserName->setText(QString::fromStdString(game.getPlayer(selectedUser).getName()));
	ui.handView->update(this->game.getPlayer(selectedUser).getCards());
	ui.stageLabel->setText(isActive ? playerStageToString(game.getStage()) : QString("-"));
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

void Pandemic::keyPressEvent(QKeyEvent *event)
{
	if (this->isVisible() && event->key() == Qt::Key::Key_Escape){
		this->close();
	}
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
		if (game.isInitialized() && !game.isOver()){
			std::string date = pan::LoggerBase::getDateString();
			std::string fileName = "autosave_" + date + ".pan";
			game.save(fileName);
		}
		event->accept();
	}
}

void Pandemic::on_teamViewPlayerDetailsSelected(pan::PlayerIndex index)
{
	if (!cardDetailsView){
		cardDetailsView = new CardDetailsView(this);
		cardDetailsView->move(QPoint(20, 20));
	}
	cardDetailsView->show();
	cardDetailsView->update(game.getPlayer(index).getRole().role);
}

void Pandemic::on_handViewCardDetailsSelected(int index)
{
	if (!cardDetailsView){
		cardDetailsView = new CardDetailsView(this);
		cardDetailsView->move(QPoint(20, 20));
	}
	cardDetailsView->show();
	cardDetailsView->update(*game.getActivePlayer().getCards()[index]);
}