#include <dialogs/prefsdialog.hpp>

#ifdef Q_OS_ANDROID
    #define L_FONT_SIZE_CAT 30
    #define L_FONT_SIZE_DEFAULT 22
    #define L_SIZE_BUTTON 100, 100
#else
    #define L_FONT_SIZE_CAT 14
    #define L_FONT_SIZE_DEFAULT 11
    #define L_SIZE_BUTTON 20, 20
#endif

PrefsDialog *prefsDialog = nullptr;

PrefsDialog::PrefsDialog(QWidget *parent)
    : MaterialDialog(parent)
{
    this->m_layout = this->createTitleBar(QObject::trUtf8("Preferences"), *ThemeLoader::i()->prefsIcon(), 2);
    this->setWindowFlags(Qt::WindowCloseButtonHint | Qt::FramelessWindowHint | Qt::Dialog);
#ifndef Q_OS_ANDROID
    createTitleBarButton(Close);
#endif

    this->ui_categoryEditor_layout = new QGridLayout();
    this->ui_categoryEditor_layout->setContentsMargins(2,2,2,2);

    /* create fonts */
    this->font_category = new QFont();
    font_category->setPointSize(L_FONT_SIZE_CAT);

    this->font_default = new QFont();
    this->font_default->setPointSize(L_FONT_SIZE_DEFAULT);

    this->font_defaultBold = new QFont();
    this->font_defaultBold->setPointSize(L_FONT_SIZE_DEFAULT);
    this->font_defaultBold->setBold(true);

    /* create the category editor field */
    this->ui_categoryEditor_field_title = new QLabel(this);
    this->ui_categoryEditor_field_title->setText(QObject::trUtf8("Categories"));
    this->ui_categoryEditor_field_title->setFont(*this->font_category);
    this->m_layout->addWidget(this->ui_categoryEditor_field_title);

    this->ui_categoryEditor_field = new QFrame(this);
    this->ui_categoryEditor_field->setFrameShadow(QFrame::Plain);
    this->ui_categoryEditor_field->setFrameShape(QFrame::Box);
    this->ui_categoryEditor_field->setLineWidth(1);
    this->m_layout->addWidget(this->ui_categoryEditor_field);

    this->ui_categoryEditor_layout = new QGridLayout(this->ui_categoryEditor_field);
    this->ui_categoryEditor_layout->setContentsMargins(2,2,2,2);

    this->ui_categoryEditor_earnings_label = new QLabel(this);
    this->ui_categoryEditor_earnings_label->setFont(*this->font_defaultBold);
    this->ui_categoryEditor_earnings_label->setStyleSheet(ThemeLoader::i()->earningColor());
    this->ui_categoryEditor_earnings_label->setText(QObject::trUtf8("Earnings"));

    this->ui_categoryEditor_expenses_label = new QLabel(this);
    this->ui_categoryEditor_expenses_label->setFont(*this->font_defaultBold);
    this->ui_categoryEditor_expenses_label->setStyleSheet(ThemeLoader::i()->expenseColor());
    this->ui_categoryEditor_expenses_label->setText(QObject::trUtf8("Expenses"));

    this->ui_categoryEditor_earnings = new QListWidget(this);
    this->ui_categoryEditor_earnings->setAcceptDrops(false);
    this->ui_categoryEditor_earnings->setDragDropMode(QListWidget::InternalMove);
    this->ui_categoryEditor_earnings->setDragEnabled(true);
    this->ui_categoryEditor_earnings->setDropIndicatorShown(true);
    this->ui_categoryEditor_earnings->setEditTriggers(QListWidget::EditKeyPressed | QListWidget::DoubleClicked);
    this->ui_categoryEditor_earnings->setSelectionMode(QListWidget::SingleSelection);
    this->ui_categoryEditor_earnings->setObjectName("ui_categoryEditor_earnings");
    this->ui_categoryEditor_earnings->installEventFilter(this);
    this->ui_categoryEditor_earnings->setFont(*this->font_default);
    QObject::connect(this->ui_categoryEditor_earnings, &QListWidget::itemChanged, this, &PrefsDialog::updateEarningCategories);

    this->ui_categoryEditor_expenses = new QListWidget(this);
    this->ui_categoryEditor_expenses->setAcceptDrops(false);
    this->ui_categoryEditor_expenses->setDragDropMode(QListWidget::InternalMove);
    this->ui_categoryEditor_expenses->setDragEnabled(true);
    this->ui_categoryEditor_expenses->setDropIndicatorShown(true);
    this->ui_categoryEditor_expenses->setEditTriggers(QListWidget::EditKeyPressed | QListWidget::DoubleClicked);
    this->ui_categoryEditor_expenses->setSelectionMode(QListWidget::SingleSelection);
    this->ui_categoryEditor_expenses->setObjectName("ui_categoryEditor_expenses");
    this->ui_categoryEditor_expenses->installEventFilter(this);
    this->ui_categoryEditor_expenses->setFont(*this->font_default);
    QObject::connect(this->ui_categoryEditor_expenses, &QListWidget::itemChanged, this, &PrefsDialog::updateExpenseCategories);

    this->ui_categoryEditor_earning_addCatBtn = new MaterialButton(this);
    this->ui_categoryEditor_createAddButton(this->ui_categoryEditor_earning_addCatBtn, QObject::trUtf8("Add Income Category"));
    QObject::connect(this->ui_categoryEditor_earning_addCatBtn, &MaterialButton::clicked, this, &PrefsDialog::addEarningCategory);

    this->ui_categoryEditor_expense_addCatBtn = new MaterialButton(this);
    this->ui_categoryEditor_createAddButton(this->ui_categoryEditor_expense_addCatBtn, QObject::trUtf8("Add Expense Category"));
    QObject::connect(this->ui_categoryEditor_expense_addCatBtn, &MaterialButton::clicked, this, &PrefsDialog::addExpenseCategory);

    this->ui_categoryEditor_earning_removeCatBtn = new MaterialButton(this);
    this->ui_categoryEditor_createRemoveButton(this->ui_categoryEditor_earning_removeCatBtn, QObject::trUtf8("Remove Income Category"));
    QObject::connect(this->ui_categoryEditor_earning_removeCatBtn, &MaterialButton::clicked, this, &PrefsDialog::removeEarningCategory);

    this->ui_categoryEditor_expense_removeCatBtn = new MaterialButton(this);
    this->ui_categoryEditor_createRemoveButton(this->ui_categoryEditor_expense_removeCatBtn, QObject::trUtf8("Remove Expense Category"));
    QObject::connect(this->ui_categoryEditor_expense_removeCatBtn, &MaterialButton::clicked, this, &PrefsDialog::removeExpenseCategory);

    this->ui_categoryEditor_layout->addWidget(this->ui_categoryEditor_earnings_label, 0, 0, 1, 3);
    this->ui_categoryEditor_layout->addWidget(this->ui_categoryEditor_expenses_label, 0, 3, 1, 3);
    this->ui_categoryEditor_layout->addWidget(this->ui_categoryEditor_earnings, 1, 0, 1, 3);
    this->ui_categoryEditor_layout->addWidget(this->ui_categoryEditor_expenses, 1, 3, 1, 3);

    this->ui_categoryEditor_layout->addWidget(this->ui_categoryEditor_earning_addCatBtn, 2, 1, 1, 1);
    this->ui_categoryEditor_layout->addWidget(this->ui_categoryEditor_earning_removeCatBtn, 2, 2, 1, 1);
    this->ui_categoryEditor_layout->addWidget(this->ui_categoryEditor_expense_addCatBtn, 2, 4, 1, 1);
    this->ui_categoryEditor_layout->addWidget(this->ui_categoryEditor_expense_removeCatBtn, 2, 5, 1, 1);

    this->buildCategoryLists();
}

PrefsDialog::~PrefsDialog()
{
    delete this->m_layout;

    delete this->font_category;
    delete this->font_default;
    delete this->font_defaultBold;

    delete this->ui_categoryEditor_field;
    delete this->ui_categoryEditor_field_title;
    delete this->ui_categoryEditor_earnings;
    delete this->ui_categoryEditor_expenses;
    delete this->ui_categoryEditor_earnings_label;
    delete this->ui_categoryEditor_expenses_label;
    delete this->ui_categoryEditor_layout;

    delete this->ui_categoryEditor_earning_addCatBtn;
    delete this->ui_categoryEditor_expense_addCatBtn;

    delete this->ui_categoryEditor_earning_removeCatBtn;
    delete this->ui_categoryEditor_expense_removeCatBtn;
}

void PrefsDialog::keyPressEvent(QKeyEvent *event)
{
    if (event->key() != Qt::Key_Escape)
        event->accept();
}

void PrefsDialog::keyReleaseEvent(QKeyEvent *event)
{
#ifdef Q_OS_ANDROID
    if (event->key() == Qt::Key_Back)
        this->close();

    else event->accept();
#else
    MaterialDialog::keyReleaseEvent(event);
#endif
}

bool PrefsDialog::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::ChildRemoved) {
        if (obj->objectName() == "ui_categoryEditor_earnings") this->updateEarningCategories();
        else if (obj->objectName() == "ui_categoryEditor_expenses") this->updateExpenseCategories();
    }

    return false;
}

void PrefsDialog::updateEarningCategories()
{
    this->updateCategoriesAbstract(DatabaseManager::Earning);
}

void PrefsDialog::updateExpenseCategories()
{
    this->updateCategoriesAbstract(DatabaseManager::Expense);
}

void PrefsDialog::updateCategoriesAbstract(DatabaseManager::EntryType type)
{
    QListWidget *widgetPointer = nullptr;
    if (type == DatabaseManager::Earning)
        widgetPointer = this->ui_categoryEditor_earnings;
    else widgetPointer = this->ui_categoryEditor_expenses;

    for (int i = 0; i < widgetPointer->count(); i++) {
        DatabaseManager::i()->editCategory(widgetPointer->item(i)->data(Qt::UserRole).toInt(),
                                           type,
                                           widgetPointer->item(i)->text());
        DatabaseManager::i()->editCategory(widgetPointer->item(i)->data(Qt::UserRole).toInt(),
                                           type,
                                           i);
    }
}

void PrefsDialog::addEarningCategory()
{
    this->addCategoryAbstract(DatabaseManager::Earning);
}

void PrefsDialog::addExpenseCategory()
{
    this->addCategoryAbstract(DatabaseManager::Expense);
}

void PrefsDialog::addCategoryAbstract(DatabaseManager::EntryType type)
{
    DatabaseManager::i()->addCategory(QObject::trUtf8("New Category"), type);
    this->buildCategoryList(type);
}

void PrefsDialog::removeEarningCategory()
{
    this->removeCategoryAbstract(DatabaseManager::Earning);
}

void PrefsDialog::removeExpenseCategory()
{
    this->removeCategoryAbstract(DatabaseManager::Expense);
}

void PrefsDialog::removeCategoryAbstract(DatabaseManager::EntryType type)
{
    QListWidget *widgetPointer = nullptr;
    if (type == DatabaseManager::Earning)
        widgetPointer = this->ui_categoryEditor_earnings;
    else widgetPointer = this->ui_categoryEditor_expenses;

    DatabaseManager::i()->removeCategory(widgetPointer->currentItem()->data(Qt::UserRole).toInt(), type);
    delete widgetPointer->item(widgetPointer->currentRow());
}

void PrefsDialog::buildCategoryLists()
{
    this->buildCategoryList(DatabaseManager::Earning);
    this->buildCategoryList(DatabaseManager::Expense);
}

void PrefsDialog::buildCategoryList(DatabaseManager::EntryType type)
{
    QListWidget *widgetPointer = nullptr;
    if (type == DatabaseManager::Earning)
        widgetPointer = this->ui_categoryEditor_earnings;
    else widgetPointer = this->ui_categoryEditor_expenses;

    widgetPointer->clear();

    QList<DatabaseManager::DatabaseCategory> entries = DatabaseManager::i()->categories(type);

    for (DatabaseManager::DatabaseCategory &c : entries) {
        QListWidgetItem* item = new QListWidgetItem(c.name);
        item->setData(Qt::UserRole, QVariant(c.id));
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsEnabled);
        widgetPointer->addItem(item);
    }

    this->updateCategoriesAbstract(type); // reorder the "order" index in the database, duplicates messes with the sorting function
}

void PrefsDialog::ui_categoryEditor_createAddButton(MaterialButton *btn, const QString &tooltip)
{
    this->ui_categoryEditor_createAbstractButton(btn, tooltip);
    btn->setIcon(*ThemeLoader::i()->btnAddIcon());

}

void PrefsDialog::ui_categoryEditor_createRemoveButton(MaterialButton *btn, const QString &tooltip)
{
    this->ui_categoryEditor_createAbstractButton(btn, tooltip);
    btn->setIcon(*ThemeLoader::i()->btnRemoveIcon());
}

void PrefsDialog::ui_categoryEditor_createAbstractButton(MaterialButton *btn, const QString &tooltip)
{
    btn->setFixedSize(L_SIZE_BUTTON);
    btn->setIconSize(QSize(L_SIZE_BUTTON));
    btn->setFlat(true);
    btn->setAutoFillBackground(true);
#ifdef Q_OS_ANDROID
    btn->setFocusPolicy(Qt::NoFocus);
#else
    btn->setFocusPolicy(Qt::TabFocus);
#endif
    btn->setToolTip(tooltip);
}
