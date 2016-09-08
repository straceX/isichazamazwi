#ifndef DB_OPERATIONS_H
#define DB_OPERATIONS_H

#include <QSqlDatabase>
#include <QDebug>

class db_operations
{
    public:
        db_operations(const QString& path);
    private:

        QSqlDatabase m_db;
};



#endif // DB_OPERATIONS_H
