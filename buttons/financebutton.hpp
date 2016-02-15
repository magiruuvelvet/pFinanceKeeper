#ifndef FINANCEBUTTON_HPP
#define FINANCEBUTTON_HPP

#include <QPushButton>

#include <QString>
#include <QEvent>
#include <QKeyEvent>
#include <QFocusEvent>

class FinanceButton : public QPushButton
{
    Q_OBJECT

public:
    explicit FinanceButton(QWidget *parent = 0, const QIcon &icon = QIcon());
    ~FinanceButton();

    QString &userData();
    int &btnId();

    int heightForWidth(int) const;

signals:
    void hovered(FinanceButton*);
    void unhovered();

protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);

    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);

    void keyPressEvent(QKeyEvent *event);

private:
    QString m_userData;
    int m_btnId;
};

#endif // FINANCEBUTTON_HPP
