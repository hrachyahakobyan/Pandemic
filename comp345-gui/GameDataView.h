#ifndef GAMEDATAVIEW_H
#define GAMEDATAVIEW_H

#include <QWidget>
#include "ui_GameDataView.h"

/**
*	@class A widget to display game related data
*	@author Hrachya Hakobyan
*/
class GameDataView : public QWidget
{
	Q_OBJECT

public:
	GameDataView(QWidget *parent = 0);
	~GameDataView();

	void update(const pan::GameData& data);
	void update(const pan::DeckData& data);
private:
	Ui::GameDataView ui;
};

#endif // GAMEDATAVIEW_H
