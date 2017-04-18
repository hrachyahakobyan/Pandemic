#pragma once

#include <QDialog>
#include "ui_NewGameDialog.h"

/**
*	@class A dialog to select options for a new game
*	@author Hrachya Hakobyan
*/
class NewGameDialog : public QDialog
{
	Q_OBJECT

public:
	NewGameDialog(QWidget *parent = Q_NULLPTR);
	~NewGameDialog();
	void mousePressEvent(QMouseEvent *event);
public Q_SLOTS:
	void on_beginnerButton_clicked();
	void on_standardButton_clicked();
	void on_heroicButton_clicked();
	void on_buttonBox_accepted();
	void on_buttonBox_rejected();
Q_SIGNALS:
	void selectedSettingsAndPlayers(const pan::Settings&, const std::vector<std::pair<std::string, pan::Roles>>&);
private:
	enum GameDifficulty{
		Beginner, Standard, Heroic
	};
	Ui::NewGameDialog ui;
	std::vector<std::pair<std::string, pan::Roles>> players;
	QVector<QPair<pan::Roles, QLabel*>> roleLabels;
	QVector<QLabel*> playerLabels;
	QVector<QLineEdit*> lineEdits;
	GameDifficulty difficulty;

	void selectedRole(pan::Roles role);
	void deselectedPlayer(std::size_t index);
	void updatePlayerLabels();
};
