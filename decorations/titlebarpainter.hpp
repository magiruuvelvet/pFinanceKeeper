#ifndef TITLEBARPAINTER_HPP
#define TITLEBARPAINTER_HPP

#include <QWidget>
#include <QString>
#include <QIcon>
#include <QFont>

#include <QLayout>
#include <QSpacerItem>
#include <QFrame>
#include <QLabel>

#ifdef Q_OS_ANDROID
    #include <buttons/menubutton.hpp>
#endif

#include <core/themeloader.hpp>
#include <buttons/titlebarbutton.hpp>
#include <buttons/materialbutton.hpp>

class TitleBarPainter
{
public:
    TitleBarPainter(QWidget *widget);
    ~TitleBarPainter();

    /* create the titlebar for the widget and return a pointer to the layout */
    QVBoxLayout *paint(const QString &title, const QIcon &icon, int linewidth);

    /* Android only: Menu Button */
#ifdef Q_OS_ANDROID
    void createMenuButton();
#endif

    /* add a titlebar button to the widget */
    void addButton(TitleBarButton *btn);

    /* add a little space between the next button */
    void addButtonSpacer(int size);

    /* update widget background on resize */
    void updateBackground();

    /* get the width of the titlebar bottom line */
    int linewidth() const;

    /* add bottom parent spacer */
    void addBottomSpacer();

    /* change window title/icon */
    void setWindowTitle(const QString &title);
    void setWindowIcon(const QIcon &icon);

private:
    QWidget *m_widget = nullptr;
    QVBoxLayout *m_layout = nullptr;

    QVBoxLayout *m_parent_layout = nullptr;

    QLabel *ui_icon = nullptr;
    QLabel *ui_title = nullptr;
    QFont *ui_title_font = nullptr;

    QPalette *ui_bg = nullptr;

    QVBoxLayout *layout_master = nullptr;
    QHBoxLayout *layout_container = nullptr,
                *layout_btnBox = nullptr,
                *layout_widgetContainer = nullptr;
    QVBoxLayout *layout_widgetBox = nullptr,
                *layout_btnContainer = nullptr;
    QSpacerItem *layout_leftSpacer = nullptr,
                *layout_rightSpacer = nullptr,
                *layout_middleSpacer = nullptr,
                *layout_btnBoxSpacer = nullptr,
                *layout_bottomParent = nullptr;
    QFrame      *layout_bottomLine = nullptr,
                *layout_bottomFixSpacer = nullptr;

#ifdef Q_OS_ANDROID
    MenuButton *menuBtn = nullptr;
    QSpacerItem *layout_menuBtn_center = nullptr;
#endif
};

#endif // TITLEBARPAINTER_HPP
