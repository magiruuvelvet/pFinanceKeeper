#include <dialogs/databaseviewer.hpp>

#ifdef Q_OS_ANDROID
    #define L_FONT_SIZE_DEFAULT  22
    #define L_COLUMN_DAY         55
    #define L_COLUMN_DESC       320
#else
    #define L_FONT_SIZE_DEFAULT  11
    #define L_COLUMN_DAY         70
    #define L_COLUMN_DESC       170
#endif

DatabaseViewer::DatabaseViewer(QWidget *parent)
    : MaterialDialog(parent)
{
    this->m_layout = this->createTitleBar(QObject::trUtf8("Database Viewer"), *ThemeLoader::i()->prefsIcon(), 2);
    this->m_layout->setSpacing(5);
    this->setWindowFlags(Qt::WindowCloseButtonHint | Qt::FramelessWindowHint | Qt::Dialog);
#ifndef Q_OS_ANDROID
    createTitleBarButton(Close);
#endif

#ifndef Q_OS_ANDROID
    this->setMinimumSize(700, 500);
#endif

    this->m_header = new QHBoxLayout();
    this->m_header->setContentsMargins(0,0,0,0);
    this->m_header->setSpacing(2);
    this->m_layout->addItem(this->m_header);

    this->font_default = new QFont();
    this->font_default->setPointSize(L_FONT_SIZE_DEFAULT);

    this->font_italic = new QFont();
    this->font_italic->setPointSize(L_FONT_SIZE_DEFAULT);
    this->font_italic->setItalic(true);

    this->font_bold = new QFont();
    this->font_bold->setPointSize(L_FONT_SIZE_DEFAULT);
    this->font_bold->setBold(true);

    this->font_boldMonospace = new QFont("Monospace");
    this->font_boldMonospace->setPointSize(L_FONT_SIZE_DEFAULT);
    this->font_boldMonospace->setBold(true);

    this->font_monospace = new QFont("Monospace");
    this->font_monospace->setPointSize(L_FONT_SIZE_DEFAULT);

    /* create view widget */
    this->ui_view = new QTableWidget(this);
    this->ui_view->setFrameShape(QTableWidget::NoFrame);
    this->ui_view->setFrameShadow(QTableWidget::Plain);
    this->ui_view->setAcceptDrops(false);
    this->ui_view->setColumnCount(4);
    this->ui_view->verticalHeader()->setVisible(false);
    this->ui_view->setEditTriggers(QTableWidget::NoEditTriggers);
    this->ui_view->setFont(*this->font_default);

#ifdef Q_OS_ANDROID
    QString field_day = QObject::trUtf8("D");
#else
    QString field_day = QObject::trUtf8("Day");
#endif

    this->ui_view->setHorizontalHeaderLabels({field_day,
                                              QObject::trUtf8("Category"),
                                              QObject::trUtf8("Description"),
                                              QObject::trUtf8("Amount")});

    this->ui_view->setColumnWidth(0, L_COLUMN_DAY);
    this->ui_view->setColumnWidth(1, L_COLUMN_DESC);
#ifndef Q_OS_ANDROID
    this->ui_view->setColumnWidth(4, 100);
#endif

    this->ui_view->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    this->ui_view->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    this->ui_view->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
#ifdef Q_OS_ANDROID
    this->ui_view->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
#else
    this->ui_view->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);
#endif

    this->m_layout->addWidget(this->ui_view);
}

DatabaseViewer::~DatabaseViewer()
{
    //delete this->m_layout;
    //delete this->m_header;

    //delete this->ui_monthSelector;
    //delete this->ui_categorySelector;

    //delete this->ui_search;
    delete this->ui_view;

    delete this->font_default;
    delete this->font_italic;
    delete this->font_bold;
    delete this->font_boldMonospace;
    delete this->font_monospace;
}

void DatabaseViewer::keyReleaseEvent(QKeyEvent *event)
{
#ifdef Q_OS_ANDROID
    if (event->key() == Qt::Key_Back)
        this->close();

    else event->accept();
#else
    MaterialDialog::keyReleaseEvent(event);
#endif
}

void DatabaseViewer::exec()
{
    this->setModal();
    this->show();

    this->eventLoop = new QEventLoop(this);
    this->eventLoop->exec();
    delete this->eventLoop;

    MaterialDialog::close();
}

void DatabaseViewer::setViewType(ViewType type)
{
    this->m_type = type;
    this->m_date = QDate::currentDate();

    if (type == Daily) {
        this->setDialogTitle(QObject::trUtf8("Todays Entries : %1").arg(this->m_date.toString("dddd, dd. MMMM")));
        this->buildCategorySelector();
        this->readDatabase();
    } else {
        this->buildMonthSelector();
        this->buildCategorySelector();
        this->setDialogTitle(QObject::trUtf8("All recorded entries"));
    }
}

void DatabaseViewer::readDatabase()
{
    this->ui_view->clearContents();

    QList<DatabaseManager::DatabaseEntry> pentries, entries;
    if (this->m_type == Daily) pentries = DatabaseManager::i()->dailyEntries(this->m_date);
    else pentries = DatabaseManager::i()->entries(this->m_date);

    QList<DatabaseManager::DatabaseCategory> categoriesEarnings = DatabaseManager::i()->categories(DatabaseManager::Earning, false);
    QList<DatabaseManager::DatabaseCategory> categoriesExpenses = DatabaseManager::i()->categories(DatabaseManager::Expense, false);

    // rebuild entries
    for (const DatabaseManager::DatabaseEntry &e : pentries) {

        // everything
        if (this->m_category.type == -1 && this->m_category.id == -1) {
            entries = pentries;
            break;
        }

        // all earnings
        else if (this->m_category.type == DatabaseManager::Earning && this->m_category.id == -1) {
            if (e.type == DatabaseManager::Earning)
                entries.push_back(e);
        }

        // all expenses
        else if (this->m_category.type == DatabaseManager::Expense && this->m_category.id == -1) {
            if (e.type == DatabaseManager::Expense)
                entries.push_back(e);
        }

        // specific category
        else {
            if (e.type == this->m_category.type && e.category == this->m_category.id)
                entries.push_back(e);
        }
    }

    this->ui_view->setRowCount(entries.size()+3);

    for (int i = 0; i < entries.size(); i++) {

        // .day()
        QTableWidgetItem* day = new QTableWidgetItem();

        QDate dayWrapper = this->m_date;
        dayWrapper.setDate(dayWrapper.year(), dayWrapper.month(), entries[i].day);

#ifdef Q_OS_ANDROID
        day->setData(Qt::UserRole, dayWrapper.toString("dd"));
#else
        day->setData(Qt::UserRole, dayWrapper.toString("ddd, d"));
#endif
        day->setText(dayWrapper.toString("dd"));

        this->ui_view->setItem(i, 0, day);

        // .type()
        QTableWidgetItem* entryType = new QTableWidgetItem();
        if (entries[i].type == DatabaseManager::Earning) {
            entryType->setForeground(QColor(52, 166, 0));
            entryType->setData(Qt::UserRole, QVariant(DatabaseManager::Earning));
        } else {
            entryType->setForeground(QColor(218, 0, 0));
            entryType->setData(Qt::UserRole, QVariant(DatabaseManager::Expense));
        }

        // .category()
        QTableWidgetItem* category = new QTableWidgetItem();
        if (entryType->data(Qt::UserRole).toInt() == DatabaseManager::Earning) {
            for (DatabaseManager::DatabaseCategory &c : categoriesEarnings) {
                if (c.id == entries[i].category)
                    category->setText(c.name);
                else if (0 == entries[i].category) {
                    category->setText(QObject::trUtf8("Retour"));
                    category->setFont(*this->font_italic);
                }
            }
        } else {
            for (DatabaseManager::DatabaseCategory &c : categoriesExpenses) {
                if (c.id == entries[i].category)
                    category->setText(c.name);
            }
        }

        this->ui_view->setItem(i, 1, category);

        // .desc()
        if (entries[i].isRetourEntry) {
            this->ui_view->setItem(i, 2, new QTableWidgetItem(entries[i].desc + " | " + entries[i].retourDesc));
        } else {
            this->ui_view->setItem(i, 2, new QTableWidgetItem(entries[i].desc));
        }

        // .amount()
        QTableWidgetItem* amount = new QTableWidgetItem();

        amount->setTextAlignment(Qt::AlignRight);
        amount->setFont(*this->font_monospace);
        amount->setText(QString::number(entries[i].amount, 'f', 2));
        amount->setForeground(entryType->foreground());

        this->ui_view->setItem(i, 3, amount);

        // cleanup
        delete entryType;
    }

    this->ui_view->sortItems(0);

    for (int i = 0; i < this->ui_view->rowCount()-3; i++)
        this->ui_view->item(i, 0)->setText(this->ui_view->item(i, 0)->data(Qt::UserRole).toString());

    QTableWidgetItem* totalEarnings = new QTableWidgetItem(QObject::trUtf8("Total Earnings"));
    totalEarnings->setFont(*this->font_bold);
    totalEarnings->setForeground(QColor(52, 166, 0));
    this->ui_view->setItem(this->ui_view->rowCount()-3, 1, totalEarnings);
    QTableWidgetItem* totalEarningsC = new QTableWidgetItem( this->totalCategoryCalculator(entries, DatabaseManager::Earning) ); //QString::number(DatabaseManager::i()->totalEarnings(this->m_date), 'f', 2));
    totalEarningsC->setFont(*this->font_boldMonospace);
    totalEarningsC->setForeground(totalEarnings->foreground());
    totalEarningsC->setTextAlignment(Qt::AlignRight);
    this->ui_view->setItem(this->ui_view->rowCount()-3, 3, totalEarningsC);

    this->ui_view->setItem(this->ui_view->rowCount()-3, 0, new QTableWidgetItem());
    this->ui_view->setItem(this->ui_view->rowCount()-3, 2, new QTableWidgetItem());

    QTableWidgetItem* totalExpenses = new QTableWidgetItem(QObject::trUtf8("Total Expenses"));
    totalExpenses->setFont(*this->font_bold);
    totalExpenses->setForeground(QColor(218, 0, 0));
    this->ui_view->setItem(this->ui_view->rowCount()-2, 1, totalExpenses);
    QTableWidgetItem* totalExpensesC = new QTableWidgetItem( this->totalCategoryCalculator(entries, DatabaseManager::Expense) ); //QString::number(DatabaseManager::i()->totalExpenses(this->m_date), 'f', 2));
    totalExpensesC->setFont(*this->font_boldMonospace);
    totalExpensesC->setForeground(totalExpenses->foreground());
    totalExpensesC->setTextAlignment(Qt::AlignRight);
    this->ui_view->setItem(this->ui_view->rowCount()-2, 3, totalExpensesC);

    this->ui_view->setItem(this->ui_view->rowCount()-2, 0, new QTableWidgetItem());
    this->ui_view->setItem(this->ui_view->rowCount()-2, 2, new QTableWidgetItem());

    QTableWidgetItem* diffT = new QTableWidgetItem(QObject::trUtf8("Difference"));
    diffT->setFont(*this->font_bold);
    diffT->setForeground(QColor(185, 180, 17));
    this->ui_view->setItem(this->ui_view->rowCount()-1, 1, diffT);
    QTableWidgetItem* diff = new QTableWidgetItem( this->totalCategoryDiff(entries) /*QString::number(
                                                        DatabaseManager::i()->totalEarnings(this->m_date)
                                                      - DatabaseManager::i()->totalExpenses(this->m_date)
                                                  ,'f', 2)*/);
    diff->setFont(*this->font_boldMonospace);
    diff->setForeground(diffT->foreground());
    diff->setTextAlignment(Qt::AlignRight);
    this->ui_view->setItem(this->ui_view->rowCount()-1, 3, diff);

    this->ui_view->setItem(this->ui_view->rowCount()-1, 0, new QTableWidgetItem());
    this->ui_view->setItem(this->ui_view->rowCount()-1, 2, new QTableWidgetItem());
}

void DatabaseViewer::buildMonthSelector()
{
    this->ui_monthSelector = new QComboBox(this);
    this->ui_monthSelector->setFrame(false);
    this->ui_monthSelector->setFont(*this->font_default);

    this->m_header->addWidget(this->ui_monthSelector);

    for (const QString &table : DatabaseManager::i()->tables()) {
        QDate date = QDate::fromString(table, "MM-yyyy");
        this->ui_monthSelector->addItem(date.toString("MMMM yyyy"), date);
    }

    void (QComboBox::*indexChangedSignal)(int) = &QComboBox::currentIndexChanged;
    QObject::connect(this->ui_monthSelector, indexChangedSignal, this, &DatabaseViewer::changeMonth);

    this->ui_monthSelector->setCurrentIndex(this->ui_monthSelector->count()-1);
    this->changeMonth(this->ui_monthSelector->currentIndex());
}

void DatabaseViewer::selectMonth(const QDate &date)
{
    this->m_date = date;
    this->readDatabase();
}

void DatabaseViewer::changeMonth(int index)
{
    this->selectMonth(this->ui_monthSelector->itemData(index, Qt::UserRole).toDate());
}

void DatabaseViewer::buildCategorySelector()
{
    this->ui_categorySelector = new QComboBox(this);
    this->ui_categorySelector->setFrame(false);
    this->ui_categorySelector->setFont(*this->font_default);

    this->m_header->addWidget(this->ui_categorySelector);

    this->ui_categorySelector->addItem(QObject::trUtf8("All Entries"), QStringList({QString::number(-1), QString::number(-1)}));
    this->ui_categorySelector->insertSeparator(this->ui_categorySelector->count());
    this->ui_categorySelector->addItem(QObject::trUtf8("────── Earnings ──────"), QStringList({QString::number(DatabaseManager::Earning), QString::number(-1)}));
    this->buildCategorySelector(DatabaseManager::Earning);
    this->ui_categorySelector->insertSeparator(this->ui_categorySelector->count());
    this->ui_categorySelector->addItem(QObject::trUtf8("────── Expenses ──────"), QStringList({QString::number(DatabaseManager::Expense), QString::number(-1)}));
    this->buildCategorySelector(DatabaseManager::Expense);

    QFont font = this->ui_categorySelector->view()->font();
    QFontMetrics fm(font);

    int max = 0;
    for (int i = 0; i < this->ui_categorySelector->count(); i++) {
        int cur = fm.width(this->ui_categorySelector->itemText(i));
        if (cur > max) max = cur;
    }

    this->ui_categorySelector->view()->setMinimumWidth(max + 55);

    void (QComboBox::*indexChangedSignal)(int) = &QComboBox::currentIndexChanged;
    QObject::connect(this->ui_categorySelector, indexChangedSignal, this, &DatabaseViewer::filterByCategory);

    this->ui_categorySelector->setCurrentIndex(0);
    this->filterByCategory(0);
}

void DatabaseViewer::buildCategorySelector(DatabaseManager::EntryType type)
{
    QList<DatabaseManager::DatabaseCategory> categories = DatabaseManager::i()->categories(type);

    for (DatabaseManager::DatabaseCategory &c : categories)
        this->ui_categorySelector->addItem(c.name, QStringList({QString::number(type), QString::number(c.id)}));
}

void DatabaseViewer::filterByCategory(int index)
{
    QStringList list = this->ui_categorySelector->itemData(index, Qt::UserRole).toStringList();
    DatabaseManager::DatabaseCategory c;

    c.type = static_cast<DatabaseManager::EntryType>(list.at(0).toInt());
    c.id   = list.at(1).toInt();
    c.name = this->ui_categorySelector->itemText(index);
    this->m_category = c;

    this->readDatabase();
}

QString DatabaseViewer::totalCategoryCalculator(const QList<DatabaseManager::DatabaseEntry> &entries, DatabaseManager::EntryType type)
{
    double total = 0.0;

    for (const DatabaseManager::DatabaseEntry &e : entries) {
        if (e.type == type)
            total += e.amount;
    }

    return QString::number(total, 'f', 2);
}

QString DatabaseViewer::totalCategoryDiff(const QList<DatabaseManager::DatabaseEntry> &entries)
{
    double totalEarning = 0.0,
           totalExpense = 0.0;

    for (const DatabaseManager::DatabaseEntry &e : entries) {
        if (e.type == DatabaseManager::Earning)
            totalEarning += e.amount;
        else totalExpense += e.amount;
    }

    return QString::number( totalEarning - totalExpense, 'f', 2 );
}
