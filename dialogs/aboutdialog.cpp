#include <dialogs/aboutdialog.hpp>
#include <core/appsettings.hpp>

#ifdef Q_OS_ANDROID
    #define L_SIZE_TITLE        35
    #define L_SIZE_VERSION      23
    #define L_SIZE_COPYRIGHT    17
    #define L_SIZE_DESC         16
    #define L_SIZE_ICON         170, 170
#else
    #define L_SIZE_TITLE        20
    #define L_SIZE_VERSION      15
    #define L_SIZE_COPYRIGHT    12
    #define L_SIZE_DESC         11
    #define L_SIZE_ICON         100, 100
#endif

AboutDialog *aboutDialog = nullptr;

AboutDialog::AboutDialog(QWidget *parent)
    : MaterialDialog(parent)
{
    this->m_layout = this->createTitleBar(QObject::trUtf8("About"), *ThemeLoader::i()->infoIcon(), 2);
    this->m_layout->setContentsMargins(0,0,0,0);
    this->setWindowFlags(Qt::WindowCloseButtonHint | Qt::FramelessWindowHint | Qt::Dialog);
#ifndef Q_OS_ANDROID
    createTitleBarButton(Close);
#endif

#ifndef Q_OS_ANDROID
    this->setFixedSize(462, 634);
#endif

    this->m_grid = new QGridLayout();
    this->m_grid->setContentsMargins(17,17,17,17);
    this->m_grid->setSpacing(7);
    this->m_layout->addLayout(this->m_grid);

    this->spacer = new QFrame(this);
    this->spacer->setFrameShadow(QFrame::Plain);
    this->spacer->setFrameShape(QFrame::HLine);
    this->spacer->setLineWidth(1);
    this->m_layout->addWidget(this->spacer);

    this->m_gridqt = new QGridLayout();
    this->m_gridqt->setContentsMargins(17,17,17,17);
    this->m_gridqt->setSpacing(7);
    this->m_layout->addLayout(this->m_gridqt);

    this->addBottomSpacer();

    /* create fonts */
    this->font_title = this->createFont(L_SIZE_TITLE, true, false);
    this->font_version = this->createFont(L_SIZE_VERSION, false, true);
    this->font_copyright = this->createFont(L_SIZE_COPYRIGHT, false, false);
    this->font_desc = this->createFont(L_SIZE_DESC, false, false);

    /* create about app */
    this->m_appicon = new QLabel(this);
    this->m_appicon->setFixedSize(L_SIZE_ICON);
    this->m_appicon->setPixmap(ThemeLoader::i()->appIcon()->pixmap(L_SIZE_ICON));
    this->m_grid->addWidget(this->m_appicon, 0, 0, 3, 1);

    this->m_appname = new QLabel(this);
    this->m_appname->setFont(*this->font_title);
    this->m_appname->setText(AppSettings::i()->AppName);
    this->m_grid->addWidget(this->m_appname, 0, 1, 1, 1);

    this->m_appversion = new QLabel(this);
    this->m_appversion->setFont(*this->font_version);
    this->m_appversion->setText(AppSettings::i()->AppVersion);
    this->m_grid->addWidget(this->m_appversion, 1, 1, 1, 1);

    this->m_appcopyright = new QLabel(this);
    this->m_appcopyright->setFont(*this->font_copyright);
    this->m_appcopyright->setText(AppSettings::i()->AppCopyright);
    this->m_grid->addWidget(this->m_appcopyright, 2, 1, 1, 1);

    this->m_grid->addWidget(new QLabel(this), 3, 0, 1, 2);

    this->m_appdesc = new QLabel(this);
    this->m_appdesc->setText(QObject::trUtf8("%1 helps you to keep track of your personal earnings and expenses.\n"
                                             "All entries are stored into a database and can be viewed either by a daily basis or the entire history at once.")
                             .arg(AppSettings::i()->AppName));
    this->m_appdesc->setFont(*this->font_desc);
    this->m_appdesc->setWordWrap(true);
    this->m_grid->addWidget(this->m_appdesc, 4, 0, 1, 2);


    /* create about qt */
    this->m_qtlogo = new QLabel(this);
    this->m_qtlogo->setFixedSize(L_SIZE_ICON);
    this->m_qtlogo->setPixmap(QPixmap(":/qt5logo.png").scaled(L_SIZE_ICON, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    this->m_gridqt->addWidget(this->m_qtlogo, 0, 0, 3, 1);

    this->m_qtname = new QLabel(this);
    this->m_qtname->setFont(*this->font_title);
    this->m_qtname->setText("Qt");
    this->m_gridqt->addWidget(this->m_qtname, 0, 1, 1, 1);

    this->m_qtversion = new QLabel(this);
    this->m_qtversion->setFont(*this->font_version);
    this->m_qtversion->setText(qVersion());
    this->m_gridqt->addWidget(this->m_qtversion, 1, 1, 1, 1);

    this->m_qtcopyright = new QLabel(this);
    this->m_qtcopyright->setFont(*this->font_copyright);
    this->m_qtcopyright->setTextFormat(Qt::RichText);
    this->m_qtcopyright->setWordWrap(true);
    this->m_qtcopyright->setOpenExternalLinks(true);
    this->m_qtcopyright->setText("<html><p>Qt is a C++ toolkit for cross-platform application development.</p>" "</br></br>"
                                 "</br></br>"
                                 "<p>Copyright © 2015 Digia Plc and/or its subsidiary(-ies) and other contributors.</p>" "</br></br>"
                                 "<p>Qt and the Qt logo are trademarks of Digia Plc and/or its subsidiary(-ies)</p>" "</br></br>"
                                 "</br></br>"
                                 "<p>Visit <a href=http://qt.io/licensing><b>qt.io/licensing</b></a> for more information.</p></html>");
    this->m_gridqt->addWidget(new QLabel(this), 3, 0, 1, 2);
    this->m_gridqt->addWidget(this->m_qtcopyright, 4, 0, 1, 2);
}

AboutDialog::~AboutDialog()
{
    delete this->m_layout;

    delete this->m_grid;
    delete this->m_gridqt;

    delete this->spacer;

    delete this->m_appicon;
    delete this->m_appname;
    delete this->m_appversion;
    delete this->m_appcopyright;
    delete this->m_appdesc;

    delete this->m_qtlogo;
    delete this->m_qtname;
    delete this->m_qtversion;
    delete this->m_qtcopyright;

    delete this->font_title;
    delete this->font_version;
    delete this->font_copyright;
    delete this->font_desc;
}

QFont *AboutDialog::createFont(int pointsize, bool bold, bool italic)
{
    QFont *font = new QFont();
    font->setPointSize(pointsize);
    font->setBold(bold);
    font->setItalic(italic);
    return font;
}
