#include <QStandardPaths>
#include <QDir>

#include <vector>

#ifdef Q_OS_ANDROID
#include <sys/stat.h>
#endif

#include <core/appsettings.hpp>

const QString AppSettings::AppName = QString::fromUcs4(std::vector<uint>({112, 70, 105, 110, 97, 110, 99, 101, 32, 75, 101, 101, 112, 101, 114}).data(), 15);
const QString AppSettings::AppVersion = "v0.6";
const QString AppSettings::AppCopyright = QString::fromUcs4(std::vector<uint>({
                                              67, 111, 112, 121, 114, 105, 103, 104, 116, 32, 169, 32,
                                              76, 101, 110, 97, 32, 83, 116, 246, 102, 102, 108, 101, 114,
                                              44, 32, 65, 108, 108, 32, 114, 105, 103, 104, 116, 32, 114, 101, 115, 101, 114, 118, 101, 100, 46}).data(), 46);

const QString AppSettings::OrganizationName = QString::fromUcs4(std::vector<uint>({
                                              76, 101, 110, 97, 32, 83, 116, 246, 102, 102, 108, 101, 114}).data(), 13);
const QString AppSettings::OrganizationDomain = QString::fromUcs4(std::vector<uint>({
                                              99, 111, 109, 46, 108, 101, 110, 97, 115, 116, 111, 102, 102, 108, 101, 114}).data(), 16);

const QChar AppSettings::DirSeparator = QDir::separator();

const QString AppSettings::m_Plus = QString::fromUcs4(std::vector<uint>({65291, 32}).data(), 2);
const QString AppSettings::m_Minus = QString::fromUcs4(std::vector<uint>({12540, 32}).data(), 2);

AppSettings *AppSettings::i()
{
    static AppSettings *instance = new AppSettings();
    return instance;
}

void AppSettings::init()
{
}

AppSettings::AppSettings()
{
    this->GlobalConfigPath = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
    this->ConfigPath = this->GlobalConfigPath + this->DirSeparator + this->AppName + this->DirSeparator;

#ifdef Q_OS_ANDROID
    static auto mkdir_tree = [](const char *dir) {
        char tmp[256];
        char *p = NULL;
        size_t len;

        snprintf(tmp, sizeof(tmp), "%s", dir);
        len = strlen(tmp);
        if (tmp[len - 1] == '/')
                tmp[len - 1] = 0;
        for (p = tmp + 1; *p; p++)
                if(*p == '/') {
                        *p = 0;
                        mkdir(tmp, S_IRWXU);
                        *p = '/';
                }
        mkdir(tmp, S_IRWXU);
    };
    mkdir_tree((this->GlobalConfigPath + this->DirSeparator + this->AppName).toUtf8().data());
#else
    QDir path(this->GlobalConfigPath);
    (void) path.mkdir(this->AppName);
#endif

    this->m_posX = 0;
    this->m_posY = 0;
}

AppSettings::~AppSettings()
{
    this->GlobalConfigPath.clear();
    this->ConfigPath.clear();

    delete this; // Automatically delete from stack on program termination
}

int &AppSettings::posX()
{
    return this->m_posX;
}

int &AppSettings::posY()
{
    return this->m_posY;
}
