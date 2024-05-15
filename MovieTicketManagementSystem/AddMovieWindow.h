#pragma once
#include <QWidget>
#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QPushButton>
#include "MovieDatabase.h"
#include "MovieListView.h"

class AddMovieWindow : public QWidget
{
    Q_OBJECT;

public:
    explicit AddMovieWindow(QTextEdit* titleEdit, QTextEdit* director, QComboBox* type, QLineEdit* durationTime, QPushButton* addButton, MovieListView* movieListView);


private:
    QTextEdit* titleEdit;
    QTextEdit* director;
    QComboBox* type;
    QLineEdit* durationTime;
    QPushButton* addButton;
    MovieDatabase movieDatabase;
    MovieListView* movieListView;

    void setLimitationsOnFields();
    bool checkInputFields();

private slots:
    void addMovie();

};