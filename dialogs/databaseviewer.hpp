#ifndef DATABASEVIEWER_HPP
#define DATABASEVIEWER_HPP

#include <core/databasemanager.hpp>
#include <dialogs/materialdialog.hpp>

#include <QTableWidget>
#include <QHeaderView>
#include <QComboBox>
#include <QLineEdit>
#include <QEventLoop>

class DatabaseViewer : public MaterialDialog
{
public:
    explicit DatabaseViewer(QWidget *parent = 0);
    ~DatabaseViewer();

    void exec();

    enum ViewType { Daily, AllTime };
    void setViewType(ViewType);

protected:
    void keyReleaseEvent(QKeyEvent *event);

private:
    QEventLoop *eventLoop;

private:
    QVBoxLayout *m_layout;
    QHBoxLayout *m_header;

    QComboBox *ui_monthSelector;
    QComboBox *ui_categorySelector;
    QLineEdit *ui_search;
    QTableWidget *ui_view;

    QFont *font_default;
    QFont *font_italic;
    QFont *font_bold;
    QFont *font_boldMonospace;
    QFont *font_monospace;

    void readDatabase();

    QString totalCategoryCalculator(const QList<DatabaseManager::DatabaseEntry> &entries, DatabaseManager::EntryType type);
    QString totalCategoryDiff(const QList<DatabaseManager::DatabaseEntry> &entries);

    void buildMonthSelector();
    void selectMonth(const QDate &date);
    void changeMonth(int index);

    void buildCategorySelector();
    void buildCategorySelector(DatabaseManager::EntryType);
    void filterByCategory(int index);

    QDate m_date;
    DatabaseManager::DatabaseCategory m_category;
    ViewType m_type;
};

#endif // DATABASEVIEWER_HPP
