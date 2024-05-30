#include "ManageMovieWindow.h"
#include "Movie.h"
#include <QMessageBox>
#include "MovieTableWidget.h"

ManageMovieWindow::ManageMovieWindow(QTextEdit* titleEditElement, QTextEdit* directorElement, QComboBox* typeElement, QLineEdit* durationTimeElement, QPushButton* saveButtonElement, QPushButton* addButtonElement, QPushButton* removeButtonElement, QTableWidget* movieTableWidgetElement)
{

    titleEdit = titleEditElement;
    director = directorElement;
    type = typeElement;
    durationTime = durationTimeElement;
    saveButton = saveButtonElement;
    addButton = addButtonElement;
    removeButton = removeButtonElement;
    movieTableWidget = new MovieTableWidget(movieTableWidgetElement);
    selectedMovieId = -1; //initialize the selected movie id to -1

    //connect the save button to the addMovie slot
    connect(addButton, SIGNAL(clicked()), this, SLOT(addMovie()));

    //connection that on selected item in the list view, the fields are updated with the movie details
    connect(movieTableWidgetElement, SIGNAL(clicked(const QModelIndex&)), this, SLOT(onMovieSelected(const QModelIndex&)));

    //connection that on clicking the remove button, the movie is removed from the database
    connect(removeButtonElement, SIGNAL(clicked()), this, SLOT(removeMovie()));

    //connection that on clicking the save button, the movie is updated in the database
    connect(saveButton, SIGNAL(clicked()), this, SLOT(updateMovie()));
}

ManageMovieWindow::~ManageMovieWindow()
{
    
	delete titleEdit;
	delete director;
	delete type;
	delete durationTime;
	delete saveButton;
	delete addButton;
	delete removeButton;
	delete movieTableWidget;
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

        Movie movie(titleStr, directorStr, typeStr, durationStr.toInt());

        selectedMovieId = movieDatabase.getMovieId(movie);//get the id of the selected movie

        updateFields(movie);
    }
}


bool ManageMovieWindow::checkInputFields()
{
    try {
        // Check if the input fields are valid, not empty
        if (titleEdit->toPlainText().isEmpty() || director->toPlainText().isEmpty() || type->currentText().isEmpty() || durationTime->text().isEmpty()) {
            throw std::invalid_argument("All fields must be filled out.");
        }

        // check if the duration is a valid number
        bool ok;
        durationTime->text().toInt(&ok);
        if (!ok) {
            throw std::invalid_argument("Duration must be a valid number.");
        }

        return true; //if all fields are valid
    }
    catch (const std::invalid_argument& e) {
        // if an exception is thrown, display an error message
        QMessageBox::critical(this, "Error", e.what());
        return false;
    }
}

void ManageMovieWindow::updateFields(const Movie& movie)
{

	titleEdit->setText(movie.getTitle());
	director->setText(movie.getDirector());
	type->setCurrentText(movie.getType());
    durationTime->setText(QString::number(movie.getDuration()));

}

Movie ManageMovieWindow::getMovieFromFields()
{
    // Check if the input fields are valid
    checkInputFields();

    // Get the values from the input fields
    QString titleStr = titleEdit->toPlainText();
    QString directorStr = director->toPlainText();
    QString typeStr = type->currentText();
    int durationInt = durationTime->text().toInt();

    Movie movie(titleStr, directorStr, typeStr, durationInt);

    return movie;
}



void ManageMovieWindow::updateFields()
{
    titleEdit->clear();
    director->clear();
    type->setCurrentIndex(0);
    durationTime->clear();

    // set the selected movie id to -1
    selectedMovieId = -1;

    // clear the selection in the tableWidget
    movieTableWidget->getTableWidget()->clearSelection();
}

void ManageMovieWindow::setLimitationsOnFields()
{
    //TODO 
    durationTime->setValidator(new QIntValidator(0, 500, this));
}

void ManageMovieWindow::addMovie()
{
    if (!checkInputFields()) {
        return;
    }
    // Get the movie from the input fields
    Movie movie = getMovieFromFields();

    // Add the movie to the database
    movieDatabase.addMovie(movie);

    //Set Movies in the tableWidget
    movieTableWidget->setMoviesInTableWidget();

    updateFields(); 
    emit moviesChanged();
}

void ManageMovieWindow::removeMovie()
{
    QList<QTableWidgetItem*> selectedItems = movieTableWidget->getTableWidget()->selectedItems();

    // check if any row is selected
    if (selectedItems.isEmpty()) {
        QMessageBox::information(this, "Information", "Select a movie to remove.");
        return;
    }

    // get the row index of the selected item
    int rowIndex = selectedItems.first()->row();

    // get data from the selected row
    QString title = movieTableWidget->getTableWidget()->item(rowIndex, 0)->text();
    QString director = movieTableWidget->getTableWidget()->item(rowIndex, 1)->text();
    QString type = movieTableWidget->getTableWidget()->item(rowIndex, 2)->text();
    int duration = movieTableWidget->getTableWidget()->item(rowIndex, 3)->text().toInt();


    Movie movie(title, director, type, duration);

    // remove the movie from the database
    if (!movieDatabase.deleteMovie(movie)) return;

    // update the tableWidget
    movieTableWidget->setMoviesInTableWidget();

    // clear the input fields
    updateFields();
    emit moviesChanged();
}

void ManageMovieWindow::updateMovie()
{
    if (selectedMovieId == -1) {
        QMessageBox::information(this, "Information", "Select a movie to update.");
        return;
    }

    // Get the movie from the input fields
    Movie newMovie = getMovieFromFields();

    // Get the old movie from the database
    Movie oldMovie = movieDatabase.getMovieById(selectedMovieId);

    // Update the movie in the database
    if (!movieDatabase.updateMovie(oldMovie, newMovie)) return;

    // update the tableWidget
    movieTableWidget->setMoviesInTableWidget();

    // clear the input fields
    updateFields();
}
