#include "stdafx.h"
#include "GaveOverView.h"
#include "Resources.h"

GaveOverView::GaveOverView(QWidget *parent)
	: QDialog(parent, Qt::CustomizeWindowHint | Qt::WindowTitleHint)
{
	ui.setupUi(this);
	QPalette pal = palette();
	pal.setColor(QPalette::Background, Qt::darkBlue);
	this->setAutoFillBackground(true);
	this->setPalette(pal);
	QPalette buttonPal = palette();
	buttonPal.setColor(QPalette::ButtonText, Qt::white);
	buttonPal.setColor(QPalette::Button, Qt::darkBlue);
	ui.newGameButton->setAutoFillBackground(true);
	ui.quitButton->setAutoFillBackground(true);
	ui.newGameButton->setPalette(buttonPal);
	ui.quitButton->setPalette(buttonPal);
}

GaveOverView::~GaveOverView()
{
}

void GaveOverView::on_newGameButton_clicked()
{
	QDialog::accept();
	Q_EMIT gameOverViewSelected(true);
}

void GaveOverView::on_quitButton_clicked()
{
	QDialog::accept();
	Q_EMIT gameOverViewSelected(false);
}

void GaveOverView::setStatus(bool victory)
{
	ui.icon->setPixmap((victory ? Resources::getVictoryIcon() : Resources::getDefeatIcon()).scaled(ui.icon->width(), ui.icon->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void GaveOverView::reject()
{

}