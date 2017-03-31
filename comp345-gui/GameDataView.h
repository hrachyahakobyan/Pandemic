#ifndef GAMEDATAVIEW_H
#define GAMEDATAVIEW_H

#include <QWidget>
#include "ui_GameDataView.h"

class GameDataView : public QWidget
{
	Q_OBJECT

public:
	GameDataView(QWidget *parent = 0);
	~GameDataView();

	void update(const pan::GameData& data);

private:
	Ui::GameDataView ui;
};

#endif // GAMEDATAVIEW_H
