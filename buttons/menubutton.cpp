#include <buttons/menubutton.hpp>
#include <dialogs/mainframe.hpp>
#include <dialogs/aboutdialog.hpp>
#include <dialogs/prefsdialog.hpp>
#include <dialogs/noticedialog.hpp>

MenuButton::MenuButton(QWidget *parent) :
    MaterialButton(parent)
{
    this->setIconSize(QSize(90, 90));
    this->setFixedSize(90, 90);
    this->setIcon(*ThemeLoader::i()->menuBtn());
    this->setStyleSheet("QLabel { color: #444444; } QPushButton { background-color: rgb(0,0,0,0); border: 0px solid rgb(0,0,0,0); outline: 0; }");

    this->m_font = new QFont();
    this->m_font->setPointSize(50);

    this->m_popup = new QMenu(this);
    this->m_prefs = new QAction(*ThemeLoader::i()->prefsIcon(), QObject::trUtf8("Preferences"), this->m_popup);
    this->m_backup_restore = new QAction(QIcon(), QObject::trUtf8("Backup && Restore"), this->m_popup);
    this->m_backup_restore->setEnabled(false);
    this->m_about = new QAction(*ThemeLoader::i()->infoIcon(), QObject::trUtf8("Info"), this->m_popup);
    this->m_quit = new QAction(*ThemeLoader::i()->closeIcon(), QObject::trUtf8("Quit"), this->m_popup);

    this->m_prefs->setFont(*this->m_font);
    this->m_backup_restore->setFont(*this->m_font);
    this->m_about->setFont(*this->m_font);
    this->m_quit->setFont(*this->m_font);

    QObject::connect(this->m_prefs, &QAction::triggered, this, &MenuButton::prefs_triggered);
    QObject::connect(this->m_backup_restore, &QAction::triggered, this, &MenuButton::backup_restore_triggered);
    QObject::connect(this->m_about, &QAction::triggered, this, &MenuButton::about_triggered);
    QObject::connect(this->m_quit, &QAction::triggered, this, &MenuButton::quit_triggered);

    this->m_popup->addAction(this->m_prefs);
    this->m_popup->addAction(this->m_backup_restore);
    this->m_popup->addAction(this->m_about);
    this->m_popup->addSeparator();
    this->m_popup->addAction(this->m_quit);

    QObject::connect(this, &MaterialButton::clicked, this, &MenuButton::popupMenu);

    this->m_status = new NoticeDialog();
    this->m_status->setDialogTitle(this->m_backup_restore->text());
    this->m_status->setOkButtonText(QObject::trUtf8("OK"));
    this->m_status->hideCancelButton();
    this->m_status->keepOnTop();
}

MenuButton::~MenuButton()
{
    delete this->m_popup;

    delete this->m_prefs;
    delete this->m_backup_restore;
    delete this->m_about;
    delete this->m_quit;

    delete this->m_font;

    delete this->m_status;

#ifdef Q_OS_ANDROID
    this->dataAbsPath.clear();
#endif
}

void MenuButton::prefs_triggered()
{
    prefsDialog->show();
}

void MenuButton::backup_restore_triggered()
{
#ifdef Q_OS_ANDROID
    if (this->dataAbsPath.isEmpty()) {
        this->mediaDir = QAndroidJniObject::callStaticObjectMethod("android/os/Environment", "getExternalStorageDirectory", "()Ljava/io/File;");
        this->mediaPath = mediaDir.callObjectMethod("getAbsolutePath", "()Ljava/lang/String;");

        this->activity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative", "activity", "()Landroid/app/Activity;");
        this->package = activity.callObjectMethod("getPackageName", "()Ljava/lang/String;");

        this->dataAbsPath = mediaPath.toString()+"/Android/data/" + this->package.toString() + "/";

        if (this->jniEnv->ExceptionCheck()) {
            this->m_status->setMessage(QObject::trUtf8("There was an error accessing the internal memory.\n\n"
                                                       "The backup and restore feature cannot work without is capability."));
            (void) this->m_status->exec();
            this->jniEnv->ExceptionClear();
            return;
        }
    } // end obtain path

    // TODO:: implement backup & restore feature
#endif
}

void MenuButton::about_triggered()
{
    aboutDialog->show();
}

void MenuButton::quit_triggered()
{
    static_cast<MainFrame*>(this->parent())->close();
}

void MenuButton::popupMenu()
{
    this->m_popup->popup(QPoint( this->x() + this->width() , this->y() + this->height() ));
}
