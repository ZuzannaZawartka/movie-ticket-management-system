#pragma once
#include <QString>
class Movie
{
public:
	Movie(const QString& title, const QString& director, const QString& type, int duration);
	int getDuration() const;
	QString getTitle() const;
	QString getDirector() const;
	QString getType() const;

private:
	QString title;
	QString director;
	QString type;
	int duration;
};

