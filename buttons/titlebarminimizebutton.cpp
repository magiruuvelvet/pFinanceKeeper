#include <core/themeloader.hpp>
#include <buttons/titlebarminimizebutton.hpp>
#include <dialogs/materialdialog.hpp>

TitleBarMinimizeButton::TitleBarMinimizeButton(QWidget *parent) :
    TitleBarButton(parent)
{
    this->setIcon(*ThemeLoader::i()->minimizeIcon());
    this->setToolTip(QObject::trUtf8("Minimize"));
    QObject::connect(this, &QPushButton::clicked, this, &TitleBarMinimizeButton::showMinimized);
}

TitleBarMinimizeButton::~TitleBarMinimizeButton()
{
}

void TitleBarMinimizeButton::showMinimized()
{
    static_cast<MaterialDialog*>(this->parent())->showMinimized();
}
