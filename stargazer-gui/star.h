#ifndef STAR_H
#define STAR_H

#include <QString>

class Star
{
public:
    int id;
    float Dec;
    float RA;
    float Mag;
    QString Name;
    QString Name_rus;
    Star(QString name, float Dec, float RA, float Mag, int id);

    QString toString();
};

#endif // STAR_H
