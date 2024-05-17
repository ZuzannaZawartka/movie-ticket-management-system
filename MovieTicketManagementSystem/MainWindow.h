#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "MovieTableWidget.h"
#include "ManageMovieWindow.h"
#include "MovieDatabase.h"
#include "ScheduleListView.h"
#include "ScheduleDatabase.h"
#include "ManageRoomWindow.h"

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
    ScheduleListView* scheduleListView;
    ManageRoomWindow* manageRoomWindow;

    private slots:
        void changeToManageMovieWindow();
        void changeToMainWindow();
        void changeToBookTicketWindow();
        void changeToShowMovieListWindow();
        void changeToViewBookingsWindow();
        void changeToManageRoomWindow();
};
