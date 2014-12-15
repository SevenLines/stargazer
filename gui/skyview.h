#ifndef SKYVIEWER_H
#define SKYVIEWER_H

#include "star.h"

#include <QWidget>
#include <QGraphicsView>
#include <QSqlDatabase>

class SkyView : public QGraphicsView
{
    Q_OBJECT
private:
    QGraphicsScene scene;
    QSqlDatabase db;
    QList<Star> stars;

public:
    explicit SkyView(QWidget *parent = 0);

signals:

public slots:

};

#endif // SKYVIEWER_H
