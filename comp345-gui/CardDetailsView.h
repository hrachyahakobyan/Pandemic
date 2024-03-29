#pragma once

#include <QWidget>
#include "ui_CardDetailsView.h"


/**
*	@class A widget to display details of a specific card
*	@author Hrachya Hakobyan
*/
class CardDetailsView : public QWidget
{
	Q_OBJECT

public:
	CardDetailsView(QWidget *parent = Q_NULLPTR);
	~CardDetailsView();
	void update(const pan::CardBase& card);
	void update(pan::Roles role);
public Q_SLOTS:
	void on_okButton_clicked();
private:
	Ui::CardDetailsView ui;
};
