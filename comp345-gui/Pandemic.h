#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Pandemic.h"
#include "ActionBuilder.h"

class Pandemic : public QMainWindow
{
	Q_OBJECT

public:
	Pandemic(QWidget *parent = Q_NULLPTR);
	void update(pan::Game&&);
public Q_SLOTS:
	void on_cityItemSelected(pan::CityIndex);
	void on_actionSelectViewSelected(pan::ActionType);
	void on_teamViewPlayerSelected(pan::PlayerIndex);
	void on_handViewCardSelected(int);
	void on_diseaseViewDiseaseSelected(pan::DiseaseType);
private:
	Ui::PandemicClass ui;
	pan::Game game;
	ActionBuilder actionBuilder;
	void updateActiveUser();
	void executeAction();
	std::shared_ptr<pan::LoggerBase> logger;

	void handleCityUpdateNotification(std::shared_ptr<pan::CityUpdateNotification>);
	void handleGameDataUpdateNotification(std::shared_ptr<pan::GameDataUpdateNotification>);
	void handleDeckDataUpdateNotification(std::shared_ptr<pan::DeckDataUpdateNotification>);
	void handlePlayerDataUpdateNotification(std::shared_ptr<pan::PlayerDataUpdateNotification>);
	void handlePlayerUpdateNotification(std::shared_ptr<pan::PlayerUpdateNotification>);

	QString playerStageToString(pan::PlayerStage s) const;
};
