#include <decorations/titlebarpainter.hpp>

#ifdef Q_OS_ANDROID
    #include <QApplication>
    #include <QDesktopWidget>
    #define L_ICON_SIZE 130, 130
    #define L_FONT_SIZE 40
    #define L_TITLE_HEIGHT 150
#else
    #define L_ICON_SIZE 30, 30
    #define L_FONT_SIZE 16
    #define L_TITLE_HEIGHT 40
#endif

TitleBarPainter::TitleBarPainter(QWidget *widget)
{
    /* create pointer to the given widget */
    this->m_widget = widget;

    /* setup widget properties */
    this->m_widget->setWindowFlags(Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint | Qt::FramelessWindowHint | Qt::Widget);

#ifdef Q_OS_ANDROID
    this->m_widget->setMinimumSize(QApplication::desktop()->availableGeometry().size());
#else
    this->m_widget->setMinimumSize(260, 270);
#endif

    /* draw background */
    this->ui_bg = new QPalette();
    this->updateBackground();

    /* create layout */
    this->m_layout = new QVBoxLayout();
    this->m_layout->setContentsMargins(0,0,0,0);
    this->m_layout->setSpacing(0);

    this->ui_title = new QLabel();
    this->ui_title_font = new QFont();
    this->ui_title_font->setPointSize(L_FONT_SIZE);
    this->ui_title_font->setWeight(75);
    this->ui_title->setFont(*this->ui_title_font);
    this->ui_title->setFixedHeight(L_TITLE_HEIGHT);
    this->ui_title->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    this->ui_icon = new QLabel();
    this->ui_icon->setFixedSize(L_ICON_SIZE);

    this->layout_master = new QVBoxLayout();
    this->layout_master->setSpacing(0);
    this->layout_master->setContentsMargins(0,0,0,0);

    this->layout_container = new QHBoxLayout();
    this->layout_container->setSpacing(0);
    this->layout_container->setContentsMargins(0,0,0,0);

    this->layout_btnBox = new QHBoxLayout();
    this->layout_btnBox->setSpacing(0);
    this->layout_btnBox->setContentsMargins(0,0,0,0);

    this->layout_leftSpacer = new QSpacerItem(15, 15, QSizePolicy::Minimum, QSizePolicy::Minimum);
    this->layout_middleSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    this->layout_rightSpacer = new QSpacerItem(15, 15, QSizePolicy::Minimum, QSizePolicy::Minimum);
    this->layout_btnBoxSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Minimum);

    this->layout_widgetBox = new QVBoxLayout();
    this->layout_widgetBox->setSpacing(0);
    this->layout_widgetBox->setContentsMargins(0,0,0,0);
    this->layout_widgetContainer = new QHBoxLayout();
    this->layout_widgetContainer->setSpacing(10);
    this->layout_widgetContainer->setContentsMargins(0,0,0,0);
    this->layout_widgetBox->addItem(this->layout_widgetContainer);

    this->layout_widgetContainer->addWidget(this->ui_icon);
    this->layout_widgetContainer->addWidget(this->ui_title);

    this->layout_btnContainer = new QVBoxLayout();
    this->layout_btnContainer->setSpacing(0);
    this->layout_btnContainer->setContentsMargins(0,0,0,0);
#ifdef Q_OS_ANDROID
    this->layout_menuBtn_center = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Minimum);
    this->layout_btnContainer->addItem(this->layout_menuBtn_center);
#endif
    this->layout_btnContainer->addItem(this->layout_btnBox);
    this->layout_btnContainer->addItem(this->layout_btnBoxSpacer);

    this->layout_container->addItem(this->layout_leftSpacer);
    this->layout_container->addItem(this->layout_widgetBox);
    this->layout_container->addItem(this->layout_middleSpacer);
    this->layout_container->addItem(this->layout_btnContainer);
    this->layout_container->addItem(this->layout_rightSpacer);

    this->layout_bottomLine = new QFrame();
    this->layout_bottomLine->setLineWidth(0);
    this->layout_bottomLine->setFrameShadow(QFrame::Plain);
    this->layout_bottomLine->setFrameShape(QFrame::HLine);

    this->layout_bottomFixSpacer = new QFrame();
    this->layout_bottomFixSpacer->setLineWidth(0);
    this->layout_bottomFixSpacer->setFrameShadow(QFrame::Plain);
    this->layout_bottomFixSpacer->setFrameShape(QFrame::Panel);
    this->layout_bottomFixSpacer->setFixedHeight(5);

    this->layout_master->addItem(this->layout_container);
    this->layout_master->addWidget(this->layout_bottomLine);
    this->layout_master->addWidget(this->layout_bottomFixSpacer);

    this->m_layout->addItem(this->layout_master);

    this->m_parent_layout = new QVBoxLayout();
    this->m_parent_layout->setContentsMargins(5,5,5,5);
    this->m_parent_layout->setSpacing(0);

    this->layout_bottomParent = new QSpacerItem(20, 4, QSizePolicy::Expanding, QSizePolicy::Expanding);

    this->m_layout->addItem(this->m_parent_layout);
}

TitleBarPainter::~TitleBarPainter()
{
    delete this->m_layout;

    delete this->ui_icon;
    delete this->ui_title;
    delete this->ui_title_font;

#ifdef Q_OS_ANDROID
    delete this->menuBtn;
#endif

    delete this->ui_bg;
}

QVBoxLayout *TitleBarPainter::paint(const QString &title, const QIcon &icon, int linewidth)
{
    this->setWindowTitle(title);
    this->setWindowIcon(icon);

    this->layout_bottomLine->setLineWidth(linewidth);
    this->m_widget->setLayout(this->m_layout);

    return this->m_parent_layout;
}

#ifdef Q_OS_ANDROID
void TitleBarPainter::createMenuButton()
{
    this->menuBtn = new MenuButton(this->m_widget);
    this->layout_btnBox->addWidget(this->menuBtn);
}
#endif

void TitleBarPainter::addButton(TitleBarButton *btn)
{
    this->layout_btnBox->addWidget(btn);
}

void TitleBarPainter::addButtonSpacer(int size)
{
    this->layout_btnBox->addSpacing(size);
}

void TitleBarPainter::updateBackground()
{
    this->ui_bg->setBrush(this->m_widget->backgroundRole(),
                          QBrush((*ThemeLoader::i()->bg()).scaled(this->m_widget->size(),
                                                                  Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    this->m_widget->setPalette(*this->ui_bg);
}

int TitleBarPainter::linewidth() const
{
    return this->layout_bottomLine->lineWidth();
}

void TitleBarPainter::addBottomSpacer()
{
    this->m_layout->addItem(this->layout_bottomParent);
}

void TitleBarPainter::setWindowTitle(const QString &title)
{
    this->ui_title->setText(title);
    this->m_widget->setWindowTitle(title);
}

void TitleBarPainter::setWindowIcon(const QIcon &icon)
{
    this->m_widget->setWindowIcon(icon);
    this->ui_icon->setPixmap(icon.pixmap(L_ICON_SIZE));
}
