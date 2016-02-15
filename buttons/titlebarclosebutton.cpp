#include <core/themeloader.hpp>
#include <buttons/titlebarclosebutton.hpp>

TitleBarCloseButton::TitleBarCloseButton(QWidget *parent) :
    TitleBarButton(parent)
{
    this->setIcon(*ThemeLoader::i()->closeIcon());
    this->setToolTip(QObject::trUtf8("Close"));
    QObject::connect(this, &QPushButton::clicked, this, &TitleBarCloseButton::close);
}

TitleBarCloseButton::~TitleBarCloseButton()
{
}

void TitleBarCloseButton::close()
{
    static_cast<QWidget*>(this->parent())->close();
}
