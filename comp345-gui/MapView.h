#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QWidget>
#include "ui_MapView.h"

class MapView : public QWidget
{
	Q_OBJECT

public:
	MapView(QWidget *parent = 0);
	~MapView();

private:
	Ui::MapView ui;
	QImage mapImage;
	QGraphicsScene* mapScene;
};

#endif // MAPVIEW_H
