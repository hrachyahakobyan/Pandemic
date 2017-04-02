#pragma once

#include <QWidget>
#include "ui_CardView.h"

class CardView : public QWidget
{
	Q_OBJECT

public:
	CardView(QWidget *parent = Q_NULLPTR);
	~CardView();

	const pan::CardBase& getCard() const { return *card.get(); }

	void update(const pan::CardBase& card);

private:
	Ui::CardView ui;
	pan::CardBasePtr card;
};
