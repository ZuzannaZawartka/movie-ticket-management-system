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
#include "ReserveSeatsWindow.h"
#include "BookTicketWindow.h"
#include "SelectMovieWindow.h"
#include "InputPersonalDataWindow.h"
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
    ScheduleTableWidget* showScheduleTable;
    ManageScheduleWindow* manageScheduleWindow;
    ManageRoomWindow* manageRoomWindow;
    ReserveSeatsWindow* reserveSeatsWindow;
    BookTicketWindow* bookTicketWindow;
    SelectMovieWindow* selectMovieWindow;
    SelectScheduleWindow* selectScheduleWindow;
    InputPersonalDataWindow* inputPersonalDataWindow;

private slots:
    void changeToMainWindow();
    void changeToShowScheduleWindow();
    void changeToManageMovieWindow();
    void changeToBookTicketWindow();
    void changeToShowMovieListWindow();
    void changeToViewBookingsWindow();
    void changeToManageRoomWindow();
    void changeToManageScheduleWindow();
    void changeToSelectMovieWindow();
    void changeToSelectScheduleWindow();
    void changeToReserveSeatsWindow();
    void changeToInputPersonalDataWindow();
};