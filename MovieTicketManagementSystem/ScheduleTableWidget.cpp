#include "ScheduleTableWidget.h"
#include <QStandardItem>


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
}

void ScheduleTableWidget::setSchedulesInTableWidget()
{

    tableWidget->clearContents();

    // download all schedules from database
    QList<Schedule> schedules = scheduleDatabase.getAllSchedules();

    // set number of rows in QTableWidget to the number of schedules
    tableWidget->setRowCount(schedules.size());

    for (int row = 0; row < schedules.size(); ++row) {
        Schedule schedule = schedules[row];

        QTableWidgetItem* titleChooseItem = new QTableWidgetItem(schedule.getMovie().getTitle());
        QTableWidgetItem* dateChooseItem = new QTableWidgetItem(schedule.getDate().toString("yyyy-MM-dd"));
        QTableWidgetItem* timeChooseItem = new QTableWidgetItem(schedule.getTime().toString("HH:mm:ss"));
        QTableWidgetItem* durationChooseItem = new QTableWidgetItem(QString::number(schedule.getDurationMinutes()));

        tableWidget->setItem(row, 0, titleChooseItem);
        tableWidget->setItem(row, 1, dateChooseItem);
        tableWidget->setItem(row, 2, timeChooseItem);
        tableWidget->setItem(row, 3, durationChooseItem);
    }

    tableWidget->resizeColumnsToContents();

    if (tableWidget->rowCount() == 0) {
        tableWidget->setRowCount(1);
        QTableWidgetItem* noDataItem = new QTableWidgetItem("NO DATA");
        tableWidget->setItem(0, 0, noDataItem);
        tableWidget->setSpan(0, 0, 1, tableWidget->columnCount()); // Merge cells to fill the entire row
    }
}
/*
void ScheduleTableWidget::setSchedulesInTableWidget()
{

    tableWidget->clearContents();

    // download all schedules from database
    QList<Schedule> schedules = scheduleDatabase.getAllSchedules();

    // set number of rows in QTableWidget to the number of schedules
    tableWidget->setRowCount(schedules.size());

    for (int row = 0; row < schedules.size(); ++row) {
        Schedule schedule = schedules[row];

        QTableWidgetItem* titleScheduleItem = new QTableWidgetItem(schedule.getMovie().getTitle());
        QTableWidgetItem* dateScheduleItem = new QTableWidgetItem(schedule.getDate().toString("yyyy-MM-dd"));
        QTableWidgetItem* timeScheduleItem = new QTableWidgetItem(schedule.getTime().toString("HH:mm:ss"));
        QTableWidgetItem* durationScheduleItem = new QTableWidgetItem(QString::number(schedule.getDurationMinutes()));

        tableWidget->setItem(row, 0, titleScheduleItem);
        tableWidget->setItem(row, 1, dateScheduleItem);
        tableWidget->setItem(row, 2, timeScheduleItem);
        tableWidget->setItem(row, 3, durationScheduleItem);
    }

    tableWidget->resizeColumnsToContents();
}
*/
QTableWidget* ScheduleTableWidget::getTableWidget() const
{
    return tableWidget;
}