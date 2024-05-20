#pragma once
#include "MovieTableWidget.h"
#include <QPushButton>
class SelectMovieWindow :
	public MovieTableWidget
{
	Q_OBJECT

public:
	SelectMovieWindow(QPushButton* acceptButton, QTableWidget* tableWidget);
	~SelectMovieWindow();
	bool isMovieSelected();

	void setSelectedMovieId();

private:
	QPushButton* acceptButton;
	QTableWidget* tableWidget;
	int selectedMovieId;

private slots:
	void onAcceptButtonClicked();
};

