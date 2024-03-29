#include "stdafx.h"
#include "MainMenu.h"

MainMenu::MainMenu(QWidget *parent)
	: QDialog(parent, Qt::CustomizeWindowHint | Qt::WindowTitleHint), savedGamesDialog(NULL), newGameDialog(NULL)
{
	ui.setupUi(this);
	QPalette pal = palette();
	pal.setColor(QPalette::Background, Qt::blue);
	this->setAutoFillBackground(true);
	this->setPalette(pal);
	QPalette buttonPal = palette();
	buttonPal.setColor(QPalette::ButtonText, Qt::white);
	buttonPal.setColor(QPalette::Button, Qt::darkBlue);
	ui.newButton->setAutoFillBackground(true);
	ui.continueButton->setAutoFillBackground(true);
	ui.newButton->setPalette(buttonPal);
	ui.continueButton->setPalette(buttonPal);
}

MainMenu::~MainMenu()
{
	if (savedGamesDialog)
		delete savedGamesDialog;
	if (newGameDialog)
		delete newGameDialog;
}

void MainMenu::on_newButton_clicked()
{
	qDebug() << "New";
	if (!newGameDialog){
		newGameDialog = new NewGameDialog(this);
		connect(newGameDialog, SIGNAL(selectedSettingsAndPlayers(const pan::Settings&, const std::vector<std::pair<std::string, pan::Roles>>&)),
			this, SLOT(on_newGameDialogSelectedSettingsAndPlayers(const pan::Settings&, const std::vector<std::pair<std::string, pan::Roles>>&)));
	}
	int status = newGameDialog->exec();
	qDebug() << "New game dialog status " << std::to_string(status).c_str();
}

void MainMenu::on_continueButton_clicked()
{
	qDebug() << "Continue";
	if (!savedGamesDialog){
		savedGamesDialog = new SavedGamesDialog(this);
		connect(savedGamesDialog, SIGNAL(selectedSavedGame(const QString&)),
			this, SLOT(on_savedGamesDialogSelectedGame(const QString&)));
	}
	int status = savedGamesDialog->exec();
	qDebug() << "Saved Games status " << std::to_string(status).c_str();
}

void MainMenu::on_savedGamesDialogSelectedGame(const QString& file)
{
	qDebug() << "Saved games dialog selected " << file;
	using namespace pan;
	Game g;
	if (Game::load(file.toStdString(), g) && !g.isOver()){
		delete savedGamesDialog;
		savedGamesDialog = NULL;
		QDialog::accept();
		Q_EMIT constructedGame(g);
	} else {
		QMessageBox msgBox;
		msgBox.setWindowTitle("Oops!");
		msgBox.setText("The save file seems corrupt... :(");
		msgBox.exec();
	}
}

void MainMenu::on_newGameDialogSelectedSettingsAndPlayers(const pan::Settings& s, const std::vector<std::pair<std::string, pan::Roles>>& p)
{
	qDebug() << "New game dialog selected " << s.description().c_str() << '\n' << "Player count: " << std::to_string(p.size()).c_str();
	using namespace pan;
	Game g(s, Map::pandemicMap());
	for (const auto& player : p){
		g.addPlayer(player.second, player.first);
	}
	delete newGameDialog;
	newGameDialog = NULL;
	QDialog::accept();
	Q_EMIT constructedGame(g);
}

void MainMenu::reject()
{

}