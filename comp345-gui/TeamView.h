#ifndef TEAMVIEW_H
#define TEAMVIEW_H

#include <QWidget>
#include "ui_TeamView.h"

class TeamView : public QWidget
{
	Q_OBJECT

public:
	TeamView(QWidget *parent = 0);
	~TeamView();
	void update(const std::vector<pan::PlayerPtr>& players);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
Q_SIGNALS:
	void playerSelected(pan::PlayerIndex index);
	void playerDetailsSelected(pan::PlayerIndex index);
private:
	Ui::TeamView ui;
	QMap<QWidget*, pan::PlayerIndex> indexMap;
	QVector<QLabel*> playerWidgets;
	QPalette selectedPalette;
	QPalette deselectedPalette;
};

#endif // TEAMVIEW_H
