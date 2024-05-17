#pragma once

#include <QWidget>
#include <QTableWidget>
#include <QStringListModel>
#include "MovieDatabase.h"

class MovieTableWidget : public QWidget
{
    Q_OBJECT

public:
    MovieTableWidget(QTableWidget* tableWidget);
    ~MovieTableWidget();
    void setMoviesInTableWidget();
    QTableWidget* getTableWidget() const;


private:
    QTableWidget* tableWidget;
    MovieDatabase movieDatabase;

};