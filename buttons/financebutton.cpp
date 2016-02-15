#include <buttons/financebutton.hpp>
#include <dialogs/mainframe.hpp>

FinanceButton::FinanceButton(QWidget *parent, const QIcon &icon) :
    QPushButton(parent)
{
    this->setMinimumSize(120, 120);
#ifdef Q_OS_ANDROID
    this->setIconSize(QSize(420, 420));
#else
    this->setIconSize(QSize(100, 100));
#endif
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setIcon(icon);
#ifdef Q_OS_ANDROID
    this->setFocusPolicy(Qt::NoFocus);
#else
    this->setFocusPolicy(Qt::StrongFocus);
#endif
    this->setFlat(true);
    this->setAutoFillBackground(true);

    QObject::connect(this, &FinanceButton::hovered, static_cast<MainFrame*>(this->parent()), &MainFrame::updateDescHovered);
    QObject::connect(this, &FinanceButton::unhovered, static_cast<MainFrame*>(this->parent()), &MainFrame::updateDescUnhovered);
}

FinanceButton::~FinanceButton()
{
    this->m_userData.clear();
}

QString &FinanceButton::userData()
{
    return this->m_userData;
}

int &FinanceButton::btnId()
{
    return this->m_btnId;
}

int FinanceButton::heightForWidth(int width) const
{
    return width;
}

void FinanceButton::enterEvent(QEvent *event)
{
    this->QPushButton::enterEvent(event);
    emit hovered(this);
}

void FinanceButton::leaveEvent(QEvent *event)
{
    this->QPushButton::leaveEvent(event);
    emit unhovered();
}

void FinanceButton::focusInEvent(QFocusEvent *event)
{
    this->QPushButton::focusInEvent(event);
    emit hovered(this);
}

void FinanceButton::focusOutEvent(QFocusEvent *event)
{
    this->QPushButton::focusOutEvent(event);
    emit unhovered();
}

void FinanceButton::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Space)
        emit clicked();

    else if (event->key() == Qt::Key_Escape)
        static_cast<MaterialDialog*>(this->parent())->close();
}
