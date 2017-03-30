#ifndef CITYDETAILSVIEW_H
#define CITYDETAILSVIEW_H

#include <QWidget>
#include "ui_CityDetailsView.h"

class CityDetailsView : public QWidget
{
	Q_OBJECT

public:
	CityDetailsView(QWidget *parent = 0);
	~CityDetailsView();

	void update(const pan::City& city);

private:
	Ui::CityDetailsView ui;
	QPixmap researchOkPixmap;
	QPixmap researchNoPixamp;
	QVector<QPixmap> regionPixmaps;
};

#endif // CITYDETAILSVIEW_H
