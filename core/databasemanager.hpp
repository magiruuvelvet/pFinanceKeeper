#ifndef DATABASEMANAGER_HPP
#define DATABASEMANAGER_HPP

#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlField>
#include <QtSql/QSqlResult>

#include <QString>
#include <QDate>

class DatabaseManager
{
public:
    static DatabaseManager *i();
    ~DatabaseManager();

    bool open();
    bool remove();

    enum EntryType {
        Earning,
        Expense
    };

    struct DatabaseEntry {
        int        day;
        EntryType  type;
        QString    desc;
        int        category;
        bool       isRetourEntry;
        QString    retourDesc;
        double     amount;
        QDate      date;
    };

    struct DatabaseCategory {
        QString    name;
        int        id;
        EntryType  type;
    };

    void addEntry(const DatabaseEntry &entry);
    void addEntries(const QList<DatabaseEntry> &entries);
    void addEntry(const QDate &date, EntryType type, const QString &desc, int category, double amount);
    void addRetourEntry(const QDate &date, const QString &desc, const QString &retourDesc, double amount);

    void addCategory(const QString &name, EntryType type);
    void removeCategory(int id, EntryType type);

    void editCategory(int id, EntryType type, const QString &name);
    void editCategory(int id, EntryType type, int newPosition);

    QList<DatabaseEntry> entries(const QDate &date, bool skipRetourEntries = false) const;
    QList<DatabaseEntry> entries(bool skipRetourEntries = false) const;
    QList<DatabaseEntry> dailyEntries(const QDate &date) const;

    DatabaseCategory category(int id, EntryType type) const;
    QList<DatabaseCategory> categories(EntryType type, bool sorted = true) const;

    QStringList tables() const;
    int tableCount() const;

    double totalEarnings(const QDate &date) const;
    double totalEarnings() const;

    double totalExpenses(const QDate &date) const;
    double totalExpenses() const;

private:
    DatabaseManager();

    QSqlDatabase m_db;
    QString m_dbPath, m_dbName;

    /* protect queries against hex-editing to avoid database corruption */
    QString sqlite_select,
            sqlite_selectAllFrom,
            sqlite_values,
            sqlite_from,
            sqlite_where,
            sqlite_except,
            sqlite_is,
            sqlite_and,
            sqlite_set,
            sqlite_total,
            sqlite_count,
            sqlite_max,
            sqlite_insertInto,
            sqlite_deleteFrom,
            sqlite_update,
            sqlite_orderBy,
            sqlite_createTable;

    QString sqlite_text,
            sqlite_int,
            sqlite_numeric,
            sqlite_notNull,
            sqlite_space;

    QString sqlite_quote,
            sqlite_comma,
            sqlite_array_begin,
            sqlite_array_close;

    QString table_categories,
            row_name,
            row_id,
            row_order,
            row_type,
            row_day,
            row_desc,
            row_category,
            row_retourfrom,
            row_retourdesc,
            row_amount,
            row_sqlite_master,
            row_table;

    QString date_format,
            day_format;

    QString sqlite_create_query(const std::vector<uint> &data);

    void createCategoryTable();
    void createMonthTable();
    void createMonthTable(const QDate &date);

    double calculationHelper(const QDate &date, EntryType type) const;
    double calculationHelper(EntryType type) const;
};

#endif // DATABASEMANAGER_HPP
