#include <core/themeloader.hpp>
#include <buttons/titlebarprintbutton.hpp>

TitleBarPrintButton::TitleBarPrintButton(QWidget *parent) :
    TitleBarButton(parent)
{
    this->setIcon(*ThemeLoader::i()->printIcon());
    this->setToolTip(QObject::trUtf8("Print"));
}

TitleBarPrintButton::~TitleBarPrintButton()
{
}
