#ifndef QSTARITEM_H
#define QSTARITEM_H

#include "star.h"

#include <QGraphicsItemGroup>



class QStarItem : public QGraphicsItemGroup
{
private:
    qreal starRadius;
    QGraphicsEllipseItem* ellipseItem;
    QGraphicsTextItem* nameItem;
    Star mStar;
public:
    QStarItem(qreal x, qreal y, const Star &star, QGraphicsItem *parent=0);
    ~QStarItem();

public slots:
    void setRadius(qreal r);
    void setName(QString name);
    void setStar(const Star &star);
};

#endif // QSTARITEM_H
