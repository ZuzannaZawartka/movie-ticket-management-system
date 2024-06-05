#include "InputPersonalDataWindow.h"
#include <QLineEdit>
#include <QComboBox>
#include <QMessageBox>
#include <QDateTimeEdit>


InputPersonalDataWindow::InputPersonalDataWindow(QLineEdit* nameInput, QLineEdit* surnameInput, QLineEdit* emailInput, QLineEdit* movieInput, QDateTimeEdit* dateTimeInput, QSpinBox* seatInput, QPushButton* acceptButton) : nameInput(nameInput), surnameInput(surnameInput), emailInput(emailInput), movieInput(movieInput), dateTimeInput(dateTimeInput), seatInput(seatInput), acceptButton(acceptButton)
{
    movieInput->setDisabled(true);
    dateTimeInput->setDisabled(true);
    seatInput->setDisabled(true);

    connect(nameInput, &QLineEdit::textChanged, this, &InputPersonalDataWindow::checkInputs);
    connect(surnameInput, &QLineEdit::textChanged, this, &InputPersonalDataWindow::checkInputs);
    connect(emailInput, &QLineEdit::textChanged, this, &InputPersonalDataWindow::checkInputs);
    connect(acceptButton, &QPushButton::clicked, this, &InputPersonalDataWindow::onAcceptButton);

    checkInputs();
}

InputPersonalDataWindow::~InputPersonalDataWindow()
{
    
}

QString InputPersonalDataWindow::getName() const
{
    return nameInput->text();
}

QString InputPersonalDataWindow::getSurname() const
{
    return surnameInput->text();
}

QString InputPersonalDataWindow::getEmail() const
{
    return emailInput->text();
}

void InputPersonalDataWindow::setMovie(Movie& movie)
{
    movieInput->setText(movie.getTitle());
}

void InputPersonalDataWindow::setDateTime(QDateTime dateTime)
{
    dateTimeInput->setDateTime(dateTime);
}

void InputPersonalDataWindow::setSeat(int seat)
{
    seatInput->setValue(seat);
}

void InputPersonalDataWindow::checkInputs()
{
    acceptButton->setEnabled(validateInputs());
}

void InputPersonalDataWindow::onAcceptButton()
{
    if (validateInputs())
    {
        emit personalDataAccepted(nameInput->text(), surnameInput->text(), emailInput->text());
    }
    else
    {
        QString errorMessage = "Please fill all fields correctly:\n";
        if (nameInput->text().isEmpty())
            errorMessage += "- Name cannot be empty\n";
        if (surnameInput->text().isEmpty())
            errorMessage += "- Surname cannot be empty\n";
        if (emailInput->text().isEmpty())
            errorMessage += "- Email cannot be empty\n";
        else
            errorMessage += "- Invalid email format\n";

        QMessageBox::warning(nullptr, "Error", errorMessage);
    }

    resetInputs();
}

void InputPersonalDataWindow::resetInputs()
{
    nameInput->clear();
    surnameInput->clear();
    emailInput->clear();
    checkInputs();
}

bool InputPersonalDataWindow::validateInputs()
{
    QString name = nameInput->text();
    QString surname = surnameInput->text();
    QString email = emailInput->text();

    QRegularExpression nameRegex("^[A-Za-z]+$");
    QRegularExpression surnameRegex("^[A-Za-z]+$");
    QRegularExpression emailRegex("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");


    bool nameValid = nameRegex.match(name).hasMatch();
    bool surnameValid = surnameRegex.match(surname).hasMatch();
    bool emailValid = emailRegex.match(email).hasMatch();

    return !name.isEmpty() && !surname.isEmpty() && !email.isEmpty() && nameValid && surnameValid && emailValid;
}
