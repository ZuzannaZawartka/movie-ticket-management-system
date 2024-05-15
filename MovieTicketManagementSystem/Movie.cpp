#include "Movie.h"

Movie::Movie(const QString& title, const QString& director, const QString& type, int duration)
    :  title(title), director(director), type(type), duration(duration)
{
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
