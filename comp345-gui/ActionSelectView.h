#ifndef ACTIONSELECTVIEW_H
#define ACTIONSELECTVIEW_H

#include <QWidget>
#include "ui_ActionSelectView.h"

/**
*	@class A widget to select actions
*	@author Hrachya Hakobyan
*/
class ActionSelectView : public QWidget
{
	Q_OBJECT

public:
	ActionSelectView(QWidget *parent = 0);
	~ActionSelectView();
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
Q_SIGNALS:
	void actionSelected(pan::ActionType type);
private:
	Ui::ActionSelectView ui;
	QMap<QWidget*, QPair<QLabel*, pan::ActionType>> widgetActions;
	QPalette selectedPalette;
	QPalette deselectedPalette;
};

#endif // ACTIONSELECTVIEW_H
