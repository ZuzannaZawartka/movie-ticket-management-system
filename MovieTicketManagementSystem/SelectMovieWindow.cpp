#include "SelectMovieWindow.h"
#include "Movie.h"
#include <QMessageBox>

SelectMovieWindow::SelectMovieWindow(QPushButton* acceptButton, QTableWidget* tableWidget) : MovieTableWidget(tableWidget)
{
    this->selectedMovieId = -1;
    this->acceptButton = acceptButton;
    this->tableWidget = tableWidget;

    // Connect the signal emitted when the user selects a movie to the onSelectItem slot
    connect(tableWidget->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this, SLOT(onSelectItem()));

    // Connect the signal emitted when the user clicks the accept button to the onAcceptButton slot
    connect(acceptButton, SIGNAL(clicked()), this, SLOT(onAcceptButton()));


}

SelectMovieWindow::~SelectMovieWindow()
{
    delete acceptButton;
    delete tableWidget;
}

bool SelectMovieWindow::isMovieSelected()
{
    if (this->selectedMovieId == -1) {
        return false;
    }
    return true;
}

int SelectMovieWindow::setSelectedMovieId()
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

            return this->selectedMovieId;
        }
        return -1;
    }
    return -1;
}


int SelectMovieWindow::getSelectedMovieId()
{
    return this->selectedMovieId;
}

void SelectMovieWindow::resetSelectedMovieId()
{
   this->selectedMovieId = -1;
   this->tableWidget->clearSelection();
   
}

void SelectMovieWindow::onSelectItem() {
    setSelectedMovieId();
    if (setSelectedMovieId() == -1) {
        QMessageBox::information(nullptr, "Movie Not Selected", "You need to select one movie.");
    }

}

void SelectMovieWindow::onAcceptButton() {
    if (selectedMovieId != -1) {
        emit movieSelected(selectedMovieId);
    }
    else {
        QMessageBox::information(nullptr, "Movie Not Selected", "You need to select one movie.");
    }

    resetSelectedMovieId();
}