#ifndef SKY_H
#define SKY_H

#include <QList>
#include <QMap>
#include <QObject>
#include <QSqlDatabase>
#include <star.h>

class Sky : public QObject
{
    Q_OBJECT

private:
    QString fileSQLProjection;
    QString fileSQLLoadExtension;
    QString fileSQLEdges;

    qreal mCenterRA;
    qreal mCenterDec;

    QSqlDatabase db;
    QList<Star> stars;
    QMap<int, QList<int> > edges;

public:
    Sky(QObject *parent=0);

    qreal centerRA() const;
    void setCenterRA(const qreal &value);

    qreal centerDec() const;
    void setCenterDec(const qreal &value);

public slots:
    void fetchStars(std::function<void(qreal,qreal,Star)> starCallback, std::function<void(qreal,qreal,qreal,qreal)> edgeCallback);
    void fetchEdges();

signals:
    void fetchStar(qreal x, qreal y, const Star &star);
    void centerRA_changed(qreal value);
    void centerDec_changed(qreal value);
};

#endif // SKY_H
