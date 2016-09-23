#ifndef DB_OPERATIONS_H
#define DB_OPERATIONS_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

class db_operations
{
    public:
        db_operations(const QString& path);
        bool insert_word(const QString& src,const QString& dst,int type);
        bool update_word(const QString& src,const QString& dst,int type);
        bool delete_word(const QString& src,const QString& dst,int type);
    private:

        QSqlDatabase m_db;
};



#endif // DB_OPERATIONS_H
