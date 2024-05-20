#include "SelectMovieWindow.h"
#include "Movie.h"
#include <QMessageBox>

SelectMovieWindow::SelectMovieWindow(QPushButton* acceptButton, QTableWidget* tableWidget) : MovieTableWidget(tableWidget)
{
	this->selectedMovieId = -1;
	this->acceptButton = acceptButton;
	this->tableWidget = tableWidget;

    connect(acceptButton, SIGNAL(clicked()), this, SLOT(onAcceptButtonClicked()));
}

SelectMovieWindow::~SelectMovieWindow()
{
	delete acceptButton;
	delete tableWidget;
}

void SelectMovieWindow::setSelectedMovieId() 
{
    int currentRow = tableWidget->currentRow();
    if (currentRow != -1) {
        QTableWidgetItem* titleItem = tableWidget->item(currentRow, 0);
        QTableWidgetItem* directorItem = tableWidget->item(currentRow, 1);
        QTableWidgetItem* typeItem = tableWidget->item(currentRow, 2);
        QTableWidgetItem* durationItem = tableWidget->item(currentRow, 3);

        if (titleItem && directorItem && typeItem && durationItem) {
            QString title = titleItem->text();
            QString director = directorItem->text();
            QString type = typeItem->text();
            int duration = durationItem->text().toInt();

            Movie movie(title, director, type, duration);
            this->selectedMovieId = movieDatabase.getMovieId(movie);

            if (this->selectedMovieId == -1) {
				QMessageBox::critical(nullptr, "Database Error", "Failed to retrieve movie ID!");
            }
            return;
        }
        else {
            QMessageBox::critical(nullptr, "Database Error", "Failed to retrieve movie ID!");
            return;
        }
    }
    QMessageBox::information(nullptr, "Movie Not Selected", "You need to select one movie");
    return;
}

void SelectMovieWindow::onAcceptButtonClicked() {
    setSelectedMovieId();
    QMessageBox::information(nullptr, "Movie Selected", "Movie selected successfully!");

}