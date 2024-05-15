#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "MovieListView.h"
#include "AddMovieWindow.h"
#include "MovieDatabase.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT;

public:
    MainWindow(QWidget* parent = nullptr); 
    ~MainWindow(); 

private:
    Ui::MainWindowClass ui;
    AddMovieWindow* addMovieWindow;
    MovieListView* movieListView;
    MovieListView* bookTicketListView;
    MovieListView* removeMovieListView;


    private slots:
        void changeToManageMovieWindow();
        void changeToMainWindow();
        void changeToBookTicketWindow();
        void changeToShowMovieListWindow();
        void changeToViewBookingsWindow();
        void changeToAddMovieWindow();
        void changeToRemoveMovieWindow();
};
