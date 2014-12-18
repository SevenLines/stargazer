#ifndef SKYVIEWER_H
#define SKYVIEWER_H

#include "sky.h"
#include "star.h"

#include <QWidget>
#include <QGraphicsView>
#include <QSqlDatabase>

class SkyView : public QGraphicsView
{
    Q_OBJECT
private:
    float mScale;
    qreal centerStarRA;
    qreal centerStarDec;
    int const_id;
    Sky *mSky;

    QPoint lastMousePos;

    QGraphicsScene scene;

    QList<Star> stars;

public:
    explicit SkyView(QWidget *parent = 0);

signals:

public slots:
    void setCenterStar(qreal RA, qreal Dec);
    void setConst_id(int id);
    void setSky(Sky *sky);
    void fetchStar(qreal x, qreal y, const Star &star);
    void reloadSky();

    // QWidget interface
protected:
    void wheelEvent(QWheelEvent *);
    void resizeEvent(QResizeEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
};

#endif // SKYVIEWER_H
