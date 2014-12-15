#include "star.h"

Star::Star(QString name, float Dec, float RA, float Mag, int id)
{
    this->Dec = Dec;
    this->Mag = Mag;
    this->Name = name;
    this->RA = RA;
    this->id = id;
}

QString Star::toString()
{
    return QString("%0 (Dec:%1, RA:%2, Mag: %3)").arg(Name).arg(Dec).arg(RA).arg(Mag);
}
