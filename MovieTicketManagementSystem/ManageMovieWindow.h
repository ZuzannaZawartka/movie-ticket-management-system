#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QPushButton>
#include "MovieDatabase.h"
#include "MovieTableWidget.h"

class ManageMovieWindow : public QWidget
{
    Q_OBJECT;

public:
    explicit ManageMovieWindow(QTextEdit* titleEdit, QTextEdit* director, QComboBox* type, QLineEdit* durationTime, QPushButton* saveButton, QPushButton* addButton, QPushButton* removeButton, QTableWidget* movieTableWidget);
    ~ManageMovieWindow();

private:
    QTextEdit* titleEdit;
    QTextEdit* director;
    QComboBox* type;
    QLineEdit* durationTime;
    QPushButton* addButton;
    QPushButton* saveButton;
    QPushButton* removeButton;
    MovieDatabase movieDatabase;
    MovieTableWidget* movieTableWidget;
    Movie getMovieFromFields();
    void setLimitationsOnFields();
    bool checkInputFields();
    void updateFields();
    void updateFields(const Movie& movie);
    int selectedMovieId;

signals:
    void moviesChanged();

private slots:
    void addMovie();
    void removeMovie();
    void updateMovie();
    void onMovieSelected(const QModelIndex& index); // Deklaracja nowego slotu
};