#ifndef PLAYERHANDVIEW_H
#define PLAYERHANDVIEW_H

#include <QWidget>
#include <core\detail\Deck.h>
#include <core\Cards.h>
#include "CardView.h"
#include "ui_PlayerHandView.h"

class PlayerHandView : public QWidget
{
	Q_OBJECT

public:
	PlayerHandView(QWidget *parent = 0);
	~PlayerHandView();

	void update(const pan::detail::Deck<pan::CardBasePtr>&);

private:
	Ui::PlayerHandView ui;
	QVector<CardView*> cardViews;
};

#endif // PLAYERHANDVIEW_H
