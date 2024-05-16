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

class ManageMovieWindow : public QWidget
{
    Q_OBJECT;

public:
    explicit ManageMovieWindow(QTextEdit* titleEdit, QTextEdit* director, QComboBox* type, QLineEdit* durationTime, QPushButton* removeButton, QPushButton* addNewButton, QPushButton* saveButton, MovieListView* movieListView);


private:
    QTextEdit* titleEdit;
    QTextEdit* director;
    QComboBox* type;
    QLineEdit* durationTime;
    QPushButton* removeButton;
    QPushButton* addNewButton;
    QPushButton* saveButton;
    MovieDatabase movieDatabase;
    MovieListView* movieListView;

    void setLimitationsOnFields();
    bool checkInputFields();

private slots:
    void addMovie();
    void removeSelectedItem()

};