#include "db_operations.h"

db_operations::db_operations(const QString& path)
{
   m_db = QSqlDatabase::addDatabase("QSQLITE");
   m_db.setDatabaseName(path);

   if (!m_db.open())
   {
      qDebug() << "Error: connection with database fail";
   }
   else
   {
      qDebug() << "Database: connection ok";
   }
}
bool db_operations::insert_word(const QString& src,const QString& dst,int type)
{
    QSqlQuery query;

    query.prepare("INSERT INTO isichazamazwi (type, src, dst) "
                   "VALUES (:type, :src, :dst)");

    try {

        query.bindValue(":src", src);
        query.bindValue(":dst", dst);
        query.bindValue(":type", type);
        query.exec();

    } catch (...) {

        return false;

    }

    return true;
}

bool db_operations::delete_word(const QString &src, const QString &dst, int type)
{
    return true;
}

bool db_operations::update_word(const QString &src, const QString &dst, int type)
{
    return true;
}
