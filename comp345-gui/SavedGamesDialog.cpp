#include "stdafx.h"
#include "SavedGamesDialog.h"

SavedGamesDialog::SavedGamesDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	QPalette pal = palette();
	pal.setColor(QPalette::Background, Qt::darkBlue);
	this->setAutoFillBackground(true);
	this->setPalette(pal);
	selectedRow = 0;
	stringModel = new QStringListModel(this);
	auto files = pan::Game::allSavedGames();
	if (files.empty()){
		ui.buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
	}
	QStringList list;
	for (const auto& f : files){
		list << QString::fromStdString(f);
	}
	ui.listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	stringModel->setStringList(list);
	ui.listView->setModel(stringModel);
	ui.listView->setSelectionMode(QAbstractItemView::SingleSelection);

	QItemSelectionModel *selectionModel = ui.listView->selectionModel();
	connect(selectionModel, SIGNAL(currentRowChanged(QModelIndex, QModelIndex)),
		this, SLOT(on_listViewIndexChanged(QModelIndex, QModelIndex)));
}

SavedGamesDialog::~SavedGamesDialog()
{
	if (stringModel)
		delete stringModel;
}


void SavedGamesDialog::on_buttonBox_accepted()
{
	qDebug() << "Accepted";
	QDialog::accept();
	Q_EMIT selectedSavedGame(stringModel->stringList()[selectedRow]);
}

void SavedGamesDialog::on_buttonBox_rejected()
{
	qDebug() << "Rejected";
	QDialog::reject();
}

void SavedGamesDialog::on_listViewIndexChanged(const QModelIndex & current, const QModelIndex & previous)
{
	qDebug() << "Changed" << std::to_string(current.row()).c_str();
	selectedRow = current.row();
}

