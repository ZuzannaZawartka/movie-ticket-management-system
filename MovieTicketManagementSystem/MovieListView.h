#pragma once

#include <QWidget>
#include <QTableWidget>
#include <QStringListModel>
#include "MovieDatabase.h"

class MovieListView : public QWidget
{
    Q_OBJECT

public:
    MovieListView(QTableWidget* tableWidget);
    ~MovieListView();
    void setMoviesInListView();
    QTableWidget* getTableWidget() const;


private:
    QTableWidget* tableWidget;
    QStringListModel* listModel = new QStringListModel(this);
    MovieDatabase movieDatabase;

};