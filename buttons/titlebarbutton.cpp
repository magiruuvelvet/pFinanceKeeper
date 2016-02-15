#include <buttons/titlebarbutton.hpp>

TitleBarButton::TitleBarButton(QWidget *parent, const QString &tooltip) :
    QPushButton(parent)
{
    this->setFixedSize(20, 20);
    this->setIconSize(QSize(20, 20));
    this->setFocusPolicy(Qt::NoFocus);
    this->setFlat(true);
    this->setAutoFillBackground(true);

    if (!tooltip.isEmpty())
        QPushButton::setToolTip(tooltip);
}

TitleBarButton::~TitleBarButton()
{
}

void TitleBarButton::setToolTip(const QString &tooltip)
{
    QPushButton::setToolTip(tooltip);
}
