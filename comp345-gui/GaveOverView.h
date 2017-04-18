#pragma once

#include <QDialog>
#include "ui_GaveOverView.h"

/**
*	@class A widget to display at the end of the game
*	@author Hrachya Hakobyan
*/
class GaveOverView : public QDialog
{
	Q_OBJECT
public:
	GaveOverView(QWidget *parent = Q_NULLPTR);
	~GaveOverView();
	void setStatus(bool victory);
	void reject();
public Q_SLOTS:
	void on_newGameButton_clicked();
	void on_quitButton_clicked();
Q_SIGNALS:
	void gameOverViewSelected(bool newGame);
private:
	Ui::GaveOverView ui;
};
