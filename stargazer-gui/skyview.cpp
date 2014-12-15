#include "skyview.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QDir>
#include <QSqlDriver>

SkyView::SkyView(QWidget* parent)
    : QGraphicsView(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("assets/GenStar.sqlite");

    QString loadExtensionScript = QString("SELECT load_extension(\"%1/libsqlitefunctions\")").arg( QDir::currentPath());

    if (db.open()) {
        qDebug() << "cool";

        QSqlQuery queryLoadExtensions(loadExtensionScript);
        if (!queryLoadExtensions.exec()) {
            qDebug() << loadExtensionScript;
            qDebug() << queryLoadExtensions.lastError().text();
            return;
        }

        QSqlQuery query("SELECT name, Dec, RA, mag, id from Stars");
        while (query.next()) {
            stars.push_back(
                Star(query.value(0).toString(),
                     query.value(1).toFloat(),
                     query.value(2).toFloat(),
                     query.value(3).toFloat(),
                     query.value(4).toInt()));
            qDebug() << stars.last().toString();
        }

    } else {
        qDebug() << db.lastError().text();
    }

    db.close();
}
