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
	int getSelectedScheduleId();
	int setSelectedScheduleId();
	void setMovieId(int movieId);

signals:
	void scheduleSelected(int scheduleID);

private:
	QPushButton* acceptButton;
	QTableWidget* tableWidget;
	ScheduleDatabase scheduleDatabase;
	int selectedScheduleId;
	int movieId;

private slots:
	void onAcceptButton2();
	void onSelectItem();
};

