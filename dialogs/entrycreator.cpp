#include <dialogs/entrycreator.hpp>
#include <dialogs/mainframe.hpp>
#include <core/amountvalidator.hpp>

#ifdef Q_OS_ANDROID
    #define L_FONT_SIZE 25
    #define L_BTN_SIZE 300, 90
#else
    #define L_FONT_SIZE 12
    #define L_BTN_SIZE 100, 40
#endif

EntryCreator::EntryCreator(DatabaseManager::EntryType type, QWidget *parent) :
    MaterialDialog(parent)
{
    this->m_layout = this->createTitleBar(QString(), QIcon(), 2);
    this->m_layout->setContentsMargins(0,0,0,0);
    this->setWindowFlags(Qt::WindowCloseButtonHint | Qt::FramelessWindowHint | Qt::Dialog);
#ifndef Q_OS_ANDROID
    createTitleBarButton(Close);

    /* reconnect the titlebar close button */
    QObject::disconnect(this->titlebarClose, &TitleBarCloseButton::clicked, 0, 0);
    QObject::connect(this->titlebarClose, &TitleBarCloseButton::clicked, this, &EntryCreator::cancel);
#endif

    this->m_type = type;

    switch (type) {
        case DatabaseManager::Earning:
            this->setDialogTitle(QObject::trUtf8("New Earning"));
            this->setDialogIcon(*ThemeLoader::i()->earningIcon());
#ifndef Q_OS_ANDROID
            this->setMinimumSize(265, 500);
#endif
            break;

        case DatabaseManager::Expense:
            this->setDialogTitle(QObject::trUtf8("New Expense"));
            this->setDialogIcon(*ThemeLoader::i()->expenseIcon());
#ifndef Q_OS_ANDROID
            this->setMinimumSize(265, 415);
#endif
            break;
    }

    /* create layout */
    this->m_font = new QFont();
    this->m_font->setPointSize(L_FONT_SIZE);

    this->m_font_amount = new QFont("Monospace");
    this->m_font_amount->setPointSize(L_FONT_SIZE);

    this->m_grid = new QGridLayout();
    this->m_grid->setContentsMargins(10, 10, 10, 10);
    this->m_layout->addItem(this->m_grid);

    this->spacer_bottom = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    this->m_layout->addItem(this->spacer_bottom);

    this->line_bottom = new QFrame(this);
    this->line_bottom->setFrameShadow(QFrame::Plain);
    this->line_bottom->setFrameShape(QFrame::HLine);
    this->line_bottom->setLineWidth(1);

    this->layout_bottom = new QHBoxLayout();
    this->layout_bottom->setContentsMargins(10, 5, 10, 5);
    this->layout_bottom->setSpacing(0);

    /* create widgets */
    this->addSpacer(0);

    this->label_category = this->addLabel(this->label_category, QObject::trUtf8("Category"), 1);

    this->m_category = new QComboBox(this);
    this->m_category->setFont(*this->m_font);
    this->m_category->setFrame(false);
#ifdef Q_OS_ANDROID
    this->m_category->setFocusPolicy(Qt::NoFocus);
#endif
    this->m_grid->addWidget(this->m_category, 2, 0);

    this->addSpacer(3);

    (void) this->addLabel(this->label_desc, QObject::trUtf8("Description"), 4);

    this->m_desc = new QLineEdit(this);
    this->m_desc->setFont(*this->m_font);
    this->m_desc->setFrame(false);
    this->m_grid->addWidget(this->m_desc, 5, 0);

    this->addSpacer(6);

    (void) this->addLabel(this->label_date, QObject::trUtf8("Date"), 7);

    this->m_date = new QDateEdit(this);
    this->m_date->setFont(*this->m_font);
    this->m_date->setCalendarPopup(true);
    this->m_date->setDate(QDate::currentDate());
    this->m_date->setDisplayFormat("dddd dd. MMMM yyyy");
    this->m_date->setCurrentSection(QDateEdit::DaySection);
    this->m_date->setFrame(false);
#ifdef Q_OS_ANDROID
    this->m_date->setMinimumHeight(130);
    this->m_date->setFocusPolicy(Qt::NoFocus);
    this->m_date->calendarWidget()->setMinimumWidth(this->minimumWidth());
    this->m_date->calendarWidget()->setMinimumHeight(this->minimumHeight()/3);
    this->m_date->calendarWidget()->setFont(*this->m_font);
#endif
    this->m_grid->addWidget(this->m_date, 8, 0);

    this->addSpacer(9);

    (void) this->addLabel(this->label_amount, QObject::trUtf8("Amount"), 10);

    this->m_amount = new QLineEdit(this);
    this->m_amount->setFont(*this->m_font_amount);
    this->m_amount->setFrame(false);
    this->m_amount->setValidator(amountValidator);
    this->m_grid->addWidget(this->m_amount, 11, 0);

    /* create widget just for the earnings dialog */
    if (type == DatabaseManager::Earning) {
        this->line_middle = new QFrame(this);
        this->line_middle->setFrameShadow(QFrame::Plain);
        this->line_middle->setFrameShape(QFrame::HLine);
        this->line_middle->setLineWidth(1);
        this->m_layout->addWidget(this->line_middle);

        this->m_grid2 = new QGridLayout();
        this->m_grid2->setContentsMargins(this->m_grid->contentsMargins());

        this->cb_retourfrom = new QCheckBox(this);
        this->cb_retourfrom->setText(QObject::trUtf8("Entry is retour from..."));
        this->cb_retourfrom->setFont(*this->m_font);
        this->cb_retourfrom->setChecked(false);
        QObject::connect(this->cb_retourfrom, &QCheckBox::toggled, this, &EntryCreator::updateRetourFromState);
        this->m_grid2->addWidget(this->cb_retourfrom, 0, 0);

        this->m_retourfrom = new QComboBox(this);
        this->m_retourfrom->setFont(*this->m_font);
        this->m_retourfrom->setFrame(false);
#ifdef Q_OS_ANDROID
        this->m_retourfrom->setFocusPolicy(Qt::NoFocus);
#endif
        this->m_grid2->addWidget(this->m_retourfrom, 1, 0);
        this->m_grid2->addWidget(new QLabel(this), 2, 0);

        this->m_layout->addItem(this->m_grid2);

        this->updateRetourFromState();
    }

    /* create bottom ─ buttons */
    this->btnComplete = new MaterialButton(this);
    this->btnComplete->setText(QObject::trUtf8("Save"));
    this->btnComplete->setFont(*this->m_font);
    this->btnComplete->setMinimumSize(L_BTN_SIZE);
    QObject::connect(this->btnComplete, &MaterialButton::clicked, this, &EntryCreator::saveEntry);

#ifdef Q_OS_ANDROID
    this->btnCancel = new MaterialButton(this);
    this->btnCancel->setText(QObject::trUtf8("Cancel"));
    this->btnCancel->setFont(*this->m_font);
    this->btnCancel->setMinimumSize(L_BTN_SIZE);
    QObject::connect(this->btnCancel, &MaterialButton::clicked, this, &EntryCreator::cancel);
#endif

    this->layout_bottom_spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    this->layout_bottom->addItem(this->layout_bottom_spacer);
#ifdef Q_OS_ANDROID
    this->layout_bottom->addWidget(this->btnCancel);
    this->layout_bottom->addSpacing(10);
#endif
    this->layout_bottom->addWidget(this->btnComplete);

    this->m_layout->addWidget(this->line_bottom);
    this->m_layout->addItem(this->layout_bottom);

    /* create notice dialogs */
    this->d_cancel = new NoticeDialog();
    this->d_cancel->setDialogTitle(QObject::trUtf8("Attention"));
    this->d_cancel->setDialogIcon(*ThemeLoader::i()->alertIcon());
    this->d_cancel->setMessage(QObject::trUtf8("Are you sure?\nThe entered data will be lost."));
    this->d_cancel->setOkButtonText(QObject::trUtf8("Yes"));
    this->d_cancel->setCancelButtonText(QObject::trUtf8("No"));
    this->d_cancel->keepOnTop();

    this->d_success = new NoticeDialog();
    this->d_success->setDialogTitle(QObject::trUtf8("Success"));
    this->d_success->setDialogIcon(*ThemeLoader::i()->appIcon());
    this->d_success->setMessage(QObject::trUtf8("The entry added successfully to the database."));
    this->d_success->setOkButtonText(QObject::trUtf8("OK"));
    this->d_success->hideCancelButton();
    this->d_success->keepOnTop();

    this->d_incomplete = new NoticeDialog();
    this->d_incomplete->setDialogTitle(QObject::trUtf8("Attention"));
    this->d_incomplete->setDialogIcon(*ThemeLoader::i()->alertIcon());
    this->d_incomplete->setMessage(QObject::trUtf8("Please fill out all the fields.\nIt is not possible to add an incomplete entry to the database."));
    this->d_incomplete->setOkButtonText(QObject::trUtf8("OK"));
    this->d_incomplete->hideCancelButton();
    this->d_incomplete->keepOnTop();

    /* read database */
    this->buildCategoryList();
    if (type == DatabaseManager::Earning) this->buildRetourList();
}

EntryCreator::~EntryCreator()
{
    delete this->m_category;
    delete this->m_retourfrom;
    delete this->m_desc;
    delete this->m_date;
    delete this->m_amount;

    delete this->btnComplete;

    delete this->label_category,
    delete this->label_desc,
    delete this->label_date,
    delete this->label_amount,

    delete this->cb_retourfrom;

    delete this->m_grid;
    delete this->m_grid2;
    delete this->m_font;
    delete this->m_font_amount;
    delete this->spacer_bottom;
    delete this->layout_bottom,
    delete this->line_bottom;

    delete this->d_cancel;
    delete this->d_success;
}

void EntryCreator::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
        this->cancel();
    else event->accept();
}

void EntryCreator::keyReleaseEvent(QKeyEvent *event)
{
#ifdef Q_OS_ANDROID
    if (event->key() == Qt::Key_Back)
        this->cancel();

    else event->accept();
#else
    MaterialDialog::keyReleaseEvent(event);
#endif
}

QLabel *EntryCreator::addLabel(QLabel *label, const QString &text, int row)
{
    label = new QLabel(this);
    label->setText(text);
    label->setFont(*this->m_font);
    this->m_grid->addWidget(label, row, 0);
    return label;
}

void EntryCreator::addSpacer(int row)
{
    this->m_grid->addWidget(new QLabel(this), row, 0);
}

void EntryCreator::saveEntry()
{
    /* check if all fields are valid */
    if (this->m_type == DatabaseManager::Earning) {
        if (this->cb_retourfrom->isChecked()) {
            if (this->m_desc->text().isEmpty()   ||
                this->m_amount->text().isEmpty() ||
                this->m_retourfrom->currentText().isEmpty())
            {
                this->disable();
                (void) this->d_incomplete->exec();
                this->enable();
                return;
            }
        } else {
            if (this->m_category->currentText().isEmpty() ||
                this->m_desc->text().isEmpty()            ||
                this->m_amount->text().isEmpty())
            {
                this->disable();
                (void) this->d_incomplete->exec();
                this->enable();
                return;
            }
        }
    } else {
        if (this->m_category->currentText().isEmpty() ||
            this->m_desc->text().isEmpty()            ||
            this->m_amount->text().isEmpty())
        {
            this->disable();
            (void) this->d_incomplete->exec();
            this->enable();
            return;
        }
    }

    /* add entry to database */
    static const QLocale amountConv(QLocale::German);

    if (this->m_type == DatabaseManager::Earning) {
        if (this->cb_retourfrom->isChecked())
            DatabaseManager::i()->addRetourEntry(this->m_date->date(),
                                                 this->m_desc->text(),
                                                 this->m_retourfrom->currentText(),
                                                 amountConv.toDouble(this->m_amount->text()));
        else
            DatabaseManager::i()->addEntry(this->m_date->date(),
                                           this->m_type,
                                           this->m_desc->text(),
                                           this->m_category->itemData(this->m_category->currentIndex()).toInt(),
                                           amountConv.toDouble(this->m_amount->text()));
    }

    else
        DatabaseManager::i()->addEntry(this->m_date->date(),
                                       this->m_type,
                                       this->m_desc->text(),
                                       this->m_category->itemData(this->m_category->currentIndex()).toInt(),
                                       amountConv.toDouble(this->m_amount->text()));

    mainframe->updateEarnings();
    mainframe->updateExpenses();

    this->disable();
    (void) this->d_success->exec();
    this->enable();

    this->close();
}

void EntryCreator::cancel()
{
    this->disable();

    if (this->d_cancel->exec())
        this->close();

    else this->enable();
}

void EntryCreator::updateRetourFromState()
{
    if (this->cb_retourfrom->isChecked()) {
        this->label_category->setVisible(false);
        this->m_category->setVisible(false);
        this->m_retourfrom->setVisible(true);
    } else {
        this->label_category->setVisible(true);
        this->m_category->setVisible(true);
        this->m_retourfrom->setVisible(false);
    }
}

void EntryCreator::disable()
{
    this->setEnabled(false);
    this->setWindowOpacity(0.8);
}

void EntryCreator::enable()
{
    this->setEnabled(true);
    this->setWindowOpacity(1.0);
}

void EntryCreator::close()
{
    mainframe->updateOpenEntryDialogCount(MainFrame::EntryDialogCount::Remove);
    (void) MaterialDialog::close();
}

void EntryCreator::buildCategoryList()
{
    QList<DatabaseManager::DatabaseCategory> categories = DatabaseManager::i()->categories(this->m_type);
    QStringList cItems;

    for (DatabaseManager::DatabaseCategory &c : categories) {
        cItems.push_back(c.name);
        this->m_category->addItem(c.name, QVariant(c.id));
    }

    QFont font = this->m_category->view()->font();
    QFontMetrics fm(font);

    int max = 0;
    for (const QString &s : cItems) {
        int cur = fm.width(s);
        if (cur > max) max = cur;
    }

    this->m_category->view()->setMinimumWidth(max + 55);

    cItems.clear();
}

void EntryCreator::buildRetourList()
{
    QList<DatabaseManager::DatabaseEntry> entries = DatabaseManager::i()->entries(true);
    QStringList cItems;

    for (DatabaseManager::DatabaseEntry &e : entries) {
        if (e.type != DatabaseManager::Earning)
            cItems.push_back(QString::number(e.day) + "-" + e.date.toString("MM-yyyy") + ": " +
                                             e.desc + " ─── " + QString::number(e.amount, 'f', 2));
    }

    QFont font = this->m_retourfrom->view()->font();
    QFontMetrics fm(font);

    int max = 0;
    for (const QString &s : cItems) {
        int cur = fm.width(s);
        if (cur > max) max = cur;
    }

    this->m_retourfrom->addItems(cItems);
    this->m_retourfrom->view()->setMinimumWidth(max + 55);

    cItems.clear();
}
