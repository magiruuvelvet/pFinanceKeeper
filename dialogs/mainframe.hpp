#ifndef MAINFRAME_HPP
#define MAINFRAME_HPP

#include <QShortcut>

#include <dialogs/materialdialog.hpp>
#include <dialogs/entrycreator.hpp>
#include <dialogs/noticedialog.hpp>
#include <buttons/financebutton.hpp>

#define shortcuts private

class MainFrame : public MaterialDialog
{
    Q_OBJECT

public:
    explicit MainFrame(QWidget *parent = 0);
    ~MainFrame();

    void updateEarnings();
    void updateExpenses();

    enum class EntryDialogCount { Init, Add, Remove };
    void updateOpenEntryDialogCount(EntryDialogCount);

    void close();

public slots:
    void updateDescHovered(FinanceButton *btn);
    void updateDescUnhovered();

    void showAbout();
    void showPrefs();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    QGridLayout *financeBtnGrid;

    FinanceButton *btnEarning;
    FinanceButton *btnExpense;
    FinanceButton *btnEntries;
    FinanceButton *btnHistory;

    QFont *font_calculation;
    QFont *font_amounts;
    QGridLayout *calculation_grid;
    QLabel *labelEarnings;
    QLabel *labelExpenses;
    QLabel *totalEarnings;
    QLabel *totalExpenses;

    QFont *font_statusbar;
    QHBoxLayout *statusbar;
    QSpacerItem *statusbarSpacer;
    QLabel *btnStatus;
    QLabel *unsavedEntries;

    uint m_openEntryDialogs;
    NoticeDialog *d_unsavedEntries;

#ifndef Q_OS_ANDROID
shortcuts:
    QShortcut *s_left,
              *s_right,
              *s_up,
              *s_down;
    QShortcut *s_quit,
              *s_altF4;
#endif

private slots:
    void keyNavLeft();
    void keyNavRight();
    void keyNavUp();
    void keyNavDown();

    void btnEarningClicked();
    void btnExpenseClicked();
    void btnEntriesClicked();
    void btnHistoryClicked();
};

extern MainFrame *mainframe;

#endif // MAINFRAME_HPP
