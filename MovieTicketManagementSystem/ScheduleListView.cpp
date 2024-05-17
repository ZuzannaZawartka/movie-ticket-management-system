#include "ScheduleListView.h"


ScheduleListView::ScheduleListView(QListView* listView)
    : scheduleListView(listView)
{
    scheduleListModel = new QStringListModel(this);
    listView->setModel(scheduleListModel);
    setScheduleListView();
}


ScheduleListView::~ScheduleListView()
{
    delete scheduleListModel;
}


void ScheduleListView::setScheduleListView()
{
    QStringList schedulesStringList;

    // Upewnij siê, ¿e scheduleDatabase jest skonfigurowany i dostêpny

    // Pobranie wszystkich harmonogramów z bazy danych
    QList<Schedule> schedules = scheduleDatabase.getAllSchedules();

    // Przechodzenie przez wszystkie harmonogramy i dodawanie informacji do listy
    for (const Schedule& sched : schedules)
    {
        QString scheduleInfo = QString("%1 - %2 - %3 (%4 minutes)")
            .arg(sched.getMovie().getTitle())
            .arg(sched.getDate().toString())
            .arg(sched.getTime().toString())
            .arg(sched.getDurationMinutes());

        schedulesStringList.append(scheduleInfo);
    }

    // Ustawienie listy stringów w modelu
    scheduleListModel->setStringList(schedulesStringList);
}