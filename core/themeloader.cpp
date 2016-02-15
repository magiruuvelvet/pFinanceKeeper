#include <core/themeloader.hpp>

ThemeLoader *ThemeLoader::i()
{
    static ThemeLoader *instance = new ThemeLoader();
    return instance;
}

void ThemeLoader::init()
{
}

ThemeLoader::ThemeLoader()
{
    /* ~~~ Protected Style Sheet ~~~
     *  QLabel { color: #444444; }
     *  QLineEdit { color: #000000; background-color: #FEFEFE; }
     *
     *  QPushButton { background-color: #EFEFEF; border: 1px solid #A0A0A0; outline: 0; }
     *  QPushButton:hover:!pressed { background-color: #A0A0A0; border: 1px solid #A0A0A0; outline: 0; }
     *  QPushButton:pressed { background-color: #575757; border: 1px solid #EFEFEF; outline: 0; }
     *  QPushButton:focus:!pressed { background-color: #F4F4F4; border: 3px solid #A0A0A0; outline: 0; }
     *
     *  QToolTip { color: #444444; background-color: #F4F4F4; border: 1px solid #444444; }
     *  QCheckBox { outline: 0; }
     *  QDateEdit { color: #000000; background-color: #FEFEFE; }
     *  QComboBox { color: #000000; background-color: #FEFEFE; }
     *  ::drop-down { width: 0px; border-style: none; padding: 2px 1px 1px 1px; }
     */
    this->m_styleSheet = QString::fromUcs4(std::vector<uint>({
                             32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 81, 76, 97, 98, 101, 108, 32, 123, 32, 99, 111,
                             108, 111, 114, 58, 32, 35, 52, 52, 52, 52, 52, 52, 59, 32, 125, 32, 32, 32, 32, 32, 32, 32, 32,
                             32, 32, 32, 32, 32, 81, 76, 105, 110, 101, 69, 100, 105, 116, 32, 123, 32, 99, 111, 108, 111, 114,
                             58, 32, 35, 48, 48, 48, 48, 48, 48, 59, 32, 98, 97, 99, 107, 103, 114, 111, 117, 110, 100, 45, 99,
                             111, 108, 111, 114, 58, 32, 35, 70, 69, 70, 69, 70, 69, 59, 32, 125, 32, 32, 32, 32, 32, 32, 32,
                             32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 81, 80, 117, 115, 104, 66,
                             117, 116, 116, 111, 110, 32, 123, 32, 98, 97, 99, 107, 103, 114, 111, 117, 110, 100, 45, 99, 111,
                             108, 111, 114, 58, 32, 35, 69, 70, 69, 70, 69, 70, 59, 32, 98, 111, 114, 100, 101, 114, 58, 32, 49,
                             112, 120, 32, 115, 111, 108, 105, 100, 32, 35, 65, 48, 65, 48, 65, 48, 59, 32, 111, 117, 116, 108,
                             105, 110, 101, 58, 32, 48, 59, 32, 125, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 81, 80,
                             117, 115, 104, 66, 117, 116, 116, 111, 110, 58, 104, 111, 118, 101, 114, 58, 33, 112, 114, 101, 115,
                             115, 101, 100, 32, 123, 32, 98, 97, 99, 107, 103, 114, 111, 117, 110, 100, 45, 99, 111, 108, 111,
                             114, 58, 32, 35, 65, 48, 65, 48, 65, 48, 59, 32, 98, 111, 114, 100, 101, 114, 58, 32, 49, 112, 120,
                             32, 115, 111, 108, 105, 100, 32, 35, 65, 48, 65, 48, 65, 48, 59, 32, 111, 117, 116, 108, 105, 110,
                             101, 58, 32, 48, 59, 32, 125, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 81, 80, 117, 115,
                             104, 66, 117, 116, 116, 111, 110, 58, 112, 114, 101, 115, 115, 101, 100, 32, 123, 32, 98, 97, 99,
                             107, 103, 114, 111, 117, 110, 100, 45, 99, 111, 108, 111, 114, 58, 32, 35, 53, 55, 53, 55, 53, 55,
                             59, 32, 98, 111, 114, 100, 101, 114, 58, 32, 49, 112, 120, 32, 115, 111, 108, 105, 100, 32, 35, 69,
                             70, 69, 70, 69, 70, 59, 32, 111, 117, 116, 108, 105, 110, 101, 58, 32, 48, 59, 32, 125, 32, 32, 32,
                             32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 81, 80, 117, 115, 104, 66, 117, 116, 116, 111, 110, 58, 102,
                             111, 99, 117, 115, 58, 33, 112, 114, 101, 115, 115, 101, 100, 32, 123, 32, 98, 97, 99, 107, 103, 114,
                             111, 117, 110, 100, 45, 99, 111, 108, 111, 114, 58, 32, 35, 70, 52, 70, 52, 70, 52, 59, 32, 98, 111,
                             114, 100, 101, 114, 58, 32, 51, 112, 120, 32, 115, 111, 108, 105, 100, 32, 35, 65, 48, 65, 48, 65,
                             48, 59, 32, 111, 117, 116, 108, 105, 110, 101, 58, 32, 48, 59, 32, 125, 32, 32, 32, 32, 32, 32, 32,
                             32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 81, 84, 111, 111, 108, 84, 105,
                             112, 32, 123, 32, 99, 111, 108, 111, 114, 58, 32, 35, 52, 52, 52, 52, 52, 52, 59, 32, 98, 97, 99, 107,
                             103, 114, 111, 117, 110, 100, 45, 99, 111, 108, 111, 114, 58, 32, 35, 70, 52, 70, 52, 70, 52, 59, 32,
                             98, 111, 114, 100, 101, 114, 58, 32, 49, 112, 120, 32, 115, 111, 108, 105, 100, 32, 35, 52, 52, 52, 52,
                             52, 52, 59, 32, 125, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 81, 67, 104, 101, 99, 107, 66,
                             111, 120, 32, 123, 32, 111, 117, 116, 108, 105, 110, 101, 58, 32, 48, 59, 32, 125, 32, 32, 32, 32,
                             32, 32, 32, 32, 32, 32, 32, 32, 32, 81, 68, 97, 116, 101, 69, 100, 105, 116, 32, 123, 32, 99, 111,
                             108, 111, 114, 58, 32, 35, 48, 48, 48, 48, 48, 48, 59, 32, 98, 97, 99, 107, 103, 114, 111, 117, 110,
                             100, 45, 99, 111, 108, 111, 114, 58, 32, 35, 70, 69, 70, 69, 70, 69, 59, 32, 125, 32, 32, 32, 32, 32,
                             32, 32, 32, 32, 32, 32, 32, 32, 81, 67, 111, 109, 98, 111, 66, 111, 120, 32, 123, 32, 99, 111, 108,
                             111, 114, 58, 32, 35, 48, 48, 48, 48, 48, 48, 59, 32, 98, 97, 99, 107, 103, 114, 111, 117, 110, 100,
                             45, 99, 111, 108, 111, 114, 58, 32, 35, 70, 69, 70, 69, 70, 69, 59, 32, 125, 32, 32, 32, 32, 32, 32,
                             32, 32, 32, 32, 32, 32, 32, 58, 58, 100, 114, 111, 112, 45, 100, 111, 119, 110, 32, 123, 32, 119, 105,
                             100, 116, 104, 58, 32, 48, 112, 120, 59, 32, 98, 111, 114, 100, 101, 114, 45, 115, 116, 121, 108, 101, 58,
                             32, 110, 111, 110, 101, 59, 32, 112, 97, 100, 100, 105, 110, 103, 58, 32, 50, 112, 120, 32, 49, 112, 120,
                             32, 49, 112, 120, 32, 49, 112, 120, 59, 32, 125, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32
                         }).data(), 915);

    /* color: #34A600; */
    this->m_earningColor = QString::fromUcs4(std::vector<uint>({99, 111, 108, 111, 114, 58, 32, 35, 51, 52, 65, 54, 48, 48, 59}).data(), 15);

    /* color: #DA0000; */
    this->m_expenseColor = QString::fromUcs4(std::vector<uint>({99, 111, 108, 111, 114, 58, 32, 35, 68, 65, 48, 48, 48, 48, 59}).data(), 15);

    /* color: #C3C3C3; */
    this->m_disabledColor = QString::fromUcs4(std::vector<uint>({99, 111, 108, 111, 114, 58, 32, 35, 67, 51, 67, 51, 67, 51, 59}).data(), 15);

    /* widget background */
    this->m_bg = new QImage(QString::fromUcs4(std::vector<uint>({58, 47, 97, 112, 112, 47, 98, 103, 46, 112, 110, 103}).data(), 12));

    /* button icons */
    this->m_appIcon = new QIcon(QString::fromUcs4(std::vector<uint>({58, 47, 97, 112, 112, 47, 105, 99, 111, 110, 46, 112, 110, 103}).data(), 14));
    this->m_prefsIcon = new QIcon(QString::fromUcs4(std::vector<uint>({58, 47, 97, 112, 112, 47, 112, 114, 101, 102, 115, 46, 112, 110, 103}).data(), 15));
    this->m_infoIcon = new QIcon(QString::fromUcs4(std::vector<uint>({58, 47, 97, 112, 112, 47, 105, 99, 111, 110, 45, 105, 110, 102, 111, 46, 112, 110, 103}).data(), 19));
    this->m_closeIcon = new QIcon(QString::fromUcs4(std::vector<uint>({58, 47, 97, 112, 112, 47, 105, 99, 111, 110, 45, 99, 108, 111, 115, 101, 46, 112, 110, 103}).data(), 20));
    this->m_minimizeIcon = new QIcon(QString::fromUcs4(std::vector<uint>({58, 47, 97, 112, 112, 47, 105, 99, 111, 110, 45, 109, 105, 110, 105, 109, 105, 122, 101, 46, 112, 110, 103}).data(), 23));
    this->m_maximizeIcon = new QIcon(QString::fromUcs4(std::vector<uint>({58, 47, 97, 112, 112, 47, 105, 99, 111, 110, 45, 109, 97, 120, 105, 109, 105, 122, 101, 46, 112, 110, 103}).data(), 23));
    this->m_unmaximizeIcon = new QIcon(QString::fromUcs4(std::vector<uint>({58, 47, 97, 112, 112, 47, 105, 99, 111, 110, 45, 117, 110, 109, 97, 120, 105, 109, 105, 122, 101, 46, 112, 110, 103}).data(), 25));
    this->m_printIcon = new QIcon(QString::fromUcs4(std::vector<uint>({58, 47, 98, 116, 110, 47, 112, 114, 105, 110, 116, 46, 112, 110, 103}).data(), 15));
    this->m_earningIcon = new QIcon(QString::fromUcs4(std::vector<uint>({58, 47, 109, 111, 110, 101, 121, 47, 97, 100, 100, 46, 112, 110, 103}).data(), 15));
    this->m_expenseIcon = new QIcon(QString::fromUcs4(std::vector<uint>({58, 47, 109, 111, 110, 101, 121, 47, 114, 101, 109, 111, 118, 101, 46, 112, 110, 103}).data(), 18));
    this->m_alertIcon = new QIcon(QString::fromUcs4(std::vector<uint>({58, 47, 97, 112, 112, 47, 97, 108, 101, 114, 116, 46, 112, 110, 103}).data(), 15));

    /* finance buttons */
    this->m_btnIncomeIcon = new QIcon(QString::fromUcs4(std::vector<uint>({58, 47, 98, 116, 110, 47, 105, 110, 99, 111, 109, 101, 46, 112, 110, 103}).data(), 16));
    this->m_btnExpenseIcon = new QIcon(QString::fromUcs4(std::vector<uint>({58, 47, 98, 116, 110, 47, 101, 120, 112, 101, 110, 115, 101, 46, 112, 110, 103}).data(), 17));
    this->m_btnEntriesIcon = new QIcon(QString::fromUcs4(std::vector<uint>({58, 47, 98, 116, 110, 47, 101, 110, 116, 114, 105, 101, 115, 46, 112, 110, 103}).data(), 17));
    this->m_btnHistoryIcon = new QIcon(QString::fromUcs4(std::vector<uint>({58, 47, 98, 116, 110, 47, 104, 105, 115, 116, 111, 114, 121, 46, 112, 110, 103}).data(), 17));

    /* preference buttons */
    this->m_btnAddIcon = new QIcon(QString::fromUcs4(std::vector<uint>({58, 47, 98, 116, 110, 47, 97, 100, 100, 46, 115, 118, 103}).data(), 13));
    this->m_btnRemoveIcon = new QIcon(QString::fromUcs4(std::vector<uint>({58, 47, 98, 116, 110, 47, 114, 101, 109, 111, 118, 101, 46, 112, 110, 103}).data(), 16));

    /* android menu button */
    this->m_menuBtn = new QIcon(QString::fromUcs4(std::vector<uint>({58, 47, 98, 116, 110, 47, 109, 101, 110, 117, 98, 116, 110, 46, 112, 110, 103}).data(), 17));
}

ThemeLoader::~ThemeLoader()
{
    this->m_styleSheet.clear();
    this->m_earningColor.clear();
    this->m_expenseColor.clear();
    this->m_disabledColor.clear();

    delete this->m_bg;

    delete this->m_appIcon;
    delete this->m_prefsIcon;
    delete this->m_infoIcon;
    delete this->m_closeIcon;
    delete this->m_minimizeIcon;
    delete this->m_maximizeIcon;
    delete this->m_unmaximizeIcon;
    delete this->m_printIcon;
    delete this->m_earningIcon;
    delete this->m_expenseIcon;
    delete this->m_alertIcon;

    delete this->m_btnIncomeIcon;
    delete this->m_btnExpenseIcon;
    delete this->m_btnEntriesIcon;
    delete this->m_btnHistoryIcon;

    delete this->m_btnAddIcon;
    delete this->m_btnRemoveIcon;

    delete this->m_menuBtn;

    delete this; // Automatically delete from stack on program termination
}


QString ThemeLoader::styleSheet() const { return this->m_styleSheet; }
QString ThemeLoader::earningColor() const { return this->m_earningColor; }
QString ThemeLoader::expenseColor() const { return this->m_expenseColor; }
QString ThemeLoader::disabledColor() const { return this->m_disabledColor; }

QImage *ThemeLoader::bg() const { return this->m_bg; }

QIcon *ThemeLoader::appIcon() const { return this->m_appIcon; }
QIcon *ThemeLoader::prefsIcon() const { return this->m_prefsIcon; }
QIcon *ThemeLoader::infoIcon() const { return this->m_infoIcon; }
QIcon *ThemeLoader::closeIcon() const { return this->m_closeIcon; }
QIcon *ThemeLoader::minimizeIcon() const { return this->m_minimizeIcon; }
QIcon *ThemeLoader::maximizeIcon() const { return this->m_maximizeIcon; }
QIcon *ThemeLoader::unmaximizeIcon() const { return this->m_unmaximizeIcon; }
QIcon *ThemeLoader::printIcon() const { return this->m_printIcon; }
QIcon *ThemeLoader::earningIcon() const { return this->m_earningIcon; }
QIcon *ThemeLoader::expenseIcon() const { return this->m_expenseIcon; }
QIcon *ThemeLoader::alertIcon() const { return this->m_alertIcon; }

QIcon *ThemeLoader::btnIncomeIcon() const { return this->m_btnIncomeIcon; }
QIcon *ThemeLoader::btnExpenseIcon() const { return this->m_btnExpenseIcon; }
QIcon *ThemeLoader::btnEntriesIcon() const { return this->m_btnEntriesIcon; }
QIcon *ThemeLoader::btnHistoryIcon() const { return this->m_btnHistoryIcon; }

QIcon *ThemeLoader::btnAddIcon() const { return this->m_btnAddIcon; }
QIcon *ThemeLoader::btnRemoveIcon() const { return this->m_btnRemoveIcon; }

QIcon *ThemeLoader::menuBtn() const { return this->m_menuBtn; }
