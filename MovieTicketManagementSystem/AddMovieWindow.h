#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QPushButton>
#include "MovieDatabase.h"
#include "MovieListView.h"

class AddMovieWindow: public QWidget
{
    Q_OBJECT;

public:
    explicit AddMovieWindow(QTextEdit* titleEdit, QTextEdit* director, QComboBox* type, QLineEdit* durationTime, QPushButton* addButton, QWidget* parent = nullptr);


private:
    QTextEdit* titleEdit;
    QTextEdit* director;
    QComboBox* type;
    QLineEdit* durationTime;
    QPushButton* addButton;
    MovieDatabase movieDatabase;

    void setLimitationsOnFields();
    bool checkInputFields();

private slots:
    void addMovie();

};
