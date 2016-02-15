#ifndef ABOUTDIALOG_HPP
#define ABOUTDIALOG_HPP

#include <dialogs/materialdialog.hpp>

class AboutDialog : public MaterialDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = 0);
    ~AboutDialog();

private:
    QVBoxLayout *m_layout;

    QGridLayout *m_grid;
    QGridLayout *m_gridqt;

    QFrame *spacer;

    QLabel *m_appicon;
    QLabel *m_appname;
    QLabel *m_appversion;
    QLabel *m_appcopyright;
    QLabel *m_appdesc;

    QLabel *m_qtlogo;
    QLabel *m_qtname;
    QLabel *m_qtversion;
    QLabel *m_qtcopyright;

    QFont *font_title;
    QFont *font_version;
    QFont *font_copyright;
    QFont *font_desc;
    QFont *createFont(int pointsize, bool bold, bool italic);
};

extern AboutDialog *aboutDialog;

#endif // ABOUTDIALOG_HPP
