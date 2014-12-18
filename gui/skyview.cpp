#include "qstaritem.h"
#include "skyview.h"
#include "star.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QDir>
#include <QSqlDriver>
#include <QWheelEvent>
#include <QThread>
#include <qscrollbar.h>
#include "qstaritem.h"

void SkyView::reloadSky()
{
    scene.clear();
    if (mSky) {
        mSky->fetchStars([&](qreal x,qreal y,Star star) {
            fetchStar(x,y,star);
        },[&](qreal x1, qreal y1, qreal x2, qreal y2) {
            scene.addLine(x1, y1, x2, y2, QPen(QBrush(Qt::yellow), 0));
        });
    }
}

SkyView::SkyView(QWidget* parent)
    : QGraphicsView(parent), mSky(0)
{
    mScale = 1;
    setCenterStar(0, 0);
    this->setScene(&scene);
    this->setBackgroundBrush(QBrush(Qt::darkBlue));
}

void SkyView::setCenterStar(qreal RA, qreal Dec)
{
    centerStarRA = RA;
    centerStarDec = Dec;

    if (centerStarRA > 24) centerStarRA -= 24;
    if (centerStarRA < 0) centerStarRA = 24 + centerStarRA;

    if (centerStarDec > 360) centerStarDec -= 360;
    if (centerStarDec < 0) centerStarDec = 360 + centerStarDec;

    if (mSky) {
        mSky->setCenterRA(centerStarRA);
        mSky->setCenterDec(centerStarDec);
    }
    this->reloadSky();
}

void SkyView::setConst_id(int id)
{
    const_id = id;
    this->reloadSky();
}

void SkyView::setSky(Sky *sky)
{
    mSky = sky;
    if (mSky) {
        connect(mSky, SIGNAL(fetchStar(qreal,qreal,Star)), this, SLOT(fetchStar(qreal,qreal,Star)), Qt::DirectConnection);
    }
}

void SkyView::fetchStar(qreal x, qreal y, const Star &star)
{
    QStarItem *item  = new QStarItem(x, y, star);
    scene.addItem(item);
}

void SkyView::wheelEvent(QWheelEvent *e)
{
    QPointF p = mapToScene(e->pos());


    if (e->delta() > 0) {
        scale(1.5, 1.5);
    } else {
        scale(0.5, 0.5);
    }
    QPointF center = mapToScene(rect().center());
    QPointF p2 = mapToScene(e->pos());
    centerOn(center  + p - p2);
}

void SkyView::resizeEvent(QResizeEvent *)
{
//    scene.setSceneRect(QRect());
//    fitInView(scene.sceneRect(),Qt::KeepAspectRatio);
    //    fitInView(scene.sceneRect(),Qt::KeepAspectRatio);
}

void SkyView::mouseMoveEvent(QMouseEvent *e)
{
    QPoint offset = e->pos() - lastMousePos;
    if (e->buttons() & Qt::MidButton) {
        setCursor(Qt::ClosedHandCursor);
        if (offset.y()) {
            QScrollBar *yScroll = verticalScrollBar();
            yScroll->setValue(yScroll->value() - offset.y());
        }
        if (offset.x()) {
            QScrollBar *xScroll = horizontalScrollBar();
            xScroll->setValue(xScroll->value() - offset.x());
        }
    } if (e->buttons() & Qt::RightButton) {
        setCenterStar((centerStarRA + ((float)offset.x() / 100) ), centerStarDec);
    } else {
        setCursor(QCursor());
    }
    lastMousePos = e->pos();
}

void SkyView::mousePressEvent(QMouseEvent *e)
{
    lastMousePos = e->pos();
}


