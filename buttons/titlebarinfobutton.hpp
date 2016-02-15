#ifndef TITLEBARINFOBUTTON_HPP
#define TITLEBARINFOBUTTON_HPP

#include <buttons/titlebarbutton.hpp>

class TitleBarInfoButton : public TitleBarButton
{
    Q_OBJECT

public:
    explicit TitleBarInfoButton(QWidget *parent = 0);
    ~TitleBarInfoButton();
};

#endif // TITLEBARINFOBUTTON_HPP
