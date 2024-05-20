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
	bool isSelectedSchedule();
	int setSelectedScheduleId();
	void setMovieId(int movieId);

	signals:
		void scheduleSelected();

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

