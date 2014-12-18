#ifndef STAR_H
#define STAR_H

#include <QString>

class Star
{
public:
    int id;
    qreal x;
    qreal y;

    qreal Dec;
    qreal RA;
    qreal Mag;
    QString Name;
    QString Name_rus;
    Star();
    Star(QString name, qreal Dec, qreal RA, qreal Mag, int id);

    QString toString();
};

#endif // STAR_H
