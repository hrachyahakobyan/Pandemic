#ifndef DISEASEDETAILSVIEW_H
#define DISEASEDETAILSVIEW_H

#include <QWidget>
#include "ui_DiseaseDetailsView.h"

class DiseaseDetailsView : public QWidget
{
	Q_OBJECT

public:
	DiseaseDetailsView(QWidget *parent = 0);
	~DiseaseDetailsView();
	void update(const std::vector<pan::Disease>&);
private:
	Ui::DiseaseDetailsView ui;
	QVector<QLabel*> vialLabels;
};

#endif // DISEASEDETAILSVIEW_H
