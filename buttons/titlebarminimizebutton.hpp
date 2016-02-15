#ifndef TITLEBARMINIMIZEBUTTON_HPP
#define TITLEBARMINIMIZEBUTTON_HPP

#include <buttons/titlebarbutton.hpp>

class TitleBarMinimizeButton : public TitleBarButton
{
    Q_OBJECT

public:
    explicit TitleBarMinimizeButton(QWidget *parent = 0);
    ~TitleBarMinimizeButton();

private slots:
    void showMinimized();
};

#endif // TITLEBARMINIMIZEBUTTON_HPP
