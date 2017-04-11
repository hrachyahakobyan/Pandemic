#ifndef MAINMENU_H
#define MAINMENU_H

#include <QDialog>
#include "ui_MainMenu.h"
#include "SavedGamesDialog.h"
#include "NewGameDialog.h"

class MainMenu : public QDialog
{
	Q_OBJECT

public:
	MainMenu(QWidget *parent = 0);
	~MainMenu();
public Q_SLOTS:
	void on_newButton_clicked();
	void on_continueButton_clicked();
	void on_savedGamesDialogSelectedGame(const QString& game);
	void on_newGameDialogSelectedSettingsAndPlayers(const pan::Settings&, const std::vector<std::pair<std::string, pan::Roles>>&);
Q_SIGNALS:
	void constructedGame(pan::Game& game);
private:
	Ui::MainMenu ui;
	SavedGamesDialog* savedGamesDialog;
	NewGameDialog* newGameDialog;
};

#endif // MAINMENU_H
