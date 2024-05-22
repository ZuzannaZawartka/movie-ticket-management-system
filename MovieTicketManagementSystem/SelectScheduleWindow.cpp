#include "SelectScheduleWindow.h"
#include <QMessageBox>

SelectScheduleWindow::SelectScheduleWindow(QPushButton* acceptButton, QTableWidget* tableWidget): ScheduleTableWidget(tableWidget)
{
	this->acceptButton = acceptButton;
	this->tableWidget = tableWidget;

    this->selectedScheduleId = -1;
    this->movieId = -1;

	//connect the signal emitted when the user selects a schedule to the onSelectItem slot
	connect(tableWidget->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this, SLOT(onSelectItem()));

    //connect the signal emitted when the user clicks the accept button to the onAcceptButton2 slot
	connect(acceptButton, SIGNAL(clicked()), this, SLOT(onAcceptButton2()));
}

SelectScheduleWindow::~SelectScheduleWindow()
{
	delete acceptButton;
	delete tableWidget;
}

int SelectScheduleWindow::getSelectedScheduleId()
{
    return this->selectedScheduleId;
}

int SelectScheduleWindow::setSelectedScheduleId()
{
    int currentRow = tableWidget->currentRow();
    if (currentRow != -1) {
      
        QString title = tableWidget->item(currentRow, 0)->text();
        QString dateStr = tableWidget->item(currentRow, 1)->text();
        QString timeStr = tableWidget->item(currentRow, 2)->text();
        QString durationStr = tableWidget->item(currentRow, 3)->text();

        
        QDate date = QDate::fromString(dateStr, "yyyy-MM-dd");
        QTime time = QTime::fromString(timeStr, "hh:mm:ss");
        int duration = durationStr.toInt();

        Schedule schedule(movieId, date, time, duration); 
        
        int scheduleId = scheduleDatabase.getScheduleId(schedule);
        if (scheduleId != -1) {
            this->selectedScheduleId = scheduleId;
            return scheduleId;
        }
        else {
            return -1;
        }
    }
    else {
        return -1;
    }
}

void SelectScheduleWindow::onSelectItem() {
    setSelectedScheduleId();
    if (selectedScheduleId == -1) {
        QMessageBox::information(nullptr, "error", "Schedule not selected or not posibble to find it");
    }
}

void SelectScheduleWindow::setMovieId(int movieId)
{
    	this->movieId = movieId;
}


void SelectScheduleWindow::onAcceptButton2()
{
	if (getSelectedScheduleId() != -1) {
		emit scheduleSelected(this->selectedScheduleId);
	}
	else {
		QMessageBox::warning(this, "Warning", "Please select a schedule.");
	}


}