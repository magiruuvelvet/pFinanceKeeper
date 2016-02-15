#include <core/themeloader.hpp>
#include <buttons/titlebarmaximizebutton.hpp>
#include <dialogs/materialdialog.hpp>

TitleBarMaximizeButton::TitleBarMaximizeButton(QWidget *parent, State state) :
    TitleBarButton(parent)
{
    this->changeButtonState(state);
}

TitleBarMaximizeButton::~TitleBarMaximizeButton()
{
}

void TitleBarMaximizeButton::showMaximized()
{
    static_cast<MaterialDialog*>(this->parent())->showMaximized();
    this->changeButtonState(Maximized);
}

void TitleBarMaximizeButton::showWindowed()
{
    static_cast<MaterialDialog*>(this->parent())->showNormal();
    this->changeButtonState(Windowed);
}

void TitleBarMaximizeButton::changeButtonState(State state)
{
    this->m_state = state;
    QObject::disconnect(this, &QPushButton::clicked, 0, 0);

    switch (this->m_state) {
        case Windowed:
            this->setIcon(*ThemeLoader::i()->maximizeIcon());
            this->setToolTip(QObject::trUtf8("Maximize"));
            QObject::connect(this, &QPushButton::clicked, this, &TitleBarMaximizeButton::showMaximized);
            this->m_state = Maximized;
            break;

        case Maximized:
            this->setIcon(*ThemeLoader::i()->unmaximizeIcon());
            this->setToolTip(QObject::trUtf8("Unmaximize"));
            QObject::connect(this, &QPushButton::clicked, this, &TitleBarMaximizeButton::showWindowed);
            this->m_state = Windowed;
            break;
    }
}
