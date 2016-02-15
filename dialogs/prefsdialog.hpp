#ifndef PREFSDIALOG_HPP
#define PREFSDIALOG_HPP

#include <QListWidget>

#include <dialogs/materialdialog.hpp>
#include <core/databasemanager.hpp>

class PrefsDialog : public MaterialDialog
{
    Q_OBJECT

public:
    explicit PrefsDialog(QWidget *parent = 0);
    ~PrefsDialog();

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void updateEarningCategories();
    void updateExpenseCategories();
    void updateCategoriesAbstract(DatabaseManager::EntryType);

    void addEarningCategory();
    void addExpenseCategory();
    void addCategoryAbstract(DatabaseManager::EntryType);

    void removeEarningCategory();
    void removeExpenseCategory();
    void removeCategoryAbstract(DatabaseManager::EntryType);

private:
    QVBoxLayout *m_layout;

    void buildCategoryLists();
    void buildCategoryList(DatabaseManager::EntryType);

    QFont *font_category;
    QFont *font_default;
    QFont *font_defaultBold;

    QFrame *ui_categoryEditor_field;
    QLabel *ui_categoryEditor_field_title;
    QListWidget *ui_categoryEditor_earnings;
    QListWidget *ui_categoryEditor_expenses;
    QLabel *ui_categoryEditor_earnings_label;
    QLabel *ui_categoryEditor_expenses_label;
    QGridLayout *ui_categoryEditor_layout;

    MaterialButton *ui_categoryEditor_earning_addCatBtn;
    MaterialButton *ui_categoryEditor_expense_addCatBtn;
    void ui_categoryEditor_createAddButton(MaterialButton *btn, const QString &tooltip);

    MaterialButton *ui_categoryEditor_earning_removeCatBtn;
    MaterialButton *ui_categoryEditor_expense_removeCatBtn;
    void ui_categoryEditor_createRemoveButton(MaterialButton *btn, const QString &tooltip);

    void ui_categoryEditor_createAbstractButton(MaterialButton *btn, const QString &tooltip);
};

extern PrefsDialog *prefsDialog;

#endif // PREFSDIALOG_HPP
