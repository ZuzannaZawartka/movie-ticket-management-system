#pragma once
#include <QWidget>
#include <QListView>
#include <QStringListModel>
#include "ScheduleDatabase.h"
#include "MovieDatabase.h"

class ScheduleListView : public QWidget
{
    Q_OBJECT

public:
    explicit ScheduleListView(QListView* listView);
    ~ScheduleListView();
    void setScheduleListView();

private:
    QListView* scheduleListView;
    QStringListModel* scheduleListModel = new QStringListModel(this);
    ScheduleDatabase scheduleDatabase;

};