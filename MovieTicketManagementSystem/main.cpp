#include "MainWindow.h"
#include "DatabaseManager.h"
#include "Movie.h"
#include "MovieDatabase.h"
#include "ScheduleDatabase.h"
#include "Schedule.h"
#include <QtWidgets/QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    ScheduleDatabase db;
    MovieDatabase db2;
    QDate date = QDate::currentDate(); // current date
    QTime time = QTime::currentTime(); // current time
    Movie mov = Movie("Tytul", "str", "str", 100);
    db2.addMovie(mov);
    Schedule m = Schedule(mov, date, time, 120);
    db.addSchedule(m);
    w.show();
    return a.exec();
}
