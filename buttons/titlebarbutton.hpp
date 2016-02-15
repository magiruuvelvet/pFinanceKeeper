#ifndef TITLEBARBUTTON_HPP
#define TITLEBARBUTTON_HPP

#include <QPushButton>

class TitleBarButton : public QPushButton
{
    Q_OBJECT

public:
    explicit TitleBarButton(QWidget *parent = 0, const QString &tooltip = QString());
    ~TitleBarButton();

    void setToolTip(const QString &tooltip);
};

#endif // TITLEBARBUTTON_HPP
