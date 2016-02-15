#ifndef APPSETTINGS_HPP
#define APPSETTINGS_HPP

#include <QString>

class AppSettings
{
public:
    static AppSettings *i();
    ~AppSettings();

    void init();

    static const QString AppName;
    static const QString AppVersion;
    static const QString AppCopyright;

    static const QString OrganizationName;
    static const QString OrganizationDomain;

    QString GlobalConfigPath;
    QString ConfigPath;

    static const QString m_Plus, m_Minus;

    int &posX();
    int &posY();

    static const QChar DirSeparator;

private:
    AppSettings();

    int m_posX, m_posY;
};

#endif // APPSETTINGS_HPP
