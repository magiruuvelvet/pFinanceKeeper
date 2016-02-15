#include <core/themeloader.hpp>
#include <buttons/titlebarprefsbutton.hpp>

TitleBarPrefsButton::TitleBarPrefsButton(QWidget *parent) :
    TitleBarButton(parent)
{
    this->setIcon(*ThemeLoader::i()->prefsIcon());
    this->setToolTip(QObject::trUtf8("Preferences"));
}

TitleBarPrefsButton::~TitleBarPrefsButton()
{
}
