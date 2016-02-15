#ifndef TITLEBARCLOSEBUTTON_HPP
#define TITLEBARCLOSEBUTTON_HPP

#include <buttons/titlebarbutton.hpp>

class TitleBarCloseButton : public TitleBarButton
{
    Q_OBJECT

public:
    explicit TitleBarCloseButton(QWidget *parent = 0);
    ~TitleBarCloseButton();

private slots:
    void close();
};

#endif // TITLEBARCLOSEBUTTON_HPP
