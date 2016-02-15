#ifndef MATERIALDIALOG_HPP
#define MATERIALDIALOG_HPP

#include <QWidget>
#include <QEvent>
#include <QMouseEvent>
#include <QResizeEvent>

#include <decorations/titlebarpainter.hpp>
#include <buttons/titlebarclosebutton.hpp>
#include <buttons/titlebarmaximizebutton.hpp>
#include <buttons/titlebarminimizebutton.hpp>
#include <buttons/titlebarinfobutton.hpp>
#include <buttons/titlebarprintbutton.hpp>
#include <buttons/titlebarprefsbutton.hpp>

#include <buttons/materialbutton.hpp>

class MaterialDialog : public QWidget
{
    Q_OBJECT

public:
    explicit MaterialDialog(QWidget *parent = 0);
    ~MaterialDialog();

    QVBoxLayout *createTitleBar(const QString &title, const QIcon &icon, int linewidth);
    void addTitleBarButton(TitleBarButton *btn);
    void addBottomSpacer();

    void setDialogTitle(const QString &title);
    void setDialogIcon(const QIcon &icon);

    #define createTitleBarButton(type) \
        this->titlebar##type = new TitleBar##type##Button(this); \
        this->addTitleBarButton(this->titlebar##type)

    #define disableDoubleClickMaximize() \
        void mouseDoubleClickEvent(QMouseEvent*) {}

protected:
    TitleBarPainter *titlebar = nullptr;
    TitleBarCloseButton *titlebarClose = nullptr;
    TitleBarMaximizeButton *titlebarMaximize = nullptr;
    TitleBarMinimizeButton *titlebarMinimize = nullptr;
    TitleBarInfoButton *titlebarInfo = nullptr;
    TitleBarPrintButton *titlebarPrint = nullptr;
    TitleBarPrefsButton *titlebarPrefs = nullptr;

#ifndef Q_OS_ANDROID
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    QPoint m_windowPosition;
#endif

    void resizeEvent(QResizeEvent *event);
    void changeEvent(QEvent *event);

#ifndef Q_OS_ANDROID
    void mouseDoubleClickEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
#endif

    void setModal();

    QVBoxLayout *m_layout;
};

#endif // MATERIALDIALOG_HPP
