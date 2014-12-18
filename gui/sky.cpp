#include <QDebug>
#include <QDir>
#include <QSqlQuery>
#include <QSqlError>
#include "sky.h"


qreal Sky::centerRA() const
{
    return mCenterRA;
}

void Sky::setCenterRA(const qreal &value)
{
    if (mCenterRA != value) {
        mCenterRA = value;
        emit centerRA_changed(mCenterRA);
    } else {
        mCenterRA = value;
    }
}

qreal Sky::centerDec() const
{
    return mCenterDec;
}

void Sky::setCenterDec(const qreal &value)
{
    if (mCenterDec != value) {
        mCenterDec = value;
        emit centerDec_changed(mCenterDec);
    } else {
        mCenterDec = value;
    }
}
Sky::Sky(QObject *parent) :
    QObject(parent),
    fileSQLLoadExtension("sql/load_extension.sql"),
    fileSQLProjection("sql/ortogonal.sql"),
    fileSQLEdges("sql/edges.sql"),
    mCenterDec(0),
    mCenterRA(0)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("assets/GenStar.sqlite");
    fetchEdges();
}

void Sky::fetchStars(std::function<void(qreal, qreal, Star)> starCallback, std::function<void(qreal, qreal, qreal, qreal)> edgeCallback)
{
    if (db.open()) {
        QString qText, qTextProjection, qTextEdges;

        QFile file(fileSQLLoadExtension);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << file.errorString();
            return;
        }

        qText = file.readAll();
        file.close();

        qText.replace("{appDir}", QDir::currentPath());
        QSqlQuery queryLoadExtensions(qText);
        if (!queryLoadExtensions.exec()) {
            qDebug() << qText;
            qDebug() << queryLoadExtensions.lastError().text();
            return;
        }

        file.setFileName(fileSQLProjection);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << file.errorString();
            return;
        }
        qTextProjection = file.readAll();
        file.close();

        qTextProjection.replace("{centerRA}", QString::number(mCenterRA));
        qTextProjection.replace("{centerDec}", QString::number(mCenterDec));
//        qText.replace("{const_id}", QString::number(const_id));
        QSqlQuery query(qTextProjection);

        qreal x1, y1, x2, y2, RA, Dec, Mag;
        Star star;

        bool    skipMag = false,
                skipRA = false,
                skipDec = false,
                skipName = false,
                skipName_rus = false;

        while (query.next()) {
            x1 = query.value("x").toFloat();
            y1 = query.value("y").toFloat();

            if (query.value("id").isValid()) star.id = query.value("id").toInt();
            if (!skipMag && query.value("Mag").isValid()) star.Mag = query.value("Mag").toInt(); else skipMag = true;
            if (!skipRA && query.value("RA").isValid()) star.RA = query.value("RA").toFloat(); else skipRA = true;
            if (!skipDec && query.value("Dec").isValid()) star.Dec = query.value("Dec").toFloat(); else skipDec = true;
            if (!skipName && query.value("Name").isValid()) star.Name = query.value("Name").toString(); else skipName = true;
            if (!skipName_rus && query.value("Name_rus").isValid()) star.Name_rus = query.value("Name_rus").toFloat(); else skipName_rus = true;
            star.x = x1;
            star.y = y1;

            if (starCallback)
                starCallback(x1, y1, star);
        }

        file.setFileName(fileSQLEdges);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << file.errorString();
            return;
        }
        qTextEdges = file.readAll();
        qTextEdges.replace("{projection_script}", qTextProjection);
        file.close();

        QSqlQuery query2(qTextEdges);
        while(query2.next()) {
            x1 = query2.value("x1").toFloat();
            y1 = query2.value("y1").toFloat();
            x2 = query2.value("x2").toFloat();
            y2 = query2.value("y2").toFloat();
            if (edgeCallback)
                edgeCallback(x1, y1, x2, y2);
        }

        db.close();
    } else {
        qDebug() << db.lastError().text();
    }
}

void Sky::fetchEdges()
{
    if (db.open()) {
        QFile file(fileSQLEdges);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << file.errorString();
            return;
        }
        QString text = file.readAll();
        file.close();

        int star_id1, star_id2, const_id;
        QSqlQuery query(text);
        while(query.next()) {
            star_id1 = query.value("star_id1").toInt();
            star_id2 = query.value("star_id2").toInt();

            edges[star_id1].append(star_id2);
            edges[star_id2].append(star_id1);
        }
    }
}
