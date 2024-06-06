#include "ManageBookingWindow.h"
#include "Booking.h"
#include <QMessageBox>
#include "BookingTableWidget.h"

ManageBookingWindow::ManageBookingWindow(QComboBox* titleEditElement, QComboBox* dateTimeEditElement, QLineEdit* nameElement, QLineEdit* surnameElement, QLineEdit* EmailElement, QLineEdit* seatElement, QPushButton* removeButtonElement, QPushButton* editButtonElement, QTableWidget* bookingTableWidgetElement)
{
    titleEdit = titleEditElement;
    dateTimeEdit = dateTimeEditElement;
    name = nameElement;
    surname = surnameElement;
    Email = EmailElement;
    seat = seatElement;
    removeButton = removeButtonElement;
    editButton = editButtonElement;
    bookingTableWidget = new BookingTableWidget(bookingTableWidgetElement);
    selectedBookingId = -1; //initialize the selected booking id to -1

    
    refreshBookings();

    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeCurrentBooking()));
    connect(editButton, SIGNAL(clicked()), this, SLOT(editCurrentBooking()));
    connect(bookingTableWidget->getTableWidget(), &QTableWidget::clicked, this, &ManageBookingWindow::onBookingSelected);
    connect(titleEdit, &QComboBox::currentIndexChanged, this, &ManageBookingWindow::onTitleChanged);
   
}

ManageBookingWindow::~ManageBookingWindow()
{
    delete titleEdit;
    delete dateTimeEdit;
    delete name;
    delete surname;
    delete Email;
    delete bookingTableWidget;
}

void ManageBookingWindow::onTitleChanged()
{
    
    QString selectedTitle = titleEdit->currentText();

    dateTimeEdit->clear();

    if (selectedTitle.isEmpty()) {
        return;
    }

    Movie movie = movieDatabase.getMovieByTitle(selectedTitle);
    int movieId = movieDatabase.getMovieId(movie);

    QList<Schedule> movieSchedules = scheduleDatabase.getSchedulesByMovieId(movieId);

    for (const Schedule& schedule : movieSchedules) {
        dateTimeEdit->addItem(schedule.getDateTime().toString("ddd MMM dd HH:mm:ss yyyy"));
    }
}

void ManageBookingWindow::refreshBookings()
{
    bookingDatabase.removeInvalidBookings();

    QList<Schedule> allSchedules = scheduleDatabase.getAllSchedules();

    dateTimeEdit->clear();
    
    for (const Schedule& schedule : allSchedules) {
        dateTimeEdit->addItem(schedule.getDateTime().toString());
    }

    QList<Movie> allMovies = movieDatabase.getAllMovies();
    titleEdit->clear();

    for (const Movie& movie : allMovies) {
        titleEdit->addItem(movie.getTitle());
    }
    onTitleChanged();
    
    bookingTableWidget->setBookingsInTableWidget();
}

void ManageBookingWindow::onBookingSelected(const QModelIndex& index)
{
    if (!index.isValid()) {
        return;
    }

    QTableWidgetItem* titleItem = bookingTableWidget->getTableWidget()->item(index.row(), 0);
    QTableWidgetItem* dateItem = bookingTableWidget->getTableWidget()->item(index.row(), 1);
    QTableWidgetItem* nameItem = bookingTableWidget->getTableWidget()->item(index.row(), 2);
    QTableWidgetItem* surnameItem = bookingTableWidget->getTableWidget()->item(index.row(), 3);
    QTableWidgetItem* emailItem = bookingTableWidget->getTableWidget()->item(index.row(), 4);
    QTableWidgetItem* seatItem = bookingTableWidget->getTableWidget()->item(index.row(), 5);

    if (titleItem && dateItem && nameItem && surnameItem && emailItem && seatItem)
    {
        QString title = titleItem->text();
        QString dateTimeStr = dateItem->text();
        QDateTime dateTime = QDateTime::fromString(dateTimeStr, "ddd MMM dd HH:mm:ss yyyy");
        if (!dateTime.isValid()) {
            dateTime = QDateTime::fromString(dateTimeStr, "ddd MMM d HH:mm:ss yyyy");
        }
        QString nameText = nameItem->text();
        QString surnameText = surnameItem->text();
        QString emailText = emailItem->text();
        QString seatText = seatItem->text();

        Movie movie = movieDatabase.getMovieByTitle(title);
        Schedule schedule = scheduleDatabase.getScheduleByMovieAndDateTime(movieDatabase.getMovieId(movie), dateTime);

        Booking booking(movieDatabase.getMovieId(movie), scheduleDatabase.getScheduleId(schedule), seatText, nameText, surnameText, emailText);
        selectedBookingId = bookingDatabase.getBookingId(booking);
        updateFields(booking);

    }
}

bool ManageBookingWindow::checkInputFields()
{
    try {
        if (titleEdit->currentText().isEmpty() || dateTimeEdit->currentText().isEmpty() || name->text().isEmpty() || surname->text().isEmpty() || Email->text().isEmpty() || seat->text().isEmpty()) {
            throw std::invalid_argument("All fields must be filled out.");
        }


        return true;
    }
    catch (const std::invalid_argument& e) {
        QMessageBox::critical(this, "Error", e.what());
        return false;
    }
}

void ManageBookingWindow::updateFields(const Booking& booking)
{
    Schedule schedule = scheduleDatabase.getScheduleById(booking.getScheduleId());
    Movie movie = movieDatabase.getMovieById(schedule.getMovieId());

    titleEdit->setCurrentText(movie.getTitle());

    QString formattedDateTime = schedule.getDateTime().toString("ddd MMM dd HH:mm:ss yyyy");
    int index = dateTimeEdit->findText(formattedDateTime);
    if (index != -1) {
        dateTimeEdit->setCurrentIndex(index);
    }
    else {
        // Je¿eli nie znaleziono, dodaj nowy element i ustaw go jako aktualny
        dateTimeEdit->addItem(formattedDateTime);
        dateTimeEdit->setCurrentText(formattedDateTime);
    }

    name->setText(booking.getName());
    surname->setText(booking.getSurname());
    Email->setText(booking.getEmail());
    seat->setText(booking.getSeat());
}

Booking ManageBookingWindow::getBookingFromFields()
{
    checkInputFields();

    QString movieTitle = titleEdit->currentText();
    Movie movie = movieDatabase.getMovieByTitle(movieTitle);
    int movieId = movieDatabase.getMovieId(movie);

    QDateTime dateTime = QDateTime::fromString(dateTimeEdit->currentText(), "ddd MMM dd HH:mm:ss yyyy");
    if (!dateTime.isValid()) {
        dateTime = QDateTime::fromString(dateTimeEdit->currentText(), "ddd MMM d HH:mm:ss yyyy");
    }
    Schedule schedule = scheduleDatabase.getScheduleByMovieAndDateTime(movieId, dateTime);

    int scheduleId = scheduleDatabase.getScheduleId(schedule); 

    QString nameText = name->text();
    QString surnameText = surname->text();
    QString emailText = Email->text();
    QString seatText = seat->text();

    return Booking(movieId, scheduleId, seatText, nameText, surnameText, emailText);
}

void ManageBookingWindow::updateFields()
{
    titleEdit->setCurrentIndex(0);
    dateTimeEdit->setCurrentIndex(0);
    name->clear();
    surname->clear();
    Email->clear();
    seat->clear();

    selectedBookingId = -1;
    bookingTableWidget->getTableWidget()->clearSelection();
}

void ManageBookingWindow::editCurrentBooking()
{
    if (!checkInputFields()) {
        return;
    }

    if (selectedBookingId == -1) {
        QMessageBox::information(this, "Information", "Select a booking to update.");
        return;
    }

    Booking newBooking = getBookingFromFields();
    Booking oldBooking = bookingDatabase.getBookingById(selectedBookingId);

    if (!bookingDatabase.updateBooking(oldBooking, newBooking)) {
        return;
    }

    Schedule newSchedule = scheduleDatabase.getScheduleById(newBooking.getScheduleId());

    if (scheduleDatabase.getScheduleId(newSchedule) == -1) {
        QMessageBox::warning(this, "Warning", "Selected date/time is not available for the chosen movie.");
        return;
    }
    bookingTableWidget->setBookingsInTableWidget();
    updateFields();
}

void ManageBookingWindow::removeCurrentBooking()
{
    QList<QTableWidgetItem*> selectedItems = bookingTableWidget->getTableWidget()->selectedItems();

    if (selectedItems.isEmpty()) {
        QMessageBox::information(this, "Information", "Select a booking to remove.");
        return;
    }

    int rowIndex = selectedItems.first()->row();

    QString title = bookingTableWidget->getTableWidget()->item(rowIndex, 0)->text();
    QString nameText = bookingTableWidget->getTableWidget()->item(rowIndex, 2)->text();
    QString surnameText = bookingTableWidget->getTableWidget()->item(rowIndex, 3)->text();
    QString emailText = bookingTableWidget->getTableWidget()->item(rowIndex, 4)->text();
    QString seatText = bookingTableWidget->getTableWidget()->item(rowIndex, 5)->text();

    Movie movie = movieDatabase.getMovieByTitle(title);
    QDateTime dateTime = QDateTime::fromString(bookingTableWidget->getTableWidget()->item(rowIndex, 1)->text(), "ddd MMM dd HH:mm:ss yyyy");
    if (!dateTime.isValid()) {
        dateTime = QDateTime::fromString(bookingTableWidget->getTableWidget()->item(rowIndex, 1)->text(), "ddd MMM d HH:mm:ss yyyy");
    }
    Schedule schedule = scheduleDatabase.getScheduleByMovieAndDateTime(movieDatabase.getMovieId(movie), dateTime);

    Booking booking(movieDatabase.getMovieId(movie), scheduleDatabase.getScheduleId(schedule), seatText, nameText, surnameText, emailText);

    if (!bookingDatabase.deleteBooking(booking)) {
        return;
    }

    bookingTableWidget->setBookingsInTableWidget();
    updateFields();
}