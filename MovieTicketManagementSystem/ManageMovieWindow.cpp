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

    //connect the save button to the addMovie slot
    connect(addButton, SIGNAL(clicked()), this, SLOT(addMovie()));

    //connection that on selected item in the list view, the fields are updated with the movie details
    connect(movieTableWidgetElement, SIGNAL(clicked(const QModelIndex&)), this, SLOT(onMovieSelected(const QModelIndex&)));

    //connection that on clicking the remove button, the movie is removed from the database
    connect(removeButtonElement, SIGNAL(clicked()), this, SLOT(removeMovie()));
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

void ManageMovieWindow::updateFields(const Movie& movie)
{

	titleEdit->setText(movie.getTitle());
	director->setText(movie.getDirector());
	type->setCurrentText(movie.getType());
    durationTime->setText(QString::number(movie.getDuration()));

}

void ManageMovieWindow::updateFields()
{
    titleEdit->clear();
    director->clear();
    type->setCurrentIndex(0);
    durationTime->clear();
}

void ManageMovieWindow::setLimitationsOnFields()
{

    //TODO 
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

        //Set Movies in the tableWidget
        movieTableWidget->setMoviesInTableWidget();

        updateFields();

    }
    catch (const std::invalid_argument& e) {
        // exception handling
        QMessageBox::critical(this, "Error", e.what());
    }
}

void ManageMovieWindow::removeMovie()
{
    QList<QTableWidgetItem*> selectedItems = movieTableWidget->getTableWidget()->selectedItems();

    // check if any row is selected
    if (selectedItems.isEmpty()) {
        QMessageBox::information(this, "Information", "Select a movie to remove.");
        return;
    }

    // Pobranie indeksu zaznaczonego wiersza
    int rowIndex = selectedItems.first()->row();

    // get data from the selected row
    QString title = movieTableWidget->getTableWidget()->item(rowIndex, 0)->text();
    QString director = movieTableWidget->getTableWidget()->item(rowIndex, 1)->text();
    QString type = movieTableWidget->getTableWidget()->item(rowIndex, 2)->text();
    int duration = movieTableWidget->getTableWidget()->item(rowIndex, 3)->text().toInt();


    Movie movie(title, director, type, duration);

    if (!movieDatabase.deleteMovie(movie)) {
        QMessageBox::critical(this, "Error", "Failed to remove movie.");
    }


    // update the tableWidget
    movieTableWidget->setMoviesInTableWidget();

    // clear the input fields
    updateFields();

}