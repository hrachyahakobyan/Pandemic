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

private:
	Ui::ActionSelectView ui;
};

#endif // ACTIONSELECTVIEW_H
