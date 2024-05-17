#include "ManageMovieWindow.h"
#include "Movie.h"
#include <QMessageBox>
#include "MovieListView.h"

ManageMovieWindow::ManageMovieWindow(QTextEdit* titleEditElement, QTextEdit* directorElement, QComboBox* typeElement, QLineEdit* durationTimeElement, QPushButton* saveButtonElement, QPushButton* addButtonElement, QPushButton* removeButtonElement, QTableWidget* movieTableWidgetElement)
{

    titleEdit = titleEditElement;
    director = directorElement;
    type = typeElement;
    durationTime = durationTimeElement;
    saveButton = saveButtonElement;
    addButton = addButtonElement;
    removeButton = removeButtonElement;
    movieTableWidget = new MovieListView(movieTableWidgetElement);

    //connect the save button to the addMovie slot
    connect(addButton, SIGNAL(clicked()), this, SLOT(addMovie()));

    //connection that on selected item in the list view, the fields are updated with the movie details
    connect(movieTableWidgetElement, SIGNAL(clicked(const QModelIndex&)), this, SLOT(onMovieSelected(const QModelIndex&)));
}

void ManageMovieWindow::onMovieSelected(const QModelIndex& index)
{
    if (!index.isValid()) {
        return;
    }

    QTableWidgetItem* titleItem = movieTableWidget->getTableWidget()->item(index.row(), 0);
    QTableWidgetItem* directorItem = movieTableWidget->getTableWidget()->item(index.row(), 1);
    QTableWidgetItem* typeItem = movieTableWidget->getTableWidget()->item(index.row(), 2);
    QTableWidgetItem* durationItem = movieTableWidget->getTableWidget()->item(index.row(), 3);

    if (titleItem && directorItem && typeItem && durationItem) {
        QString titleStr = titleItem->text();
        QString directorStr = directorItem->text();
        QString typeStr = typeItem->text();
        QString durationStr = durationItem->text();

        titleEdit->setText(titleStr);
        director->setText(directorStr);
        type->setCurrentText(typeStr);
        durationTime->setText(durationStr);
    }
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

void ManageMovieWindow::updateFieldsWithMovie(const Movie& movie)
{
	//Update the fields with the movie details
	titleEdit->setText(movie.getTitle());
	director->setText(movie.getDirector());
	type->setCurrentText(movie.getType());
	durationTime->setText(QString::number(movie.getDuration()));
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

        movieTableWidget->setMoviesInListView();

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