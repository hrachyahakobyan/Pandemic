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
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
Q_SIGNALS:
	void diseaseSelected(pan::DiseaseType type);
private:
	Ui::DiseaseDetailsView ui;
	QVector<std::tuple<pan::DiseaseType,QLabel*, QLabel*>> labels;
	QPalette selectedPalette;
	QPalette deselectedPalette;
};

#endif // DISEASEDETAILSVIEW_H
