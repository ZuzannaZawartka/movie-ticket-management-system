#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "MovieListView.h"
#include "AddMovieWindow.h"
#include "MovieDatabase.h"
#include "ScheduleListView.h"
#include "ScheduleDatabase.h"

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
    ScheduleListView* scheduleListView;


    private slots:
        void changeToManageMovieWindow();
        void changeToMainWindow();
        void changeToBookTicketWindow();
        void changeToShowMovieListWindow();
        void changeToViewBookingsWindow();
        void changeToAddMovieWindow();
        void changeToRemoveMovieWindow();
};
