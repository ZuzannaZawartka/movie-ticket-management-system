#include "SelectScheduleWindow.h"

SelectScheduleWindow::SelectScheduleWindow(QPushButton* acceptButton, QTableWidget* tableWidget): ScheduleTableWidget(tableWidget)
{
	this->acceptButton = acceptButton;
	this->tableWidget = tableWidget;

}

SelectScheduleWindow::~SelectScheduleWindow()
{
	delete acceptButton;
	delete tableWidget;
}

