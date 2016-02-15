#ifndef ENTRYCREATOR_HPP
#define ENTRYCREATOR_HPP

#include <dialogs/materialdialog.hpp>
#include <dialogs/noticedialog.hpp>
#include <core/databasemanager.hpp>

#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>
#include <QDateEdit>
#include <QCalendarWidget>
#include <QAbstractItemView>
#include <QFrame>

class EntryCreator : public MaterialDialog
{
    Q_OBJECT

public:
    explicit EntryCreator(DatabaseManager::EntryType type, QWidget *parent = 0);
    ~EntryCreator();

    void close();

private:
    QLabel *addLabel(QLabel*, const QString &text, int row);
    void addSpacer(int row);

    void disable();
    void enable();

    void buildCategoryList();
    void buildRetourList();

private slots:
    void saveEntry();
    void cancel();

    void updateRetourFromState();

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    QVBoxLayout *m_layout;
    QSpacerItem *spacer_bottom;

    QHBoxLayout *layout_bottom;
    QFrame      *line_bottom;
    QFrame      *line_middle;
    QSpacerItem *layout_bottom_spacer;

    QFont *m_font, *m_font_amount;
    QGridLayout *m_grid;
    QGridLayout *m_grid2;

    MaterialButton *btnComplete;
#ifdef Q_OS_ANDROID
    MaterialButton *btnCancel;
#endif

    QLabel *label_category,
           *label_desc,
           *label_date,
           *label_amount;

    QCheckBox *cb_retourfrom;

    QComboBox *m_category;
    QComboBox *m_retourfrom;
    QLineEdit *m_desc;
    QDateEdit *m_date;
    QLineEdit *m_amount;

    NoticeDialog *d_cancel;
    NoticeDialog *d_success;
    NoticeDialog *d_incomplete;

    DatabaseManager::EntryType m_type;
};

#endif // ENTRYCREATOR_HPP
