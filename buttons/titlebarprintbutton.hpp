#ifndef TITLEBARPRINTBUTTON_HPP
#define TITLEBARPRINTBUTTON_HPP

#include <buttons/titlebarbutton.hpp>

class TitleBarPrintButton : public TitleBarButton
{
    Q_OBJECT

public:
    explicit TitleBarPrintButton(QWidget *parent = 0);
    ~TitleBarPrintButton();
};

#endif // TITLEBARPRINTBUTTON_HPP
