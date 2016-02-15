#ifndef THEMELOADER_HPP
#define THEMELOADER_HPP

#include <QString>
#include <QImage>
#include <QIcon>

class ThemeLoader
{
public:
    static ThemeLoader *i();
    ~ThemeLoader();

    void init();

    QString styleSheet() const;
    QString earningColor() const;
    QString expenseColor() const;
    QString disabledColor() const;

    QImage *bg() const;

    QIcon *appIcon() const;
    QIcon *prefsIcon() const;
    QIcon *infoIcon() const;
    QIcon *closeIcon() const;
    QIcon *minimizeIcon() const;
    QIcon *maximizeIcon() const;
    QIcon *unmaximizeIcon() const;
    QIcon *printIcon() const;
    QIcon *earningIcon() const;
    QIcon *expenseIcon() const;
    QIcon *alertIcon() const;

    QIcon *btnIncomeIcon() const;
    QIcon *btnExpenseIcon() const;
    QIcon *btnEntriesIcon() const;
    QIcon *btnHistoryIcon() const;

    QIcon *btnAddIcon() const;
    QIcon *btnRemoveIcon() const;

    QIcon *menuBtn() const;

private:
    ThemeLoader();

    QString m_styleSheet,
            m_earningColor,
            m_expenseColor,
            m_disabledColor;

    QImage *m_bg;

    QIcon   *m_appIcon,
            *m_prefsIcon,
            *m_infoIcon,
            *m_closeIcon,
            *m_minimizeIcon,
            *m_maximizeIcon,
            *m_unmaximizeIcon,
            *m_printIcon,
            *m_earningIcon,
            *m_expenseIcon,
            *m_alertIcon;

    QIcon   *m_btnIncomeIcon,
            *m_btnExpenseIcon,
            *m_btnEntriesIcon,
            *m_btnHistoryIcon;

    QIcon   *m_btnAddIcon,
            *m_btnRemoveIcon;

    QIcon   *m_menuBtn;
};

#endif // THEMELOADER_HPP
