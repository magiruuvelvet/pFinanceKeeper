#include <core/themeloader.hpp>
#include <buttons/titlebarinfobutton.hpp>

TitleBarInfoButton::TitleBarInfoButton(QWidget *parent) :
    TitleBarButton(parent)
{
    this->setIcon(*ThemeLoader::i()->infoIcon());
    this->setToolTip(QObject::trUtf8("Info"));
}

TitleBarInfoButton::~TitleBarInfoButton()
{
}
