#ifndef PANDEMIC_H
#define PANDEMIC_H

#include <QtWidgets/QMainWindow>
#include "ui_pandemic.h"

class Pandemic : public QMainWindow
{
	Q_OBJECT

public:
	Pandemic(QWidget *parent = 0);
	~Pandemic();

private:
	Ui::PandemicClass ui;
};

#endif // PANDEMIC_H
