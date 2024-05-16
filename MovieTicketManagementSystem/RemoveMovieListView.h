#pragma once
#include "MovieListView.h"
#include <QPushButton>

class RemoveMovieListView :
    public MovieListView
{
    public:
	RemoveMovieListView(QListView* listView,QPushButton* pushButton);
	~RemoveMovieListView() override;

private:
	QPushButton* pushButton;

private slots:
	void removeSelectedItem();
};

