#ifndef PLAYERHANDVIEW_H
#define PLAYERHANDVIEW_H

#include <QWidget>
#include <core\detail\Deck.h>
#include <core\Cards.h>
#include "ui_PlayerHandView.h"

/**
*	@class A widget to display the player's cards
*	@author Hrachya Hakobyan
*/
class PlayerHandView : public QWidget
{
	Q_OBJECT

public:
	PlayerHandView(QWidget *parent = 0);
	~PlayerHandView();

	void update(const pan::detail::Deck<pan::CardBasePtr>&);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
Q_SIGNALS:
	void cardSelected(int index);
	void cardDetailsSelected(int index);
private:
	Ui::PlayerHandView ui;
	QVector<QLabel*> cardViews;
	QMap<QLabel*, int> indexMap;
	QPalette selectedPalette;
	QPalette deselectedPalette;
};

#endif // PLAYERHANDVIEW_H
