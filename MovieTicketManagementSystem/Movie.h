#pragma once
#include <QString>
class Movie
{
public:
	Movie(int id, const QString& title, const QString& director, const QString& type, int duration);
	int getId() const;
	int getDuration() const;
	QString getTitle() const;
	QString getDirector() const;
	QString getType() const;

private:
	int id;
	QString title;
	QString director;
	QString type;
	int duration;

};

