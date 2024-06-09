#pragma once
#include <QWidget>
#include <QTableWidget>
#include "BookingDatabase.h"
#include "MovieDatabase.h"
#include "ScheduleDatabase.h"

class BookingTableWidget : public QWidget
{
    Q_OBJECT

public:
    BookingTableWidget(QTableWidget* tableWidget);
    void setBookingsInTableWidget();
    QTableWidget* getTableWidget() const;

protected:
    BookingDatabase bookingDatabase;
    MovieDatabase movieDatabase;
    ScheduleDatabase scheduleDatabase;

private:
    QTableWidget* tableWidget;
};
