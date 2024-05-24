#include "ScheduleTableWidget.h"
#include <QStandardItem>
#include <QMessageBox>

ScheduleTableWidget::ScheduleTableWidget(QTableWidget* tableWidget)
    : tableWidget(tableWidget)
{
    tableWidget->setColumnCount(4);
    tableWidget->setHorizontalHeaderLabels({ "Title", "Date", "Time", "Duration" });
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows); // select entire row
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); // turn off editing

    setSchedulesInTableWidget();
}

ScheduleTableWidget::~ScheduleTableWidget()
{
    	//delete tableWidget;

}
void ScheduleTableWidget::setSchedulesInTableWidget(int movieId)
{
    tableWidget->clearContents();

    QList<Schedule> schedules;

    // if default value -1 is passed, get all schedules , else get schedules by movie id
    if (movieId == -1) {
        schedules = scheduleDatabase.getAllSchedules();
    }
    else {
        schedules = scheduleDatabase.getSchedulesByMovieIdSortedByDate(movieId);
    }

    tableWidget->setRowCount(schedules.size());

    for (int row = 0; row < schedules.size(); ++row) {
        const Schedule& schedule = schedules[row];
        Movie movie = movieDatabase.getMovieById(schedule.getMovieId());
        QTableWidgetItem* titleItem = new QTableWidgetItem(movie.getTitle());
        tableWidget->setItem(row, 0, titleItem);
       
     
        QTableWidgetItem* dateItem = new QTableWidgetItem(schedule.getDate().toString("yyyy-MM-dd"));
        QTableWidgetItem* timeItem = new QTableWidgetItem(schedule.getTime().toString("HH:mm:ss"));
        QTableWidgetItem* durationItem = new QTableWidgetItem(QString::number(movie.getDuration()));

        
        tableWidget->setItem(row, 1, dateItem);
        tableWidget->setItem(row, 2, timeItem);
        tableWidget->setItem(row, 3, durationItem);
    }

    tableWidget->resizeColumnsToContents();
}

QTableWidget* ScheduleTableWidget::getTableWidget() const
{
    return tableWidget;
}
