#ifndef MENUBUTTON_HPP
#define MENUBUTTON_HPP

#include <QMenu>
#include <QAction>

#ifdef Q_OS_ANDROID
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#endif

#include <core/themeloader.hpp>
#include <buttons/materialbutton.hpp>

class NoticeDialog; // do not include <dialogs/noticedialog.hpp> here, causes compilation error, maybe bug in GCC ??

class MenuButton : public MaterialButton
{
    Q_OBJECT

public:
    explicit MenuButton(QWidget *parent = 0);
    ~MenuButton();

private slots:
    void prefs_triggered();
    void backup_restore_triggered();
    void about_triggered();
    void quit_triggered();

    void popupMenu();

private:
    QMenu *m_popup;

    QAction *m_prefs,
            *m_backup_restore,
            *m_about,
            *m_quit;   // provide a simple way to quit the application on android

    QFont *m_font;

    NoticeDialog *m_status;

#ifdef Q_OS_ANDROID
    QAndroidJniObject mediaDir,
                      mediaPath;
    QAndroidJniObject activity,
                      package;
    QString           dataAbsPath;
    QAndroidJniEnvironment jniEnv;
#endif
};

#endif // MENUBUTTON_HPP
