#pragma once

#include <QWidget>
#include <QListView>
#include <QStringListModel>
#include "MovieDatabase.h"

class MovieListView : public QWidget
{
    Q_OBJECT

public:
    MovieListView(QListView* listView);
    virtual ~MovieListView();
    void setMoviesInListView();
    void setSelectionMode();


protected:
    QListView* listView;
    QStringListModel* listModel = new QStringListModel(this);
    MovieDatabase movieDatabase;

};