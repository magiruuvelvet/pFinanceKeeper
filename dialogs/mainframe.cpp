#include <dialogs/mainframe.hpp>
#include <dialogs/aboutdialog.hpp>
#include <dialogs/prefsdialog.hpp>
#include <dialogs/databaseviewer.hpp>
#include <core/appsettings.hpp>
#include <core/databasemanager.hpp>

#ifdef Q_OS_ANDROID
    #define L_FONT_SIZE 40
#else
    #define L_FONT_SIZE 17
#endif

MainFrame *mainframe = nullptr;

MainFrame::MainFrame(QWidget *parent) :
    MaterialDialog(parent)
{
    this->m_layout = this->createTitleBar(AppSettings::i()->AppName, *ThemeLoader::i()->appIcon(), 2);
#ifdef Q_OS_ANDROID
    this->titlebar->createMenuButton();
#else
    createTitleBarButton(Info);
    this->titlebar->addButtonSpacer(15);
    createTitleBarButton(Prefs);
    this->titlebar->addButtonSpacer(15);
    createTitleBarButton(Minimize);
    createTitleBarButton(Maximize);
    createTitleBarButton(Close);
    QObject::disconnect(this->titlebarClose, &TitleBarCloseButton::clicked, 0, 0);
    QObject::connect(this->titlebarClose, &TitleBarCloseButton::clicked, this, &MainFrame::close);

    QObject::connect(this->titlebarInfo, &TitleBarInfoButton::clicked, this, &MainFrame::showAbout);
    QObject::connect(this->titlebarPrefs, &TitleBarPrefsButton::clicked, this, &MainFrame::showPrefs);
#endif

#ifndef Q_OS_ANDROID
    this->setMinimumSize(410, 500);
#endif

    this->financeBtnGrid = new QGridLayout();
    this->financeBtnGrid->setContentsMargins(15,15,15,15);
    this->financeBtnGrid->setSpacing(20);

    this->btnEarning = new FinanceButton(this, *ThemeLoader::i()->btnIncomeIcon());
#ifndef Q_OS_ANDROID
    this->btnEarning->userData() = QObject::trUtf8("Add new Income");
    this->btnEarning->btnId() = 0;
#endif
    this->financeBtnGrid->addWidget(this->btnEarning, 0, 0);
    QObject::connect(this->btnEarning, &FinanceButton::clicked, this, &MainFrame::btnEarningClicked);

    this->btnExpense = new FinanceButton(this, *ThemeLoader::i()->btnExpenseIcon());
#ifndef Q_OS_ANDROID
    this->btnExpense->userData() = QObject::trUtf8("Add new Expense");
    this->btnExpense->btnId() = 1;
#endif
    this->financeBtnGrid->addWidget(this->btnExpense, 0, 1);
    QObject::connect(this->btnExpense, &FinanceButton::clicked, this, &MainFrame::btnExpenseClicked);

    this->btnEntries = new FinanceButton(this, *ThemeLoader::i()->btnEntriesIcon());
#ifndef Q_OS_ANDROID
    this->btnEntries->userData() = QObject::trUtf8("View all recorded entries");
    this->btnEntries->btnId() = 2;
#endif
    this->financeBtnGrid->addWidget(this->btnEntries, 1, 0);
    QObject::connect(this->btnEntries, &FinanceButton::clicked, this, &MainFrame::btnEntriesClicked);

    this->btnHistory = new FinanceButton(this, *ThemeLoader::i()->btnHistoryIcon());
#ifndef Q_OS_ANDROID
    this->btnHistory->userData() = QObject::trUtf8("View daily entries");
    this->btnHistory->btnId() = 3;
#endif
    this->financeBtnGrid->addWidget(this->btnHistory, 1, 1);
    QObject::connect(this->btnHistory, &FinanceButton::clicked, this, &MainFrame::btnHistoryClicked);

    this->m_layout->addItem(this->financeBtnGrid);

    this->font_calculation = new QFont();
    this->font_calculation->setPointSize(L_FONT_SIZE);
    this->font_calculation->setBold(true);

    this->font_amounts = new QFont("Monospace");
    this->font_amounts->setPointSize(L_FONT_SIZE);
    this->font_amounts->setBold(true);
    this->font_amounts->setItalic(true);

    this->calculation_grid = new QGridLayout();
    this->calculation_grid->setContentsMargins(10,10,10,10);
    this->calculation_grid->setSpacing(20);

    this->labelEarnings = new QLabel(this);
    this->labelEarnings->setText("  " + QObject::trUtf8("Earnings:"));
    this->labelEarnings->setFont(*this->font_calculation);
    this->labelEarnings->setStyleSheet(ThemeLoader::i()->earningColor());

    this->labelExpenses = new QLabel(this);
    this->labelExpenses->setText("  " + QObject::trUtf8("Expenses:"));
    this->labelExpenses->setFont(*this->font_calculation);
    this->labelExpenses->setStyleSheet(ThemeLoader::i()->expenseColor());

    this->totalEarnings = new QLabel(this);
    this->totalEarnings->setStyleSheet(ThemeLoader::i()->earningColor());
    this->totalEarnings->setFont(*this->font_amounts);
    this->totalEarnings->setAlignment(Qt::AlignRight);

    this->totalExpenses = new QLabel(this);
    this->totalExpenses->setStyleSheet(ThemeLoader::i()->expenseColor());
    this->totalExpenses->setFont(*this->font_amounts);
    this->totalExpenses->setAlignment(Qt::AlignRight);

    this->calculation_grid->addWidget(this->labelEarnings, 0, 0);
    this->calculation_grid->addWidget(this->labelExpenses, 1, 0);
    this->calculation_grid->addWidget(this->totalEarnings, 0, 1);
    this->calculation_grid->addWidget(this->totalExpenses, 1, 1);

    this->m_layout->addItem(this->calculation_grid);

    this->statusbar = new QHBoxLayout();
    this->statusbar->setContentsMargins(15, 10, 15, 5);
    this->statusbarSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    this->font_statusbar = new QFont();
    this->font_statusbar->setBold(true);
    this->btnStatus = new QLabel(this);
    this->unsavedEntries = new QLabel(this);
    this->unsavedEntries->setFont(*this->font_statusbar);

    this->statusbar->addWidget(this->btnStatus);
    this->statusbar->addItem(this->statusbarSpacer);
    this->statusbar->addWidget(this->unsavedEntries);

    this->m_layout->addItem(this->statusbar);

#ifndef Q_OS_ANDROID
    this->s_left = new QShortcut(QKeySequence(Qt::Key_Left), this);
    this->s_right = new QShortcut(QKeySequence(Qt::Key_Right), this);
    this->s_up = new QShortcut(QKeySequence(Qt::Key_Up), this);
    this->s_down = new QShortcut(QKeySequence(Qt::Key_Down), this);
    QObject::connect(this->s_left, &QShortcut::activated, this, &MainFrame::keyNavLeft);
    QObject::connect(this->s_right, &QShortcut::activated, this, &MainFrame::keyNavRight);
    QObject::connect(this->s_up, &QShortcut::activated, this, &MainFrame::keyNavUp);
    QObject::connect(this->s_down, &QShortcut::activated, this, &MainFrame::keyNavDown);

    this->s_quit = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q), this);
    this->s_altF4 = new QShortcut(QKeySequence(Qt::ALT + Qt::Key_F4), this);
    QObject::connect(this->s_quit, &QShortcut::activated, this, &MainFrame::close);
    QObject::connect(this->s_altF4, &QShortcut::activated, this, &MainFrame::close);
#endif

    /* unsaved entries dialog */
    this->d_unsavedEntries = new NoticeDialog();
    this->d_unsavedEntries->setDialogTitle(QObject::trUtf8("Quit %1").arg(AppSettings::i()->AppName));
    this->d_unsavedEntries->setDialogIcon(*ThemeLoader::i()->alertIcon());
    this->d_unsavedEntries->setMessage(QObject::trUtf8("Are you sure that you want to leave %1?\n\nYou have unsaved entries, which will be lost.")
                                           .arg(AppSettings::i()->AppName));
    this->d_unsavedEntries->setOkButtonText(QObject::trUtf8("Leave"));
    this->d_unsavedEntries->setOkButtonIcon(*ThemeLoader::i()->closeIcon());
    this->d_unsavedEntries->setCancelButtonText(QObject::trUtf8("Stay"));
    this->d_unsavedEntries->setCancelButtonIcon(*ThemeLoader::i()->appIcon());

#ifdef Q_OS_ANDROID
    this->btnStatus->setVisible(false);
    this->unsavedEntries->setVisible(false);
#endif

    this->updateOpenEntryDialogCount(EntryDialogCount::Init);
    this->updateEarnings();
    this->updateExpenses();
}

MainFrame::~MainFrame()
{
    delete this->btnEarning;
    delete this->btnExpense;
    delete this->btnEntries;
    delete this->btnHistory;

    delete this->financeBtnGrid;

    delete this->btnStatus;
    delete this->unsavedEntries;
    delete this->statusbarSpacer;
    delete this->statusbar;

    delete this->labelEarnings;
    delete this->labelExpenses;
    delete this->totalEarnings;
    delete this->totalExpenses;
    delete this->calculation_grid;

    delete this->font_statusbar;
    delete this->font_calculation;
    delete this->font_amounts;

    delete this->d_unsavedEntries;

#ifndef Q_OS_ANDROID
    delete this->s_left;
    delete this->s_right;
    delete this->s_up;
    delete this->s_down;

    delete this->s_quit;
    delete this->s_altF4;
#endif

    delete this;
}

void MainFrame::updateDescHovered(FinanceButton *btn)
{
#ifndef Q_OS_ANDROID
    this->btnStatus->setText(btn->userData());
#else
    Q_UNUSED(btn);
#endif
}

void MainFrame::updateDescUnhovered()
{
#ifndef Q_OS_ANDROID
    this->btnStatus->setText(static_cast<FinanceButton*>(this->focusWidget())->userData());
#endif
}

void MainFrame::updateEarnings()
{
    this->totalEarnings->setText(QString::number(DatabaseManager::i()->totalEarnings(QDate::currentDate()), 'f', 2) + "  ");
}

void MainFrame::updateExpenses()
{
    this->totalExpenses->setText(QString::number(DatabaseManager::i()->totalExpenses(QDate::currentDate()), 'f', 2) + "  ");
}

void MainFrame::updateOpenEntryDialogCount(EntryDialogCount c)
{
    if (c == EntryDialogCount::Init)
        this->m_openEntryDialogs = 0;
    else if (c == EntryDialogCount::Add)
        this->m_openEntryDialogs++;
    else this->m_openEntryDialogs--;

    if (this->m_openEntryDialogs == 0)
        this->unsavedEntries->setText(QObject::trUtf8("No unsaved entries"));
    else if (this->m_openEntryDialogs == 1)
        this->unsavedEntries->setText(QObject::trUtf8("%1 unsaved entry").arg(QString::number(this->m_openEntryDialogs)));
    else
        this->unsavedEntries->setText(QObject::trUtf8("%1 unsaved entries").arg(QString::number(this->m_openEntryDialogs)));
}

#ifndef Q_OS_ANDROID
void MainFrame::keyNavLeft()
{
    int btnId = static_cast<FinanceButton*>(this->focusWidget())->btnId();

         if (btnId == 1) this->btnEarning->setFocus();
    else if (btnId == 3) this->btnEntries->setFocus();
}

void MainFrame::keyNavRight()
{
    int btnId = static_cast<FinanceButton*>(this->focusWidget())->btnId();

         if (btnId == 0) this->btnExpense->setFocus();
    else if (btnId == 2) this->btnHistory->setFocus();
}

void MainFrame::keyNavUp()
{
    int btnId = static_cast<FinanceButton*>(this->focusWidget())->btnId();

         if (btnId == 2) this->btnEarning->setFocus();
    else if (btnId == 3) this->btnExpense->setFocus();
}

void MainFrame::keyNavDown()
{
    int btnId = static_cast<FinanceButton*>(this->focusWidget())->btnId();

         if (btnId == 0) this->btnEntries->setFocus();
    else if (btnId == 1) this->btnHistory->setFocus();
}
#else
void MainFrame::keyNavLeft() {}
void MainFrame::keyNavRight() {}
void MainFrame::keyNavUp() {}
void MainFrame::keyNavDown() {}
#endif

void MainFrame::btnEarningClicked()
{
    /* multitasking support, dialog deletes itself after closing */
    EntryCreator *ec_earning = new EntryCreator(DatabaseManager::Earning, this);
    ec_earning->show();
    this->updateOpenEntryDialogCount(EntryDialogCount::Add);
}

void MainFrame::btnExpenseClicked()
{
    /* multitasking support, dialog deletes itself after closing */
    EntryCreator *ec_expense = new EntryCreator(DatabaseManager::Expense, this);
    ec_expense->show();
    this->updateOpenEntryDialogCount(EntryDialogCount::Add);
}

void MainFrame::btnEntriesClicked()
{
    DatabaseViewer *dbViewer = new DatabaseViewer();
    dbViewer->setViewType(DatabaseViewer::AllTime);
    dbViewer->exec();
    delete dbViewer;
}

void MainFrame::btnHistoryClicked()
{
    DatabaseViewer *dbViewer = new DatabaseViewer();
    dbViewer->setViewType(DatabaseViewer::Daily);
    dbViewer->exec();
    delete dbViewer;
}

void MainFrame::close()
{
    if (this->m_openEntryDialogs != 0)
        if (!this->d_unsavedEntries->exec())
            return;
    (void) MaterialDialog::close();
}

void MainFrame::keyPressEvent(QKeyEvent *event)
{
    if (event->key() != Qt::Key_Escape)
        event->accept();
}

void MainFrame::showAbout()
{
    aboutDialog->show();
}

void MainFrame::showPrefs()
{
    prefsDialog->show();
}
