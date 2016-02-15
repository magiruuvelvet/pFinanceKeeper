#ifndef NOTICEDIALOG_HPP
#define NOTICEDIALOG_HPP

#include <dialogs/materialdialog.hpp>

#include <QEventLoop>

class NoticeDialog : public MaterialDialog
{
    Q_OBJECT

public:
    explicit NoticeDialog(QWidget *parent = 0);
    ~NoticeDialog();

    void setMessage(const QString &msg);

    void setOkButtonText(const QString &text);
    void setCancelButtonText(const QString &text);

    void setOkButtonIcon(const QIcon &icon);
    void setCancelButtonIcon(const QIcon &icon);

    void hideCancelButton(); // for information only, where the user doesn't need to choose an action

    void keepOnTop(); // keep dialog on top, for IMPORTANT messages!!

    bool exec(); // reimplement QDialog::exec() using QEventLoop, because the TitleBarPainter doesn't work with Qt's Dialog implementation

private slots:
    void accepted();
    void rejected();

public slots:
    void close();

protected:
    void keyPressEvent(QKeyEvent *event);
    disableDoubleClickMaximize()

private:
    QEventLoop *eventLoop;

private:
    QHBoxLayout *btnLayout;
    QSpacerItem *btnSpacer;

    QFont *msgFont;
    QFont *btnFont;

    QLabel *message;
    MaterialButton *btnOk;
    MaterialButton *btnCancel;

    bool m_dialogAccepted = false;
};

#endif // NOTICEDIALOG_HPP
