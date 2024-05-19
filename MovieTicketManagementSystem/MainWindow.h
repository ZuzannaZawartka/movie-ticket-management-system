#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "MovieTableWidget.h"
#include "ManageMovieWindow.h"
#include "MovieDatabase.h"
#include "ScheduleTableWidget.h"
#include "ScheduleDatabase.h"
#include "ManageScheduleWindow.h"
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
    ScheduleTableWidget* scheduleTableWidget;
    ScheduleTableWidget* showScheduleTable;
    ManageScheduleWindow* manageScheduleWindow;
    ManageRoomWindow* manageRoomWindow;

private slots:
    void changeToMainWindow();
    void changeToShowScheduleWindow();
    void changeToManageMovieWindow();
    void changeToBookTicketWindow();
    void changeToShowMovieListWindow();
    void changeToViewBookingsWindow();
    void changeToManageRoomWindow();
    void changeToManageScheduleWindow();
};