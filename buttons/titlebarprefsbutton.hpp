#ifndef TITLEBARPREFSBUTTON_HPP
#define TITLEBARPREFSBUTTON_HPP

#include <buttons/titlebarbutton.hpp>

class TitleBarPrefsButton : public TitleBarButton
{
    Q_OBJECT

public:
    explicit TitleBarPrefsButton(QWidget *parent = 0);
    ~TitleBarPrefsButton();
};

#endif // TITLEBARPREFSBUTTON_HPP
