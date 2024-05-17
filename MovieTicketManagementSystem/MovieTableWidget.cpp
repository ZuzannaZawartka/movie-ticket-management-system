#include "MovieTableWidget.h"
#include <QStandardItem>


MovieTableWidget::MovieTableWidget(QTableWidget* tableWidget)
    : tableWidget(tableWidget)

{
    tableWidget->setColumnCount(4);

    tableWidget->setHorizontalHeaderLabels({ "Title", "Director", "Type", "Duration" });

    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows); // select entire row
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); // turn off editing


    setMoviesInTableWidget();
}

MovieTableWidget::~MovieTableWidget()
{
}

void MovieTableWidget::setMoviesInTableWidget()
{

    tableWidget->clearContents();

    // download all movies from database
    QList<Movie> movies = movieDatabase.getAllMovies();

    // set number of rows in QTableWidget to the number of movies
    tableWidget->setRowCount(movies.size());

    for (int row = 0; row < movies.size(); ++row) {
        Movie movie = movies[row];

        QTableWidgetItem* titleItem = new QTableWidgetItem(movie.getTitle());
        QTableWidgetItem* directorItem = new QTableWidgetItem(movie.getDirector());
        QTableWidgetItem* typeItem = new QTableWidgetItem(movie.getType());
        QTableWidgetItem* durationItem = new QTableWidgetItem(QString::number(movie.getDuration()));

        tableWidget->setItem(row, 0, titleItem);
        tableWidget->setItem(row, 1, directorItem);
        tableWidget->setItem(row, 2, typeItem);
        tableWidget->setItem(row, 3, durationItem);
    }

    tableWidget->resizeColumnsToContents();
}

QTableWidget* MovieTableWidget::getTableWidget() const
{
    return tableWidget;
}
