#ifndef MATERIALBUTTON_HPP
#define MATERIALBUTTON_HPP

#include <QPushButton>
#include <QVariant>

class QKeyEvent;

class MaterialButton : public QPushButton
{
    Q_OBJECT

public:
    explicit MaterialButton(QWidget *parent = 0);
    ~MaterialButton();

    QVariant &userData();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    QVariant m_userData;
};

#endif // MATERIALBUTTON_HPP
