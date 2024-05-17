#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "MovieTableWidget.h"
#include "ManageMovieWindow.h"
#include "MovieDatabase.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT;

public:
    MainWindow(QWidget* parent = nullptr); 
    ~MainWindow(); 

private:
    Ui::MainWindowClass ui;
    ManageMovieWindow* manageMovieWindow;
    MovieTableWidget* movieTableWidget;
    MovieTableWidget* bookTicketListView;


    private slots:
        void changeToManageMovieWindow();
        void changeToMainWindow();
        void changeToBookTicketWindow();
        void changeToShowMovieListWindow();
        void changeToViewBookingsWindow();
};
