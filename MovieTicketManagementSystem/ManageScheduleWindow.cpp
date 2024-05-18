#include "ManageScheduleWindow.h"
#include "Schedule.h"
#include <QMessageBox>
#include "ScheduleTableWidget.h"

ManageScheduleWindow::ManageScheduleWindow(QComboBox* titleEditElement, QDateEdit* dateEditElement, QTimeEdit* timeEditElement, QLineEdit* durationTimeElement, QPushButton* addButtonElement, QTableWidget* scheduleTableWidgetElement)
{

    titleEdit = titleEditElement;
    dateEdit = dateEditElement;
    timeEdit = timeEditElement;
    durationTime = durationTimeElement;
    addButton = addButtonElement;
    scheduleTableWidget = new ScheduleTableWidget(scheduleTableWidgetElement);
    selectedScheduleId = -1; //initialize the selected movie id to -1

    // Pobierz wszystkie filmy z bazy danych filmów
    QList<Movie> allMovies = movieDatabase.getAllMovies();

    // Wyczyœæ ComboBox, aby upewniæ siê, ¿e jest pusty przed dodaniem nowych elementów
    titleEdit->clear();

    // Dodaj tytu³y filmów do ComboBoxa
    for (const Movie& movie : allMovies) {
        titleEdit->addItem(movie.getTitle());
    }

    //connect the save button to the addSchedule slot
    connect(addButton, SIGNAL(clicked()), this, SLOT(addNewSchedule()));

}

ManageScheduleWindow::~ManageScheduleWindow()
{

    delete titleEdit;
    delete dateEdit;
    delete timeEdit;
    delete durationTime;
    delete addButton;
    delete scheduleTableWidget;
}

void ManageScheduleWindow::onScheduleSelected(const QModelIndex& index)
{
    if (!index.isValid()) {
        return;
    }

    QTableWidgetItem* titleItem = scheduleTableWidget->getTableWidget()->item(index.row(), 0);
    QTableWidgetItem* dateItem = scheduleTableWidget->getTableWidget()->item(index.row(), 1);
    QTableWidgetItem* timeItem = scheduleTableWidget->getTableWidget()->item(index.row(), 2);
    QTableWidgetItem* durationItem = scheduleTableWidget->getTableWidget()->item(index.row(), 3);

    if (titleItem && dateItem && timeItem && durationItem) 
    {
        QString movieTitle = titleItem->text();
        QDate date = QDate::fromString(dateItem->text(), "yyyy-MM-dd");
        QTime time = QTime::fromString(timeItem->text(), "HH:mm:ss");
        QString durationStr = durationItem->text();
        Movie movie = movieDatabase.getMovieByTitle(movieTitle);
        int movieId = movieDatabase.getMovieId(movie);

        Schedule schedule(movieId, date, time, durationStr.toInt());

        selectedScheduleId = scheduleDatabase.getScheduleId(schedule);//get the id of the selected movie

        updateFields(schedule);
    }
}


bool ManageScheduleWindow::checkInputFields()
{
    try {
        // SprawdŸ, czy wszystkie pola wejœciowe s¹ poprawnie wype³nione
        if (titleEdit->currentText().isEmpty() || dateEdit->text().isEmpty() || timeEdit->text().isEmpty() || durationTime->text().isEmpty()) {
            throw std::invalid_argument("All fields must be filled out.");
        }

        // SprawdŸ, czy czas trwania jest poprawn¹ liczb¹
        bool ok;
        int duration = durationTime->text().toInt(&ok);
        if (!ok || duration <= 0) {
            throw std::invalid_argument("Duration must be a positive integer.");
        }

        // SprawdŸ, czy wybrana data jest poprawna
        QDate date = dateEdit->date();
        if (!date.isValid()) {
            throw std::invalid_argument("Invalid date.");
        }

        // SprawdŸ, czy wybrany czas jest poprawny
        QTime time = timeEdit->time();
        if (!time.isValid()) {
            throw std::invalid_argument("Invalid time.");
        }

        return true; // Jeœli wszystkie pola s¹ poprawne
    }
    catch (const std::invalid_argument& e) {
        // Jeœli zostanie zg³oszony wyj¹tek, wyœwietl komunikat o b³êdzie
        QMessageBox::critical(this, "Error", e.what());
        return false;
    }
}

void ManageScheduleWindow::updateFields(const Schedule& schedule)
{
    
    Movie movie = movieDatabase.getMovieById(schedule.getMovieId());
    titleEdit->setCurrentText(movie.getTitle());
    dateEdit->setDate(schedule.getDate());
    timeEdit->setTime(schedule.getTime());
    durationTime->setText(QString::number(schedule.getDurationMinutes()));

}

Schedule ManageScheduleWindow::getScheduleFromFields()
{
    // Check if the input fields are valid
    checkInputFields();

    // Get the values from the input fields
    QString movieTitle = titleEdit->currentText();
    Movie movie = movieDatabase.getMovieByTitle(movieTitle);
    int movieId = movieDatabase.getMovieId(movie);
    QDate date = dateEdit->date();
    QTime time = timeEdit->time();
    int durationInt = durationTime->text().toInt();

    Schedule schedule(movieId, date, time, durationInt);

    return schedule;
}



void ManageScheduleWindow::updateFields()
{
    titleEdit->setCurrentIndex(0);
    dateEdit->setDate(QDate(0,0,0));
    timeEdit->setTime(QTime(0,0));
    durationTime->clear();

    // set the selected movie id to -1
    selectedScheduleId = -1;

    // clear the selection in the tableWidget
    scheduleTableWidget->getTableWidget()->clearSelection();
}

void ManageScheduleWindow::addNewSchedule()
{
    // Get the movie from the input fields
    Schedule schedule = getScheduleFromFields();

    // Add the movie to the database
    scheduleDatabase.addSchedule(schedule);

    //Set Movies in the tableWidget
    scheduleTableWidget->setSchedulesInTableWidget();

    updateFields();
}

