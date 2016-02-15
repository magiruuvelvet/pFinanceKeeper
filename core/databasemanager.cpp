#include <core/databasemanager.hpp>
#include <core/appsettings.hpp>

#include <QFile>
#include <QDebug>
DatabaseManager::DatabaseManager()
{
    // Database file = ${ConfigPath}/book.db
    this->m_dbPath = AppSettings::i()->ConfigPath + QString::fromUcs4(std::vector<uint>({98, 111, 111, 107, 46, 100, 98}).data(), 7);

    // QSqlDatabase Driver = QSQLITE
    this->m_dbName = QString::fromUcs4(std::vector<uint>({81, 83, 81, 76, 73, 84, 69}).data(), 7);

    /* ~~~ SQLite Queries ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        SELECT QVector(83, 69, 76, 69, 67, 84) 6
        SELECT * FROM QVector(83, 69, 76, 69, 67, 84, 32, 42, 32, 70, 82, 79, 77) 13
        FROM QVector(70, 82, 79, 77) 4
        WHERE QVector(87, 72, 69, 82, 69) 5
        IS QVector(73, 83) 2
        AND QVector(65, 78, 68) 3
        SET QVector(83, 69, 84) 3
        total QVector(116, 111, 116, 97, 108) 5
        INSERT INTO QVector(73, 78, 83, 69, 82, 84, 32, 73, 78, 84, 79) 11
        DELETE FROM QVector(68, 69, 76, 69, 84, 69, 32, 70, 82, 79, 77) 11
        UPDATE QVector(85, 80, 68, 65, 84, 69) 6
        ORDER BY QVector(79, 82, 68, 69, 82, 32, 66, 89) 8
        CREATE TABLE QVector(67, 82, 69, 65, 84, 69, 32, 84, 65, 66, 76, 69) 12
        TEXT QVector(84, 69, 88, 84) 4
        INT QVector(73, 78, 84) 3
        NUMERIC QVector(78, 85, 77, 69, 82, 73, 67) 7
        NOT NULL QVector(78, 79, 84, 32, 78, 85, 76, 76) 8
        " QVector(34) 1
        ( QVector(40) 1
        ) QVector(41) 1
        , QVector(44) 1
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    this->sqlite_select = this->sqlite_create_query({83, 69, 76, 69, 67, 84});
    this->sqlite_selectAllFrom = this->sqlite_create_query({83, 69, 76, 69, 67, 84, 32, 42, 32, 70, 82, 79, 77});
    this->sqlite_values = this->sqlite_create_query({86, 65, 76, 85, 69, 83});
    this->sqlite_from = this->sqlite_create_query({70, 82, 79, 77});
    this->sqlite_where = this->sqlite_create_query({87, 72, 69, 82, 69});
    this->sqlite_except = this->sqlite_create_query({69, 88, 67, 69, 80, 84});
    this->sqlite_is = this->sqlite_create_query({73, 83});
    this->sqlite_and = this->sqlite_create_query({65, 78, 68});
    this->sqlite_set = this->sqlite_create_query({83, 69, 84});
    this->sqlite_total = this->sqlite_create_query({116, 111, 116, 97, 108});
    this->sqlite_count = this->sqlite_create_query({99, 111, 117, 110, 116, 40, 42, 41});
    this->sqlite_max = this->sqlite_create_query({109, 97, 120});
    this->sqlite_insertInto = this->sqlite_create_query({73, 78, 83, 69, 82, 84, 32, 73, 78, 84, 79});
    this->sqlite_deleteFrom = this->sqlite_create_query({68, 69, 76, 69, 84, 69, 32, 70, 82, 79, 77});
    this->sqlite_update = this->sqlite_create_query({85, 80, 68, 65, 84, 69});
    this->sqlite_orderBy = this->sqlite_create_query({79, 82, 68, 69, 82, 32, 66, 89});
    this->sqlite_createTable = this->sqlite_create_query({67, 82, 69, 65, 84, 69, 32, 84, 65, 66, 76, 69});

    this->sqlite_text = this->sqlite_create_query({84, 69, 88, 84});
    this->sqlite_int = this->sqlite_create_query({73, 78, 84});
    this->sqlite_numeric = this->sqlite_create_query({78, 85, 77, 69, 82, 73, 67});
    this->sqlite_notNull = this->sqlite_create_query({78, 79, 84, 32, 78, 85, 76, 76});
    this->sqlite_space = this->sqlite_create_query({32});

    this->sqlite_quote = this->sqlite_create_query({34});
    this->sqlite_comma = this->sqlite_create_query({44, 32});
    this->sqlite_array_begin = this->sqlite_create_query({40});
    this->sqlite_array_close = this->sqlite_create_query({41});

    this->table_categories = this->sqlite_create_query({34, 99, 97, 116, 101, 103, 111, 114, 105, 101, 115, 34});
    this->row_name = this->sqlite_create_query({34, 110, 97, 109, 101, 34});
    this->row_id = this->sqlite_create_query({34, 105, 100, 34});
    this->row_order = this->sqlite_create_query({34, 111, 114, 100, 101, 114, 34});
    this->row_type = this->sqlite_create_query({34, 116, 121, 112, 101, 34});
    this->row_day = this->sqlite_create_query({34, 100, 97, 121, 34});
    this->row_desc = this->sqlite_create_query({34, 100, 101, 115, 99, 34});
    this->row_category = this->sqlite_create_query({34, 99, 97, 116, 101, 103, 111, 114, 121, 34});
    this->row_retourfrom = this->sqlite_create_query({34, 114, 101, 116, 111, 117, 114, 102, 114, 111, 109, 34});
    this->row_retourdesc = this->sqlite_create_query({34, 114, 101, 116, 111, 117, 114, 100, 101, 115, 99, 34});
    this->row_amount = this->sqlite_create_query({34, 97, 109, 111, 117, 110, 116, 34});
    this->row_sqlite_master = this->sqlite_create_query({34, 115, 113, 108, 105, 116, 101, 95, 109, 97, 115, 116, 101, 114, 34});
    this->row_table = this->sqlite_create_query({34, 116, 97, 98, 108, 101, 34});

    this->date_format = this->sqlite_create_query({77, 77, 45, 121, 121, 121, 121});
    this->day_format = this->sqlite_create_query({100, 100});

    this->m_db = QSqlDatabase::addDatabase(this->m_dbName);
    this->m_db.setDatabaseName(this->m_dbPath);
}

QString DatabaseManager::sqlite_create_query(const std::vector<uint> &data)
{
    return QString::fromUcs4(data.data(), data.size());
}

DatabaseManager::~DatabaseManager()
{
    (void) this->m_db.commit();
    this->m_db.close();
    this->m_db.removeDatabase(this->m_dbName);

    this->m_dbPath.clear();
    this->m_dbName.clear();

    this->sqlite_select.clear();
    this->sqlite_selectAllFrom.clear();
    this->sqlite_values.clear();
    this->sqlite_from.clear();
    this->sqlite_where.clear();
    this->sqlite_except.clear();
    this->sqlite_is.clear();
    this->sqlite_and.clear();
    this->sqlite_set.clear();
    this->sqlite_total.clear();
    this->sqlite_count.clear();
    this->sqlite_max.clear();
    this->sqlite_insertInto.clear();
    this->sqlite_deleteFrom.clear();
    this->sqlite_update.clear();
    this->sqlite_orderBy.clear();
    this->sqlite_createTable.clear();

    this->sqlite_text.clear();
    this->sqlite_int.clear();
    this->sqlite_numeric.clear();
    this->sqlite_notNull.clear();
    this->sqlite_space.clear();

    this->sqlite_quote.clear();
    this->sqlite_comma.clear();
    this->sqlite_array_begin.clear();
    this->sqlite_array_close.clear();

    this->table_categories.clear();
    this->row_name.clear();
    this->row_id.clear();
    this->row_order.clear();
    this->row_type.clear();
    this->row_day.clear();
    this->row_desc.clear();
    this->row_category.clear();
    this->row_retourfrom.clear();
    this->row_retourdesc.clear();
    this->row_amount.clear();
    this->row_sqlite_master.clear();
    this->row_table.clear();

    this->date_format.clear();
    this->day_format.clear();

    delete this;
}

DatabaseManager *DatabaseManager::i()
{
    static DatabaseManager *instance = new DatabaseManager();
    return instance;
}

bool DatabaseManager::open()
{
    if (this->m_db.open()) {
        this->createCategoryTable();
        this->createMonthTable();
        return true;
    }

    return false;
}

bool DatabaseManager::remove()
{
    return QFile::remove(this->m_dbPath);
}

void DatabaseManager::addEntry(const DatabaseEntry &entry)
{
    if (entry.isRetourEntry)
        this->addRetourEntry(entry.date, entry.desc, entry.retourDesc, entry.amount);
    else
        this->addEntry(entry.date, entry.type, entry.desc, entry.category, entry.amount);
}

void DatabaseManager::addEntries(const QList<DatabaseEntry> &entries)
{
    for (const DatabaseEntry &e : entries)
        this->addEntry(e);
}

void DatabaseManager::addEntry(const QDate &date, EntryType type, const QString &desc, int category, double amount)
{
    this->createMonthTable(date);
    QSqlQuery( this->sqlite_insertInto + this->sqlite_space + this->sqlite_quote + date.toString(this->date_format) + this->sqlite_quote + this->sqlite_space +
               this->sqlite_array_begin +
               this->row_day + this->sqlite_comma +
               this->row_type + this->sqlite_comma +
               this->row_desc + this->sqlite_comma +
               this->row_category + this->sqlite_comma +
               this->row_retourfrom + this->sqlite_comma +
               this->row_retourdesc + this->sqlite_comma +
               this->row_amount +
               this->sqlite_array_close + this->sqlite_space + this->sqlite_values + this->sqlite_space + this->sqlite_array_begin +
               this->sqlite_quote + date.toString(this->day_format) + this->sqlite_quote + this->sqlite_comma +
               this->sqlite_quote + QString::number(type) + this->sqlite_quote + this->sqlite_comma +
               this->sqlite_quote + desc + this->sqlite_quote + this->sqlite_comma +
               this->sqlite_quote + QString::number(category) + this->sqlite_quote + this->sqlite_comma +
               this->sqlite_quote + QString::number(0) + this->sqlite_quote + this->sqlite_comma +
               "NULL" + this->sqlite_comma +
               this->sqlite_quote + QString::number(amount, 'f', 2) + this->sqlite_quote + this->sqlite_array_close,
               this->m_db
             );
}

void DatabaseManager::addRetourEntry(const QDate &date, const QString &desc, const QString &retourDesc, double amount)
{
    this->createMonthTable(date);
    QSqlQuery( this->sqlite_insertInto + this->sqlite_space + this->sqlite_quote + date.toString(this->date_format) + this->sqlite_quote + this->sqlite_space +
               this->sqlite_array_begin +
               this->row_day + this->sqlite_comma +
               this->row_type + this->sqlite_comma +
               this->row_desc + this->sqlite_comma +
               this->row_category + this->sqlite_comma +
               this->row_retourfrom + this->sqlite_comma +
               this->row_retourdesc + this->sqlite_comma +
               this->row_amount +
               this->sqlite_array_close + this->sqlite_space + this->sqlite_values + this->sqlite_space + this->sqlite_array_begin +
               this->sqlite_quote + date.toString(this->day_format) + this->sqlite_quote + this->sqlite_comma +
               this->sqlite_quote + QString::number(Earning) + this->sqlite_quote + this->sqlite_comma +
               this->sqlite_quote + desc + this->sqlite_quote + this->sqlite_comma +
               this->sqlite_quote + QString::number(0) + this->sqlite_quote + this->sqlite_comma +
               this->sqlite_quote + QString::number(1) + this->sqlite_quote + this->sqlite_comma +
               this->sqlite_quote + retourDesc + this->sqlite_quote + this->sqlite_comma +
               this->sqlite_quote + QString::number(amount, 'f', 2) + this->sqlite_quote + this->sqlite_array_close,
               this->m_db
             );
}

void DatabaseManager::addCategory(const QString &name, EntryType type)
{
    // SELECT max("id") FROM "categories" WHERE "type" IS [type]
    QSqlQuery counter( this->sqlite_select + this->sqlite_space + this->sqlite_max + this->sqlite_array_begin + this->row_id + this->sqlite_array_close + this->sqlite_space +
                       this->sqlite_from + this->sqlite_space + this->table_categories + this->sqlite_space +
                       this->sqlite_where + this->sqlite_space + this->row_type + this->sqlite_space +
                       this->sqlite_is + this->sqlite_space + QString::number(type)
                     );
    if (counter.exec()) {
        counter.next();

        QString idx = QString::number(counter.value(0).toInt() + 1);

        // INSERT INTO "categories" ("name", "id", "order", "type") VALUES ([name], [idx], [idx], [type])
        QSqlQuery( this->sqlite_insertInto + this->sqlite_space + this->table_categories + this->sqlite_space +
                   this->sqlite_array_begin +
                   this->row_name + this->sqlite_comma +
                   this->row_id + this->sqlite_comma +
                   this->row_order + this->sqlite_comma +
                   this->row_type + this->sqlite_array_close + this->sqlite_space +
                   this->sqlite_values + this->sqlite_space +
                   this->sqlite_array_begin +
                   this->sqlite_quote + name + this->sqlite_quote + this->sqlite_comma +
                   this->sqlite_quote + idx + this->sqlite_quote + this->sqlite_comma +
                   this->sqlite_quote + idx + this->sqlite_quote + this->sqlite_comma +
                   this->sqlite_quote + QString::number(type) + this->sqlite_quote + this->sqlite_array_close,
                   this->m_db
                 );

        idx.clear();
    }
}

void DatabaseManager::removeCategory(int id, EntryType type)
{
    // DELETE FROM "categories" WHERE "id" IS [id] AND "type" IS [type]
    QSqlQuery( this->sqlite_deleteFrom + this->sqlite_space + this->table_categories + this->sqlite_space +
               this->sqlite_where + this->sqlite_space + this->row_id + this->sqlite_space +
               this->sqlite_is + this->sqlite_space + QString::number(id) + this->sqlite_space +
               this->sqlite_and + this->sqlite_space + this->row_type + this->sqlite_space +
               this->sqlite_is + this->sqlite_space + QString::number(type),
               this->m_db
             );
}

void DatabaseManager::editCategory(int id, EntryType type, const QString &name)
{
    // UPDATE "categories" SET "name" = [name] WHERE "id" = [id] AND "type" = [type]
    QSqlQuery( this->sqlite_update + this->sqlite_space + this->table_categories + this->sqlite_space +
               this->sqlite_set + this->sqlite_space + this->row_name + this->sqlite_space + "=" + this->sqlite_space + this->sqlite_quote + name + this->sqlite_quote + this->sqlite_space +
               this->sqlite_where + this->sqlite_space + this->row_id + this->sqlite_space + "=" + this->sqlite_space + this->sqlite_quote + QString::number(id) + this->sqlite_quote + this->sqlite_space +
               this->sqlite_and + this->sqlite_space + this->row_type + this->sqlite_space + "=" + this->sqlite_space + this->sqlite_quote + QString::number(type) + this->sqlite_quote,
               this->m_db
             );
}

void DatabaseManager::editCategory(int id, EntryType type, int newPosition)
{
    // UPDATE "categories" SET "order" = [newPosition] WHERE "id" = [id] AND "type" = [type]
    QSqlQuery( this->sqlite_update + this->sqlite_space + this->table_categories + this->sqlite_space +
               this->sqlite_set + this->sqlite_space + this->row_order + this->sqlite_space + "=" + this->sqlite_space + this->sqlite_quote + QString::number(newPosition) + this->sqlite_quote + this->sqlite_space +
               this->sqlite_where + this->sqlite_space + this->row_id + this->sqlite_space + "=" + this->sqlite_space + this->sqlite_quote + QString::number(id) + this->sqlite_quote + this->sqlite_space +
               this->sqlite_and + this->sqlite_space + this->row_type + this->sqlite_space + "=" + this->sqlite_space + this->sqlite_quote + QString::number(type) + this->sqlite_quote,
               this->m_db
             );
}

QList<DatabaseManager::DatabaseEntry> DatabaseManager::entries(const QDate &date, bool skipRetourEntries) const
{
    // SELECT * FROM "MM-yyyy" {WHERE "retourfrom" IS 0}
    QString query_string = this->sqlite_selectAllFrom + this->sqlite_space + this->sqlite_quote + date.toString(this->date_format) + this->sqlite_quote;
    if (skipRetourEntries) query_string.append(this->sqlite_space + this->sqlite_where + this->sqlite_space +
                                               this->row_retourfrom + this->sqlite_space + this->sqlite_is + this->sqlite_space + QString::number(0));

    QList<DatabaseEntry> m_entries;

    QSqlQuery query(query_string);

    if (query.exec()) {
        query.next();

        DatabaseEntry buf;

        do {
            QSqlRecord record = query.record();

            buf.day           = record.value(0).toInt();
            buf.type          = static_cast<EntryType>(record.value(1).toInt());
            buf.desc          = record.value(2).toString();
            buf.category      = record.value(3).toInt();
            buf.isRetourEntry = record.value(4).toBool();
            buf.retourDesc    = record.value(5).toString();
            buf.amount        = record.value(6).toDouble();
            buf.date          = date;

            m_entries.push_back(buf);
        } while (query.next());
    }

    return m_entries;
}

QList<DatabaseManager::DatabaseEntry> DatabaseManager::entries(bool skipRetourEntries) const
{
    QList<DatabaseEntry> m_totalEntries;
    QList<DatabaseEntry> m_entriesBuf;

    for (const QString &current : this->tables()) {
        m_entriesBuf = this->entries(QDate::fromString(current, this->date_format), skipRetourEntries);

        for (DatabaseEntry &e : m_entriesBuf)
            m_totalEntries.push_back(e);
    }

    m_entriesBuf.clear();
    return m_totalEntries;
}

QList<DatabaseManager::DatabaseEntry> DatabaseManager::dailyEntries(const QDate &date) const
{
    // SELECT * FROM "MM-yyyy" WHERE "day" IS [date.day()]
    QString query_string = this->sqlite_selectAllFrom + this->sqlite_space + this->sqlite_quote + date.toString(this->date_format) + this->sqlite_quote + this->sqlite_space +
                           this->sqlite_where + this->sqlite_space + this->row_day + this->sqlite_space + this->sqlite_is + this->sqlite_space + date.toString(this->day_format);

    QList<DatabaseEntry> m_entries;

    QSqlQuery query(query_string);

    if (query.exec()) {
        query.next();

        DatabaseEntry buf;

        do {
            QSqlRecord record = query.record();

            buf.day           = record.value(0).toInt();
            buf.type          = static_cast<EntryType>(record.value(1).toInt());
            buf.desc          = record.value(2).toString();
            buf.category      = record.value(3).toInt();
            buf.isRetourEntry = record.value(4).toBool();
            buf.retourDesc    = record.value(5).toString();
            buf.amount        = record.value(6).toDouble();
            buf.date          = date;

            m_entries.push_back(buf);
        } while (query.next());
    }

    return m_entries;
}

DatabaseManager::DatabaseCategory DatabaseManager::category(int id, EntryType type) const
{
    if (id == 0) {
        DatabaseCategory buf;
        buf.name = QObject::trUtf8("Retour");
        buf.id   = 0;
        buf.type = Earning;
        return buf;
    }

    // SELECT "name" FROM "categories" WHERE "id" IS [id] AND "type" IS [type]
    QSqlQuery query( this->sqlite_select + this->sqlite_space + this->row_name + this->sqlite_space + this->sqlite_from + this->sqlite_space + this->table_categories + this->sqlite_space +
                     this->sqlite_where + this->sqlite_space + this->row_id + this->sqlite_space + this->sqlite_is + this->sqlite_space + QString::number(id) + this->sqlite_space +
                     this->sqlite_and + this->sqlite_space + this->row_type + this->sqlite_space + this->sqlite_is + this->sqlite_space + QString::number(type)
                   );
    if (query.exec()) {
        query.next();
        DatabaseCategory buf;
        buf.name = query.value(0).toString();
        buf.id   = id;
        buf.type = type;
        return buf;
    }

    return DatabaseCategory();
}

QList<DatabaseManager::DatabaseCategory> DatabaseManager::categories(EntryType type, bool sorted) const
{   
    // SELECT "name","id" FROM "categories" WHERE "type" IS [type] {ORDER BY "order"}
    QString query_string = this->sqlite_select + this->sqlite_space + this->row_name + this->sqlite_comma + this->row_id + this->sqlite_space +
                           this->sqlite_from + this->sqlite_space + this->table_categories + this->sqlite_space +
                           this->sqlite_where + this->sqlite_space + this->row_type + this->sqlite_space + this->sqlite_is + this->sqlite_space + QString::number(type);
    if (sorted) query_string.append(this->sqlite_space + this->sqlite_orderBy + this->sqlite_space + this->row_order);

    QList<DatabaseCategory> m_categories;

    QSqlQuery query(query_string);

    if (query.exec()) {
        query.next();

        do {
            DatabaseCategory buf;
            buf.name = query.record().value(0).toString();
            buf.id   = query.record().value(1).toInt();
            buf.type = type;
            m_categories.push_back(buf);
        } while (query.next());
    }

    return m_categories;
}

QStringList DatabaseManager::tables() const
{
    // SELECT "name" FROM "sqlite_master" WHERE "type" = "table" EXCEPT SELECT "name" FROM "sqlite_master" WHERE "name" IS "categories"
    QSqlQuery tableQuery( this->sqlite_select + this->sqlite_space + this->row_name + this->sqlite_space +
                          this->sqlite_from + this->sqlite_space + this->row_sqlite_master + this->sqlite_space +
                          this->sqlite_where + this->sqlite_space + this->row_type + this->sqlite_space + "=" + this->sqlite_space + this->row_table +
                          this->sqlite_except + this->sqlite_space + this->sqlite_select + this->sqlite_space + this->row_name + this->sqlite_space +
                          this->sqlite_from + this->sqlite_space + this->row_sqlite_master + this->sqlite_space +
                          this->sqlite_where + this->sqlite_space + this->row_name + this->sqlite_space + this->sqlite_is + this->sqlite_space +
                          this->table_categories
                        );
    if (tableQuery.exec()) {
        tableQuery.next();

        QStringList tables;
        do { tables.push_back(tableQuery.value(0).toString()); } while (tableQuery.next());
        return tables;
    }

    return QStringList();
}

int DatabaseManager::tableCount() const
{
    // SELECT count(*) FROM "sqlite_master" WHERE "type" = "table"
    QSqlQuery tableQuery( this->sqlite_select + this->sqlite_space + this->sqlite_count + this->sqlite_space +
                          this->sqlite_from + this->sqlite_space + this->row_sqlite_master + this->sqlite_space +
                          this->sqlite_where + this->sqlite_space + this->row_type + this->sqlite_space + "=" + this->sqlite_space + this->row_table
                        );
    if (tableQuery.exec()) {
        tableQuery.next();

        return tableQuery.value(0).toInt() - 1;
    }

    return 0;
}

double DatabaseManager::totalEarnings(const QDate &date) const
{
    return this->calculationHelper(date, Earning);
}

double DatabaseManager::totalEarnings() const
{
    return this->calculationHelper(Earning);
}

double DatabaseManager::totalExpenses(const QDate &date) const
{
    return this->calculationHelper(date, Expense);
}

double DatabaseManager::totalExpenses() const
{
    return this->calculationHelper(Expense);
}

void DatabaseManager::createCategoryTable()
{
    // CREATE TABLE "categories" ("name" TEXT NOT NULL, "id" INT NOT NULL, "order" INT NOT NULL, "type" INT NOT NULL)
    QSqlQuery( this->sqlite_createTable + this->sqlite_space + this->table_categories + this->sqlite_space + this->sqlite_array_begin +
               this->row_name + this->sqlite_space + this->sqlite_text + this->sqlite_space + this->sqlite_notNull + this->sqlite_comma +
               this->row_id + this->sqlite_space + this->sqlite_int + this->sqlite_space + this->sqlite_notNull + this->sqlite_comma +
               this->row_order + this->sqlite_space + this->sqlite_int + this->sqlite_space + this->sqlite_notNull + this->sqlite_comma +
               this->row_type + this->sqlite_space + this->sqlite_int + this->sqlite_space + this->sqlite_notNull + this->sqlite_array_close,
               this->m_db
             );
}

void DatabaseManager::createMonthTable()
{
    this->createMonthTable(QDate::currentDate());
}

void DatabaseManager::createMonthTable(const QDate &date)
{
    // CREATE TABLE "MM-yyyy" (
    //  "day" INT NOT NULL,
    //  "type" INT NOT NULL,
    //  "desc" TEXT NOT NULL,
    //  "category" INT NOT NULL,
    //  "retourfrom" INT NOT NULL,
    //  "retourdesc" TEXT,
    //  "amount" NUMERIC NOT NULL)
    QSqlQuery( this->sqlite_createTable + this->sqlite_space + this->sqlite_quote + date.toString(this->date_format) + this->sqlite_quote +
               this->sqlite_space + this->sqlite_array_begin +
               this->row_day + this->sqlite_space + this->sqlite_int + this->sqlite_space + this->sqlite_notNull + this->sqlite_comma +
               this->row_type + this->sqlite_space + this->sqlite_int + this->sqlite_space + this->sqlite_notNull + this->sqlite_comma +
               this->row_desc + this->sqlite_space + this->sqlite_text + this->sqlite_space + this->sqlite_notNull + this->sqlite_comma +
               this->row_category + this->sqlite_space + this->sqlite_int + this->sqlite_space + this->sqlite_notNull + this->sqlite_comma +
               this->row_retourfrom + this->sqlite_space + this->sqlite_int + this->sqlite_space + this->sqlite_notNull + this->sqlite_comma +
               this->row_retourdesc + this->sqlite_space + this->sqlite_text + this->sqlite_comma +
               this->row_amount + this->sqlite_space + this->sqlite_numeric + this->sqlite_space + this->sqlite_notNull + this->sqlite_array_close,
               this->m_db
             );
}

double DatabaseManager::calculationHelper(const QDate &date, EntryType type) const
{
    // SELECT total("amount") FROM "MM-yyyy" WHERE "type" IS [type]
    QSqlQuery totalQuery( this->sqlite_select + this->sqlite_space + this->sqlite_total +
                          this->sqlite_array_begin + this->row_amount + this->sqlite_array_close + this->sqlite_space +
                          this->sqlite_from + this->sqlite_space + this->sqlite_quote + date.toString(this->date_format) + this->sqlite_quote + this->sqlite_space +
                          this->sqlite_where + this->sqlite_space + this->row_type + this->sqlite_space + this->sqlite_is + this->sqlite_space + QString::number(type)
                        );
    if (totalQuery.exec()) {
        totalQuery.next();
        return totalQuery.value(0).toDouble();
    }

    return 0.0;
}

double DatabaseManager::calculationHelper(EntryType type) const
{
    double m_total = 0.0;

    for (const QString &current : this->tables())
        m_total += this->calculationHelper(QDate::fromString(current, this->date_format), type);

    return m_total;
}
