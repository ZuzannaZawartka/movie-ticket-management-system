#include "Movie.h"

Movie::Movie(int id, const QString& title, const QString& director, const QString& type, int duration)
    : id(id), title(title), director(director), type(type), duration(duration)
{
}

int Movie::getId() const
{
    return id;
}

QString Movie::getTitle() const
{
    return title;
}

QString Movie::getDirector() const
{
    return director;
}

QString Movie::getType() const
{
    return type;
}

int Movie::getDuration() const
{
    return duration;
}
