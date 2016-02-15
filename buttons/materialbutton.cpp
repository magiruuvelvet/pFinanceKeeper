#include <QKeyEvent>

#include <core/themeloader.hpp>
#include <buttons/materialbutton.hpp>
#include <dialogs/materialdialog.hpp>
#include <dialogs/noticedialog.hpp>

MaterialButton::MaterialButton(QWidget *parent) :
    QPushButton(parent)
{
    this->setFocusPolicy(Qt::StrongFocus);
    this->setFlat(true);
    this->setAutoFillBackground(true);
}

MaterialButton::~MaterialButton()
{
    this->m_userData.clear();
}

void MaterialButton::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Space)
        emit clicked();

    else if (event->key() == Qt::Key_Escape) {
        if (qobject_cast<NoticeDialog*>(this->parent()) != nullptr)
            static_cast<NoticeDialog*>(this->parent())->close();
        else if (qobject_cast<MaterialDialog*>(this->parent()) != nullptr)
            static_cast<MaterialDialog*>(this->parent())->close();
        else static_cast<QWidget*>(this->parent())->close();
    }
}

QVariant &MaterialButton::userData()
{
    return this->m_userData;
}
