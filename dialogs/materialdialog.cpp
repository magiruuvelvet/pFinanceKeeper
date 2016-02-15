#include <dialogs/materialdialog.hpp>

#define DELETE(object) if (object != nullptr) delete object

MaterialDialog::MaterialDialog(QWidget *parent) :
    QWidget(parent)
{
    this->titlebar = new TitleBarPainter(this);
}

MaterialDialog::~MaterialDialog()
{
    delete this->titlebar;

    DELETE(this->titlebarClose);
    DELETE(this->titlebarMaximize);
    DELETE(this->titlebarMinimize);
    DELETE(this->titlebarInfo);
    DELETE(this->titlebarPrint);
    DELETE(this->titlebarPrefs);
}

QVBoxLayout *MaterialDialog::createTitleBar(const QString &title, const QIcon &icon, int linewidth)
{
    return this->titlebar->paint(title, icon, linewidth);
}

void MaterialDialog::addTitleBarButton(TitleBarButton *btn)
{
    if (btn != nullptr)
        this->titlebar->addButton(btn);
}

void MaterialDialog::addBottomSpacer()
{
    this->titlebar->addBottomSpacer();
}

void MaterialDialog::setDialogTitle(const QString &title)
{
    this->titlebar->setWindowTitle(title);
}

void MaterialDialog::setDialogIcon(const QIcon &icon)
{
    this->titlebar->setWindowIcon(icon);
}

void MaterialDialog::setModal()
{
    this->setWindowFlags(this->windowFlags() | Qt::Dialog);
}

#ifndef Q_OS_ANDROID
void MaterialDialog::mousePressEvent(QMouseEvent *event)
{
    this->m_windowPosition = event->globalPos();
}

void MaterialDialog::mouseMoveEvent(QMouseEvent *event)
{
    if ( this->mapFromGlobal(QCursor::pos()).y() < ( 63 - this->titlebar->linewidth() ) ) {
        const QPoint delta = event->globalPos() - this->m_windowPosition;
        this->move(this->x() + delta.x(), this->y() + delta.y());
        this->m_windowPosition = event->globalPos();
    }
}
#endif

void MaterialDialog::resizeEvent(QResizeEvent *event)
{
    this->titlebar->updateBackground();
    event->accept();
}

void MaterialDialog::changeEvent(QEvent *event)
{
    if (this->titlebarMaximize != nullptr) {
        if (event->type() == QEvent::WindowStateChange) {
            if (this->isMaximized())
                this->titlebarMaximize->changeButtonState(TitleBarMaximizeButton::Maximized);
            else
                this->titlebarMaximize->changeButtonState(TitleBarMaximizeButton::Windowed);
        }
    }

    event->accept();
}

#ifndef Q_OS_ANDROID
void MaterialDialog::mouseDoubleClickEvent(QMouseEvent *event)
{
    if ( this->mapFromGlobal(QCursor::pos()).y() < ( 63 - this->titlebar->linewidth() ) ) {
        if (event->button() == Qt::LeftButton) {
            if (this->isMaximized())
                this->showNormal();
            else this->showMaximized();
        }
    }
}

void MaterialDialog::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
        emit close();
    event->accept();
}
#endif
