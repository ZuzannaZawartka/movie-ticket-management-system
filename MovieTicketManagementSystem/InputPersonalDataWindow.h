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
	QString getName() const;
	QString getSurname() const;
	QString getEmail() const;
	void setMovie(Movie& movie);
	void setDateTime(QDateTime dateTime);
	void setSeat(int seat);
	void resetInputs();

signals:
	void personalDataAccepted(QString name, QString surname, QString email);

private:
	QLineEdit* nameInput;
	QLineEdit* surnameInput;
	QLineEdit* emailInput;
	QLineEdit* movieInput;
	QDateTimeEdit* dateTimeInput;
	QSpinBox* seatInput;
	QPushButton* acceptButton;
	QRegularExpressionValidator* nameValidator;  
	QRegularExpressionValidator* surnameValidator;  
	QRegularExpressionValidator* emailValidator;  
	void checkInputs();
	void onAcceptButton();
	bool validateInputs();
};

