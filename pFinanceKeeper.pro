#-------------------------------------------------
#
# pFinanceKeeper < Personal Household Book >
#
# Easy to use with nice material design UI :)
#
#-------------------------------------------------

# Qt Libraries
QT       += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# Android: include QtAndroidExtras
android: QT += androidextras

# Desktop Application
TARGET = pFinanceKeeper
TEMPLATE = app

# Written in C++11
QMAKE_CXXFLAGS += -std=c++0x

# Source files
SOURCES += main.cpp \
    core/appsettings.cpp \
    core/themeloader.cpp \
    buttons/financebutton.cpp \
    buttons/materialbutton.cpp \
    buttons/titlebarbutton.cpp \
    buttons/titlebarminimizebutton.cpp \
    buttons/titlebarclosebutton.cpp \
    buttons/titlebarprintbutton.cpp \
    buttons/titlebarinfobutton.cpp \
    buttons/titlebarmaximizebutton.cpp \
    decorations/titlebarpainter.cpp \
    dialogs/materialdialog.cpp \
    core/databasemanager.cpp \
    dialogs/noticedialog.cpp \
    dialogs/mainframe.cpp \
    buttons/titlebarprefsbutton.cpp \
    buttons/menubutton.cpp \
    dialogs/entrycreator.cpp \
    core/amountvalidator.cpp \
    dialogs/aboutdialog.cpp \
    dialogs/prefsdialog.cpp \
    dialogs/databaseviewer.cpp

# Header files
HEADERS  += \
    core/appsettings.hpp \
    core/themeloader.hpp \
    buttons/financebutton.hpp \
    buttons/materialbutton.hpp \
    buttons/titlebarbutton.hpp \
    buttons/titlebarminimizebutton.hpp \
    buttons/titlebarclosebutton.hpp \
    buttons/titlebarprintbutton.hpp \
    buttons/titlebarinfobutton.hpp \
    buttons/titlebarmaximizebutton.hpp \
    decorations/titlebarpainter.hpp \
    dialogs/materialdialog.hpp \
    core/databasemanager.hpp \
    dialogs/noticedialog.hpp \
    dialogs/mainframe.hpp \
    buttons/titlebarprefsbutton.hpp \
    buttons/menubutton.hpp \
    dialogs/entrycreator.hpp \
    core/amountvalidator.hpp \
    dialogs/aboutdialog.hpp \
    dialogs/prefsdialog.hpp \
    dialogs/databaseviewer.hpp

# Embedded Resources for portability
RESOURCES += \
    resources/resources.qrc

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
