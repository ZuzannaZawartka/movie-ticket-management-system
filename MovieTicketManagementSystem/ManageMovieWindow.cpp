#include "ManageMovieWindow.h"
#include "Movie.h"
#include <QMessageBox>
#include "MovieListView.h"

ManageMovieWindow::ManageMovieWindow(QTextEdit* titleEditElement, QTextEdit* directorElement, QComboBox* typeElement,
    QLineEdit* durationTimeElement, QPushButton* removeButtonElement, QPushButton* addNewButtonElement, QPushButton* saveButtonElement, MovieListView* movieListViewElement)
{

    titleEdit = titleEditElement;
    director = directorElement;
    type = typeElement;
    durationTime = durationTimeElement;
    addNewButton = addNewButtonElement;
    saveButton = saveButtonElement;
    removeButton = removeButtonElement;
    movieListView = movieListViewElement;


    connect(addNewButton, SIGNAL(clicked()), this, SLOT(addMovie()));
}


bool ManageMovieWindow::checkInputFields()
{
    //TODO 

    //Check if the input fields are valid
    if (titleEdit->toPlainText().isEmpty() || director->toPlainText().isEmpty() || type->currentText().isEmpty() || durationTime->text().isEmpty()) {
        throw std::invalid_argument("All fields must be filled out.");
    }

    // check if the duration is a valid number
    bool ok;
    int durationInt = durationTime->text().toInt(&ok);
    if (!ok) {
        throw std::invalid_argument("Duration must be a valid number.");
    }
}

void ManageMovieWindow::setLimitationsOnFields()
{

    //TODO 
    //set limitations on the fields
    durationTime->setValidator(new QIntValidator(0, 500, this));
}

void ManageMovieWindow::addMovie()
{
    try {
        // Check if the input fields are valid
        checkInputFields();

        // Get the values from the input fields
        QString titleStr = titleEdit->toPlainText();
        QString directorStr = director->toPlainText();
        QString typeStr = type->currentText();
        int durationInt = durationTime->text().toInt();

        // Add the movie to the database
        movieDatabase.addMovie(Movie(titleStr, directorStr, typeStr, durationInt));

        movieListView->setMoviesInListView();

        // Clear the fields after adding the movie
        titleEdit->clear();
        director->clear();
        type->setCurrentIndex(0); // Set the first item in the combobox
        durationTime->clear();


    }
    catch (const std::invalid_argument& e) {
        // exception handling
        QMessageBox::critical(this, "Error", e.what());
    }
}

void ManageMovieWindow::removeSelectedItem()
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