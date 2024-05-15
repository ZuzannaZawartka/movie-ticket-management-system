#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QPushButton>

class AddMovieWindow: public QWidget
{
    Q_OBJECT;

public:
    explicit AddMovieWindow(QTextEdit* titleEdit, QTextEdit* director, QComboBox* type, QLineEdit* durationTime, QPushButton* addButton, QWidget* parent = nullptr);

private slots:
    void addMovie();

private:
    QTextEdit* titleEdit;
    QTextEdit* director;
    QComboBox* type;
    QLineEdit* durationTime;
    QPushButton* addButton;
};
