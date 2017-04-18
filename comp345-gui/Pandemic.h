#pragma once

#include <QSound>
#include <QtWidgets/QMainWindow>
#include "ui_Pandemic.h"
#include "ActionBuilder.h"
#include "MainMenu.h"
#include "GaveOverView.h"
#include "CardDetailsView.h"

/**
*	@class The main window, i.e. the controller
*	@author Hrachya Hakobyan
*/
class Pandemic : public QMainWindow
{
	Q_OBJECT

public:
	Pandemic(QWidget *parent = Q_NULLPTR);
	~Pandemic();
	void start();
	void closeEvent(QCloseEvent *event);
	void keyPressEvent(QKeyEvent *event);

public Q_SLOTS:
	void on_cityItemSelected(pan::CityIndex);
	void on_actionSelectViewSelected(pan::ActionType);
	void on_teamViewPlayerSelected(pan::PlayerIndex);
	void on_handViewCardSelected(int);
	void on_diseaseViewDiseaseSelected(pan::DiseaseType);
	void on_mainMenuConstructedGame(pan::Game& g);
	void on_gameOverViewSelected(bool newGame);
	void on_teamViewPlayerDetailsSelected(pan::PlayerIndex);
	void on_handViewCardDetailsSelected(int);
private:
	void initialize(pan::Game&&);
	bool initialized;
	Ui::PandemicClass ui;
	pan::Game game;
	ActionBuilder actionBuilder;
	void updateSelectedUser();
	void executeAction();
	std::shared_ptr<pan::LoggerBase> logger;

	void handleCityUpdateNotification(std::shared_ptr<pan::CityUpdateNotification>);
	void handleGameDataUpdateNotification(std::shared_ptr<pan::GameDataUpdateNotification>);
	void handleDeckDataUpdateNotification(std::shared_ptr<pan::DeckDataUpdateNotification>);
	void handlePlayerDataUpdateNotification(std::shared_ptr<pan::PlayerDataUpdateNotification>);
	void handlePlayerUpdateNotification(std::shared_ptr<pan::PlayerUpdateNotification>);

	QString playerStageToString(pan::PlayerStage s) const;

	MainMenu* menu;
	GaveOverView* gameOverView;
	CardDetailsView* cardDetailsView;
	pan::PlayerIndex selectedUser;
};
