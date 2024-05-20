#pragma once
#include "ScheduleTableWidget.h"
#include <QPushButton>


class SelectScheduleWindow :
    public ScheduleTableWidget
{
    Q_OBJECT

public:
	SelectScheduleWindow(QPushButton* acceptButton, QTableWidget* tableWidget);
	~SelectScheduleWindow();
private:


};

