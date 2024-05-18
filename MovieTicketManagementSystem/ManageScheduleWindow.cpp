#include "ManageScheduleWindow.h"
#include "Schedule.h"
#include <QMessageBox>
#include "ScheduleTableWidget.h"

ManageScheduleWindow::ManageScheduleWindow(QComboBox* titleEditElement, QDateEdit* dateEditElement, QTimeEdit* timeEditElement, QLineEdit* durationTimeElement, QPushButton* addButtonElement, QPushButton* removeButtonElement, QPushButton* editButtonElement, QTableWidget* scheduleTableWidgetElement)
{

    titleEdit = titleEditElement;
    dateEdit = dateEditElement;
    timeEdit = timeEditElement;
    durationTime = durationTimeElement;
    addButton = addButtonElement;
    removeButton = removeButtonElement;
    editButton = editButtonElement;
    scheduleTableWidget = new ScheduleTableWidget(scheduleTableWidgetElement);
    selectedScheduleId = -1; //initialize the selected movie id to -1

    setLimitationsOnFields();

    //Get all movie titles from movieDatabase
    QList<Movie> allMovies = movieDatabase.getAllMovies();

    //Clear QComboBox
    titleEdit->clear();

    //Add movie titles to QComboBox
    for (const Movie& movie : allMovies) {
        titleEdit->addItem(movie.getTitle());
    }

    //connect the save button to the addSchedule slot
    connect(addButton, SIGNAL(clicked()), this, SLOT(addNewSchedule()));
    //connect the remove button to removeSchedule slot
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeCurrentSchedule()));

    connect(editButton, SIGNAL(clicked()), this, SLOT(editCurrentSchedule()));

    connect(scheduleTableWidget, SIGNAL(clicked(const QModelIndex&)), this, SLOT(onScheduleSelected(const QModelIndex&)));
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
       
        if (titleEdit->currentText().isEmpty() || dateEdit->text().isEmpty() || timeEdit->text().isEmpty() || durationTime->text().isEmpty()) {
            throw std::invalid_argument("All fields must be filled out.");
        }

        // Check date
        if (dateEdit->date() < QDate::currentDate()) {
            throw std::invalid_argument("Wrong date input.");
        }

        // Check duration time
        bool ok;
        int duration = durationTime->text().toInt(&ok);
        if (!ok || duration <= 0 || duration > 500) {
            throw std::invalid_argument("Wrong duration time input.");
        }


        
        QDate date = dateEdit->date();
        if (!date.isValid()) {
            throw std::invalid_argument("Invalid date.");
        }

        QTime time = timeEdit->time();
        if (!time.isValid()) {
            throw std::invalid_argument("Invalid time.");
        }

        return true; 
    }
    catch (const std::invalid_argument& e) {
        
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

void ManageScheduleWindow::setLimitationsOnFields() 
{
    //TO DO (check if it's today's date - if true set limitation on timeEdit
    dateEdit->setMinimumDate(QDate::currentDate());
    durationTime->setValidator(new QIntValidator(0, 500, this));
}
void ManageScheduleWindow::editCurrentSchedule()
{
    if (!checkInputFields()) {
        return;
    }

    if (selectedScheduleId == -1) {
        QMessageBox::information(this, "Information", "Select a schedule to update.");
        return;
    }

    // Get the schedule from the input fields
    Schedule newSchedule = getScheduleFromFields();

    // Get the old schedule from the database
    Schedule oldSchedule = scheduleDatabase.getScheduleById(selectedScheduleId);

    // Update the schedule in the database
    if (!scheduleDatabase.updateSchedule(oldSchedule, newSchedule)) return;

    // update the tableWidget
    scheduleTableWidget->setSchedulesInTableWidget();

    // clear the input fields
    updateFields();
}

void ManageScheduleWindow::addNewSchedule()
{
    if (!checkInputFields()) {
        return; 
    }
    // Get the movie from the input fields
    Schedule schedule = getScheduleFromFields();

    // Add the movie to the database
    scheduleDatabase.addSchedule(schedule);

    //Set Movies in the tableWidget
    scheduleTableWidget->setSchedulesInTableWidget();

    updateFields();
}
void ManageScheduleWindow::removeCurrentSchedule()
{
    QList<QTableWidgetItem*> selectedItems = scheduleTableWidget->getTableWidget()->selectedItems();

    // check if any row is selected
    if (selectedItems.isEmpty()) {
        QMessageBox::information(this, "Information", "Select a schedule to remove.");
        return;
    }

    // get the row index of the selected item
    int rowIndex = selectedItems.first()->row();

    // get data from the selected row
    
    QString title = scheduleTableWidget->getTableWidget()->item(rowIndex, 0)->text();
    QString dateString = scheduleTableWidget->getTableWidget()->item(rowIndex, 1)->text();
    QString timeString = scheduleTableWidget->getTableWidget()->item(rowIndex, 2)->text();
    int duration = scheduleTableWidget->getTableWidget()->item(rowIndex, 3)->text().toInt();

    QDate date = QDate::fromString(dateString, "yyyy-MM-dd");
    QTime time = QTime::fromString(timeString, "HH:mm:ss");

    Movie movie = movieDatabase.getMovieByTitle(title);
    int movieId = movieDatabase.getMovieId(movie);
    
    Schedule schedule(movieId, date, time, duration);

    // remove the schedule from the database
    if (!scheduleDatabase.deleteSchedule(schedule)) return;

    // update the tableWidget
    scheduleTableWidget->setSchedulesInTableWidget();
    
    
    updateFields();
}
