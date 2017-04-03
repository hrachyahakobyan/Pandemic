#ifndef ACTIONSELECTVIEW_H
#define ACTIONSELECTVIEW_H

#include <QWidget>
#include "ui_ActionSelectView.h"

class ActionSelectView : public QWidget
{
	Q_OBJECT

public:
	ActionSelectView(QWidget *parent = 0);
	~ActionSelectView();
	void mousePressEvent(QMouseEvent *event);
Q_SIGNALS:
	void actionSelected(pan::ActionType type);
private:
	Ui::ActionSelectView ui;
	QMap<QWidget*, pan::ActionType> widgetActions;
};

#endif // ACTIONSELECTVIEW_H
