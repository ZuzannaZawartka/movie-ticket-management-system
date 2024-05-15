#include "AddMovieWindow.h"
#include "Movie.h"
#include <QMessageBox>
#include "MovieListView.h"

AddMovieWindow::AddMovieWindow(QTextEdit* titleEditElement, QTextEdit* directorElement, QComboBox* typeElement, QLineEdit* durationTimeElement, QPushButton* addButtonElement, MovieListView* movieListViewElement)
{

    titleEdit = titleEditElement;
    director = directorElement;
    type = typeElement;
    durationTime = durationTimeElement;
    addButton = addButtonElement;
    movieListView = movieListViewElement;


    connect(addButton, SIGNAL(clicked()), this, SLOT(addMovie()));
}


bool AddMovieWindow::checkInputFields()
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

void AddMovieWindow::setLimitationsOnFields()
{

    //TODO 
    //set limitations on the fields
    durationTime->setValidator(new QIntValidator(0, 500, this));
}

void AddMovieWindow::addMovie()
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