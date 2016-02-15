#include <QApplication>

#include <core/appsettings.hpp>
#include <core/themeloader.hpp>
#include <core/databasemanager.hpp>
#include <core/amountvalidator.hpp>

#include <dialogs/mainframe.hpp>
#include <dialogs/noticedialog.hpp>
#include <dialogs/aboutdialog.hpp>
#include <dialogs/prefsdialog.hpp>

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    AppSettings::i()->init();
    ThemeLoader::i()->init();

    a.setApplicationName(AppSettings::i()->AppName);
    a.setApplicationVersion(AppSettings::i()->AppVersion);
    a.setOrganizationName(AppSettings::i()->OrganizationName);
    a.setOrganizationDomain(AppSettings::i()->OrganizationDomain);
    a.setStyleSheet(ThemeLoader::i()->styleSheet());

    if (!DatabaseManager::i()->open()) {
        NoticeDialog *dbError = new NoticeDialog();
        QString btnOkText = QObject::trUtf8("Continue");
        QString btnCancelText = QObject::trUtf8("Quit");
        dbError->setDialogTitle(QObject::trUtf8("Database Error"));
        dbError->setDialogIcon(*ThemeLoader::i()->alertIcon());
        dbError->setMessage(QObject::trUtf8("The database is corrupt :/"
                                            "\n"
                                            "Press '%1' to create a new one..."
                                            "\n"
                                            "Press '%2' to exit %3")
                            .arg(btnOkText,
                                 btnCancelText,
                                 AppSettings::i()->AppName));
        dbError->setOkButtonText(btnOkText);
        dbError->setCancelButtonText(btnCancelText);
        dbError->setOkButtonIcon(*ThemeLoader::i()->appIcon());
        dbError->setCancelButtonIcon(*ThemeLoader::i()->closeIcon());

        if (!dbError->exec()) {
            delete dbError;
            btnOkText.clear();
            btnCancelText.clear();
            std::exit(5); // force quit, 5 = corrupt db
        } else {
            if (!DatabaseManager::i()->remove()) {
                dbError->setMessage(QObject::trUtf8("The configuration path '%1' is not writable, "
                                                    "you need to fix this problem by hand before you can continue!")
                                    .arg(AppSettings::i()->ConfigPath));
                dbError->setOkButtonText(QObject::trUtf8("OK"));
                dbError->setOkButtonIcon(*ThemeLoader::i()->closeIcon());
                dbError->hideCancelButton();
                (void) dbError->exec();
                delete dbError;
                std::exit(7); // force quit, 7 = no writable location for db found or other permission problem
            }
        }
    }

    amountValidator = new QRegExpValidator(QRegExp("^\\d{1,3}(([.]\\d{3})*),(\\d{2})$"));

    aboutDialog = new AboutDialog();
    prefsDialog = new PrefsDialog();

    mainframe = new MainFrame();
    mainframe->show();

    return a.exec();
}
