#include <dialogs/noticedialog.hpp>

#ifdef Q_OS_ANDROID
    #include <QApplication>
    #include <QDesktopWidget>
    #define L_FONT_SIZE_MSG 22
    #define L_FONT_SIZE_BTN 25
    #define L_ICON_SIZE_BTN 60, 60
    #define L_BTN_MINIMUM_HEIGTH 100
#else
    #define L_FONT_SIZE_MSG 12
    #define L_FONT_SIZE_BTN 12
    #define L_ICON_SIZE_BTN 38, 38
    #define L_BTN_MINIMUM_HEIGTH 40
#endif

NoticeDialog::NoticeDialog(QWidget *parent) :
    MaterialDialog(parent)
{
    this->m_layout = this->createTitleBar(QObject::trUtf8("Notice"), *ThemeLoader::i()->infoIcon(), 1);
    this->m_layout->setContentsMargins(12,7,12,7);
#ifndef Q_OS_ANDROID
    createTitleBarButton(Close);
#endif

#ifdef Q_OS_ANDROID
    this->setMinimumSize(QApplication::desktop()->availableGeometry().size());
#endif

    QObject::connect(this->titlebarClose, &TitleBarCloseButton::clicked, this, &NoticeDialog::close);

    this->msgFont = new QFont();
    this->msgFont->setPointSize(L_FONT_SIZE_MSG);
    this->msgFont->setBold(true);

    this->btnFont = new QFont();
    this->btnFont->setPointSize(L_FONT_SIZE_BTN);

    this->message = new QLabel(this);
    this->message->setFont(*this->msgFont);
    this->message->setWordWrap(true);
    this->m_layout->addWidget(this->message);

    this->btnLayout = new QHBoxLayout();
    this->btnLayout->setContentsMargins(7,5,7,7);
    this->btnLayout->setSpacing(15);

    this->btnSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    this->m_layout->addItem(this->btnSpacer);

    this->btnCancel = new MaterialButton(this);
    this->btnCancel->setMinimumHeight(L_BTN_MINIMUM_HEIGTH);
    this->btnCancel->setFont(*this->btnFont);
    this->btnCancel->setIconSize(QSize(L_ICON_SIZE_BTN));
    this->btnCancel->setIcon(this->btnCancel->icon().pixmap(L_ICON_SIZE_BTN));
    this->btnOk = new MaterialButton(this);
    this->btnOk->setMinimumHeight(L_BTN_MINIMUM_HEIGTH);
    this->btnOk->setFont(*this->btnFont);
    this->btnOk->setIconSize(QSize(L_ICON_SIZE_BTN));
    this->btnOk->setIcon(this->btnOk->icon().pixmap(L_ICON_SIZE_BTN));

    this->btnLayout->addWidget(this->btnCancel);
    this->btnLayout->addWidget(this->btnOk);

    this->m_layout->addItem(this->btnLayout);

    QObject::connect(this->btnOk, &MaterialButton::clicked, this, &NoticeDialog::accepted);
    QObject::connect(this->btnCancel, &MaterialButton::clicked, this, &NoticeDialog::rejected);
}

NoticeDialog::~NoticeDialog()
{
    delete this->msgFont;
    delete this->btnFont;

    delete this->message;
    delete this->btnOk;
    delete this->btnCancel;
}

void NoticeDialog::setMessage(const QString &msg)
{
    this->message->setText(msg);
}

void NoticeDialog::setOkButtonText(const QString &text)
{
    this->btnOk->setText(text);
}

void NoticeDialog::setCancelButtonText(const QString &text)
{
    this->btnCancel->setText(text);
}

void NoticeDialog::setOkButtonIcon(const QIcon &icon)
{
    this->btnOk->setIcon(icon);
}

void NoticeDialog::setCancelButtonIcon(const QIcon &icon)
{
    this->btnCancel->setIcon(icon);
}

void NoticeDialog::hideCancelButton()
{
    this->btnCancel->setEnabled(false);
    this->btnCancel->setVisible(false);
}

void NoticeDialog::keepOnTop()
{
    this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);
}

bool NoticeDialog::exec()
{
    this->setModal();
    this->show();

    this->eventLoop = new QEventLoop(this);
    this->eventLoop->exec();
    delete this->eventLoop;

    MaterialDialog::close();
    return this->m_dialogAccepted;
}

void NoticeDialog::accepted()
{
    this->m_dialogAccepted = true;
    this->eventLoop->exit(this->m_dialogAccepted);
}

void NoticeDialog::rejected()
{
    this->m_dialogAccepted = false;
    this->eventLoop->exit(this->m_dialogAccepted);
}

void NoticeDialog::close()
{
    this->m_dialogAccepted = false;
    this->eventLoop->exit(this->m_dialogAccepted);
}

void NoticeDialog::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
        emit close();

    event->accept();
}
