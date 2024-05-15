#include "MainWindow.h"
#include <QStringListModel>
#include "Movie.h"
#include "MovieListView.h"
#include "AddMovieWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    movieListView = new MovieListView(ui.MovieListView);
    addMovieWindow = new AddMovieWindow(ui.textTitleEdit, ui.textDirectorEdit, ui.movieTypeComboBox, ui.timeDurationLineEdit, ui.addMovieToDatabase);

}

MainWindow::~MainWindow()
{}

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
void MainWindow::changeToAddMovieWindow()
{
    ui.stackedWidget->setCurrentWidget(ui.addMovieWindow);
}
