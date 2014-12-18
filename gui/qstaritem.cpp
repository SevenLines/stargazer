#include "qstaritem.h"

#include <QFont>
#include <QPen>
#include <QDebug>



QStarItem::QStarItem(qreal x, qreal y, const Star &star, QGraphicsItem *parent)
{
    this->starRadius = 0.025;

    nameItem = new QGraphicsTextItem(star.Name);
//    addToGroup(nameItem);

    ellipseItem = new QGraphicsEllipseItem();
    ellipseItem->setPen(QPen(QBrush(Qt::yellow),0));
    ellipseItem->setBrush(QBrush(Qt::yellow));
    addToGroup(ellipseItem);

    setPos(x, y);
    setStar(star);
}

QStarItem::~QStarItem()
{
}

void QStarItem::setRadius(qreal r)
{
    ellipseItem->setRect(ellipseItem->x() - r*0.5, ellipseItem->y() - r*0.5, r, r);
}

void QStarItem::setName(QString name)
{
    nameItem->setPlainText(name);
}

void QStarItem::setStar(const Star &star)
{
    mStar = star;

    qreal w = this->starRadius / (mStar.Mag ?  mStar.Mag : 1);
    ellipseItem->setRect( -w *0.5, -w *0.5, w, w);

    if (w > 0) {
        QFont font;
        font.setPointSizeF(w);
        nameItem->setFont(font);
    }
}

