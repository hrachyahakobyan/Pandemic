#include "stdafx.h"
#include "NewGameDialog.h"
#include "Resources.h"

NewGameDialog::NewGameDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	QPalette pal = palette();
	pal.setColor(QPalette::Background, Qt::darkBlue);
	this->setAutoFillBackground(true);
	this->setPalette(pal);
	this->on_beginnerButton_clicked();
	roleLabels.push_back(qMakePair(pan::Roles::CPlanner, ui.role1));
	roleLabels.push_back(qMakePair(pan::Roles::Dispatcher, ui.role2));
	roleLabels.push_back(qMakePair(pan::Roles::Medic, ui.role3));
	roleLabels.push_back(qMakePair(pan::Roles::OperationsExpert, ui.role4));
	roleLabels.push_back(qMakePair(pan::Roles::QSpecialist, ui.role5));
	roleLabels.push_back(qMakePair(pan::Roles::Researcher, ui.role6));
	roleLabels.push_back(qMakePair(pan::Roles::Scientist, ui.role7));
	playerLabels.push_back(ui.player1);
	playerLabels.push_back(ui.player2);
	playerLabels.push_back(ui.player3);
	playerLabels.push_back(ui.player4);
	lineEdits.push_back(ui.player1Name);
	lineEdits.push_back(ui.player2Name);
	lineEdits.push_back(ui.player3Name);
	lineEdits.push_back(ui.player4Name);
	for (auto p : roleLabels){
		p.second->setPixmap(Resources::avatarForRole(p.first).scaled(p.second->width(), p.second->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	}
	for (auto l : lineEdits){
		l->setMaxLength(10);
	}
	updatePlayerLabels();
}

NewGameDialog::~NewGameDialog()
{
}

void NewGameDialog::on_beginnerButton_clicked()
{
	ui.standardButton->setPalette(QPalette(Qt::gray));
	ui.heroicButton->setPalette(QPalette(Qt::gray));
	difficulty = Beginner;
	ui.beginnerButton->setPalette(QPalette(Qt::green));
}

void NewGameDialog::on_standardButton_clicked()
{
	ui.beginnerButton->setPalette(QPalette(Qt::gray));
	ui.heroicButton->setPalette(QPalette(Qt::gray));
	difficulty = Standard;
	ui.standardButton->setPalette(QPalette(Qt::green));
}

void NewGameDialog::on_heroicButton_clicked()
{
	ui.standardButton->setPalette(QPalette(Qt::gray));
	ui.beginnerButton->setPalette(QPalette(Qt::gray));
	difficulty = Heroic;
	ui.heroicButton->setPalette(QPalette(Qt::green));
}

void NewGameDialog::on_buttonBox_accepted()
{
	qDebug() << "New game dialog accept";
	QDialog::accept();
	for (std::size_t i = 0; i < players.size(); i++){
		players[i].first = lineEdits[i]->text().toStdString();
	}
	pan::Settings s;
	if (difficulty == Beginner)
		s = pan::Settings::Beginner(players.size());
	else if (difficulty == Standard)
		s = pan::Settings::Standard(players.size());
	else
		s = pan::Settings::Heroic(players.size());
	Q_EMIT selectedSettingsAndPlayers(s, players);
}

void NewGameDialog::on_buttonBox_rejected()
{
	qDebug() << "New game dialog reject";
	QDialog::reject();
}

void NewGameDialog::mousePressEvent(QMouseEvent *event)
{
	for (auto t : roleLabels){
		QPointF localpos = event->localPos();
		QPoint pt = ui.widget_2->mapFromParent(QPoint(localpos.x(), localpos.y()));
		auto label = t.second;
		QRect g = label->geometry();
		bool contains = g.contains(pt);
		if (contains){
			selectedRole(t.first);
			return;
		}
	}

	for (std::size_t i = 0; i < playerLabels.size(); i++){
		QPointF localpos = event->localPos();
		QPoint ptOuter = ui.widget_3->mapFromParent(QPoint(localpos.x(), localpos.y()));
		auto label = playerLabels[i];
		QPoint ptInner = label->parentWidget()->mapFromParent(ptOuter);
		QRect g = label->geometry();
		bool contains = g.contains(ptInner);
		if (contains){
			deselectedPlayer(i);
			return;
		}
	}
}

void NewGameDialog::selectedRole(pan::Roles role)
{
	if (players.size() == 4) return;
	for (const auto& p : players){
		if (p.second == role)
			return;
	}
	players.push_back(std::make_pair("", role));
	if (players.size() > 1){
		ui.buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
	}
	updatePlayerLabels();
}

void NewGameDialog::deselectedPlayer(std::size_t index)
{
	if (index >= players.size()) return;
	players.erase(players.begin() + index);
	updatePlayerLabels();
}

void NewGameDialog::updatePlayerLabels()
{
	ui.buttonBox->button(QDialogButtonBox::Ok)->setEnabled(players.size() > 1);
	for (std::size_t i = players.size(); i < playerLabels.size(); i++){
		QLabel* p = playerLabels[i];
		p->setPixmap(Resources::getAvatarBlank().scaled(p->width(), p->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	}
	for (std::size_t i = 0; i < std::min(std::size_t(playerLabels.size()), players.size()); i++){
		playerLabels[i]->setPixmap(Resources::avatarForRole(players[i].second).scaled(playerLabels[i]->width(), playerLabels[i]->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	}
}