#include "AddMovieWindow.h"

AddMovieWindow::AddMovieWindow(QTextEdit* titleEditElement, QTextEdit* directorElement, QComboBox* typeElement, QLineEdit* durationTimeElement, QPushButton* addButtonElement, QWidget* parent)
{
	titleEdit = titleEditElement;
	director = directorElement;
	type = typeElement;
	durationTime = durationTimeElement;
	addButton = addButtonElement;

    connect(addButton, SIGNAL(clicked()), this, SLOT(addMovie()));
}

void AddMovieWindow::addMovie()
{
    //get data from the fields
    QString titleStr = titleEdit->toPlainText();
    QString directorStr = director->toPlainText();
    QString typeStr = type->currentText();
    int durationInt = durationTime->text().toInt();

    //database function

    //clear after adding
    titleEdit->clear();
    director->clear();
    type->clear();
    durationTime->clear();
}
