#include "InputPersonalDataWindow.h"
#include <QLineEdit>
#include <QComboBox>
#include <QMessageBox>
#include <QDateTimeEdit>


InputPersonalDataWindow::InputPersonalDataWindow(QLineEdit* nameInput, QLineEdit* surnameInput, QLineEdit* emailInput, QLineEdit* movieInput, QDateTimeEdit* dateTimeInput, QSpinBox* seatInput,QPushButton* acceptButton) : nameInput(nameInput), surnameInput(surnameInput), emailInput(emailInput), movieInput(movieInput), dateTimeInput(dateTimeInput), seatInput(seatInput), acceptButton(acceptButton)
{
	movieInput->setDisabled(true);
	dateTimeInput->setDisabled(true);
	seatInput->setDisabled(true);

	connect(nameInput, &QLineEdit::textChanged, this, &InputPersonalDataWindow::checkInputs);
	connect(surnameInput, &QLineEdit::textChanged, this, &InputPersonalDataWindow::checkInputs);
	connect(emailInput, &QLineEdit::textChanged, this, &InputPersonalDataWindow::checkInputs);


	connect(acceptButton, &QPushButton::clicked, this, &InputPersonalDataWindow::onAcceptButtonClicked);

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
	//bool allFieldsFilled = !nameInput->text().isEmpty() && !surnameInput->text().isEmpty() && !emailInput->text().isEmpty();
	acceptButton->setEnabled(validateInputs());
}

void InputPersonalDataWindow::onAcceptButtonClicked()
{

	if (!validateInputs()) {
		QMessageBox::warning(nullptr, "Input Error", "All fields must be filled out.");
		return;
	}

	// Dalsze dzia³ania po klikniêciu przycisku acceptButton
}

bool InputPersonalDataWindow::validateInputs()
{
	return !nameInput->text().isEmpty() && !surnameInput->text().isEmpty() && !emailInput->text().isEmpty();
}