#ifndef SKY_H
#define SKY_H

#include <QList>
#include <star.h>

class Sky
{
private:
    QList<Star> stars;
public:
    Sky();
    void addStar(Star star);
};

#endif // SKY_H
