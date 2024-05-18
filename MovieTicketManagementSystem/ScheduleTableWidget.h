#pragma once

#include <QWidget>
#include <QTableWidget>
#include <QStringListModel>
#include "ScheduleDatabase.h"

class ScheduleTableWidget : public QWidget
{
    Q_OBJECT

public:
    ScheduleTableWidget(QTableWidget* tableWidget);
    ~ScheduleTableWidget();
    void setSchedulesInTableWidget();
    QTableWidget* getTableWidget() const;


private:
    QTableWidget* tableWidget;
    ScheduleDatabase scheduleDatabase;

};