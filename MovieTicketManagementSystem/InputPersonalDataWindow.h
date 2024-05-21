#pragma once
#include <QString>
#include <QLineEdit>
#include <QSpinBox>
#include "Movie.h"
#include <QPushButton>

class InputPersonalDataWindow : public QObject
{
	Q_OBJECT

public:

	InputPersonalDataWindow(QLineEdit* nameInput,QLineEdit* surnameInput,QLineEdit* emailInput,QLineEdit* movieInput, QDateTimeEdit* dateTimeInput, QSpinBox* seatInput,QPushButton* acceptButton);
	~InputPersonalDataWindow();

	QString getName() const;
	QString getSurname() const;
	QString getEmail() const;

	void setMovie(Movie& movie);
	void setDateTime(QDateTime dateTime);
	void setSeat(int seat);
private:
	QLineEdit* nameInput;
	QLineEdit* surnameInput;
	QLineEdit* emailInput;
	QLineEdit* movieInput;
	QDateTimeEdit* dateTimeInput;
	QSpinBox* seatInput;
	QPushButton* acceptButton;
	void checkInputs();
	bool validateInputs();

};

