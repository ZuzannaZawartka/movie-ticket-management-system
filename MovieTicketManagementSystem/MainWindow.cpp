#include "MainWindow.h"
#include <QStringListModel>
#include "Movie.h"
#include "MovieListView.h"
#include "ManageMovieWindow.h"
#include "MovieDatabase.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    movieListView = new MovieListView(ui.MovieListView); //show movie window
    bookTicketListView = new MovieListView(ui.bookTicketListView);
    manageMovieWindow = new ManageMovieWindow(ui.textTitleEdit, ui.textDirectorEdit, ui.chooseMovieTypeBox, ui.timeDurationLineEdit, ui.removeSelectedMovieButton, ui.addNewMovieButton, ui.saveMovieButton, movieListView);

}

MainWindow::~MainWindow()
{
}


void MainWindow::changeToMainWindow()
{
    ui.stackedWidget->setCurrentWidget(ui.mainWindow);
}

void MainWindow::changeToManageMovieWindow()
{
    ui.stackedWidget->setCurrentWidget(ui.manageMovieWindow);
}
void MainWindow::changeToBookTicketWindow()
{
    ui.stackedWidget->setCurrentWidget(ui.bookTicketWindow);
}
void MainWindow::changeToShowMovieListWindow()
{
    ui.stackedWidget->setCurrentWidget(ui.showMovieListWindow);
}
void MainWindow::changeToViewBookingsWindow()
{
    ui.stackedWidget->setCurrentWidget(ui.viewBookingsWindow);
}
