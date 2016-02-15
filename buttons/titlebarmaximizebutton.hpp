#ifndef TITLEBARMAXIMIZEBUTTON_HPP
#define TITLEBARMAXIMIZEBUTTON_HPP

#include <buttons/titlebarbutton.hpp>

class TitleBarMaximizeButton : public TitleBarButton
{
    Q_OBJECT

public:
    /* state of the current window */
    enum State {
        Maximized,
        Windowed
    };

    explicit TitleBarMaximizeButton(QWidget *parent = 0, State = Windowed);
    ~TitleBarMaximizeButton();

    void changeButtonState(State);
    State m_state;

private slots:
    void showMaximized();
    void showWindowed();
};

#endif // TITLEBARMAXIMIZEBUTTON_HPP
