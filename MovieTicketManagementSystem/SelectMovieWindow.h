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
	int setSelectedMovieId();
	int getSelectedMovieId();
	void resetSelectedMovieId();

signals:
	void movieSelected(int movieId);

private:
	QPushButton* acceptButton;
	QTableWidget* tableWidget;
	int selectedMovieId;

private slots:
	void onSelectItem();
	void onAcceptButton();
};

