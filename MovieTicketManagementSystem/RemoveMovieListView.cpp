#include "RemoveMovieListView.h"
#include <QMessageBox>
#include <QPushButton>


RemoveMovieListView::RemoveMovieListView(QListView* listView, QPushButton* pushButtonElement)
	: MovieListView(listView)  // Lista inicjatorów konstruktora
{
	pushButton = pushButtonElement;

	// £¹czenie sygna³u clicked przycisku z slotem removeSelectedItem
	connect(pushButton, SIGNAL(clicked()), this, SLOT(removeSelectedItem()));
}

RemoveMovieListView::~RemoveMovieListView()
{
		delete listModel;
}


void RemoveMovieListView::removeSelectedItem()
{

	QMessageBox::information(this, "Movie removed", "The movie has been removed successfully");

		// Pobranie indeksu zaznaczonego elementu
	QModelIndex selectedIndex = listView->currentIndex();

	// Sprawdzenie czy jakiœ element jest zaznaczony
	if (!selectedIndex.isValid())
	{
		QMessageBox::warning(this, "No item selected", "Please select an item to remove");
		return;
	}

	// Pobranie informacji o zaznaczonym elemencie
	QString selectedMovieInfo = listModel->data(selectedIndex, Qt::DisplayRole).toString();

	// Pobranie tytu³u filmu
	QString selectedMovieTitle = selectedMovieInfo.split(" - ")[0];

	// Usuniêcie filmu z bazy danych
	//movieDatabase.removeMovie(selectedMovieTitle);

	// Usuniêcie filmu z listy
	listModel->removeRow(selectedIndex.row());

	// Aktualizacja widoku QListView
	listView->update();

}
