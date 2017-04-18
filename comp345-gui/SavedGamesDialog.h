#pragma once

#include <QDialog>
#include "ui_SavedGamesDialog.h"

/**
*	@class A dialog to load a saved game
*	@author Hrachya Hakobyan
*/
class SavedGamesDialog : public QDialog
{
	Q_OBJECT

public:
	SavedGamesDialog(QWidget *parent = Q_NULLPTR);
	~SavedGamesDialog();
public Q_SLOTS:
	void on_buttonBox_rejected();
	void on_buttonBox_accepted();
	void on_listViewIndexChanged(const QModelIndex & current, const QModelIndex & previous);
Q_SIGNALS:
	void selectedSavedGame(const QString& name);
private:
	Ui::SavedGamesDialog ui;
	QStringListModel* stringModel;
	int selectedRow;
};
