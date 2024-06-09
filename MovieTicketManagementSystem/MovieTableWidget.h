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
    void setMoviesInTableWidget();
    QTableWidget* getTableWidget() const;

protected:
    MovieDatabase movieDatabase;

private:
    QTableWidget* tableWidget;
};