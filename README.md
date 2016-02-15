**THIS PROJECT HAS BEEN CANCELED AND WILL NO LONGER BE MAINTAINED! REPOSITORY WILL BE KEPT FOR HISTORICAL REASONS**

--


# pFinanceKeeper

pFinance Keeper helps you to keep track of your personal earnings and expenses.
All entries are stored into a database and can be viewed either by a daily basis or the entire history at once.

pFinance Keeper is
  - written in C++ and [Qt5](http://www.qt.io/)
  - open source
  - licensed under the [GNU GENERAL PUBLIC LICENSE](LICENSE)

pFinance Keeper is currently only available in English.
More languages may come in the future.

##FEATURES

All versions
  - Freely editable categories for your earnings and expenses.
  - Ability to mark an earning as retour item from an expense, useful for returns.
  - View all your entries in a list sortable by categories or all at once.
  - Amounts are colored: green for earnings and red for expenses

Android and (iOS)
  - Coming soon: Backup & Restore feature. Currently greyed out in the app.

###Supported Platforms

 - Linux
 - Mac OS X
 - Windows
 - Android

###Milestones

 * iOS Support, refer to [Qt Mac Extras](http://doc.qt.io/qt-5/qtmacextras-index.html) and [Qt for iOS](http://doc.qt.io/qt-5/ios-support.html)
    * Optimize UI for iPhones
    * Publish App on the AppStore
 * Complete rewrite of the UI
    * Use the [QScreen](http://doc.qt.io/qt-5/qscreen.html) class to grep DPI and calculate a scaling factor
    * Also refer to this -> [Qt Scalability](http://doc.qt.io/qt-5/scalability.html) (it's in QML but it gives me at least some ideas)
 * Translate pFinance Keeper
    * German (my native language)
    * maybe other languages
 * __DROP DESKTOP SUPPORT__ (there is no use for such app on desktop platforms these days)

###Android Notes

```This software is a hobby project by me, there may be resolution issues on your device. I will try to improve the app as the audience grows. Feel free to help improve this app on GitHub.```

Available on [Google Play](https://play.google.com/store/apps/details?id=com.lenastoffler.pfinancekeeper)


#Next version and futhur development

I'm taking this project very serious now. It started as hobby project and now I want it to become a useful utility for others.

##Platforms

I'm targetting the following platforms for the complete rewrite.
Since I write this in C++11/Qt, there should not be that much trouble regarding platform-specific languages/frameworks :D

  - Android *4.2 and up*
  - iOS *7 and up*
  - BlackBerry __10__
  - Windows RT (Windows Phone)

##Upcoming features

  × __First-launch dialog__
  
    The user can enter the amount of money to start with. This value is interpreted as earning and used for all upcoming entries.
    
  × __Automatically carry over the remaining money to the next month__
  
    The app automatically creates a pseudo-entry for each month, informing the user which amount of money was left.
    pseudo-entry = calculated at runtime (not stored in the db)
    
  × __Store photos (eg: for an bill)__
  
    You can take/add a picture to your entries.
    
  × __New database structure__
  
    SQLite3 Database
      Name         SQLite Type  C++ Type
    × type (+/-)    [INT]        (enum EntryType)
    × category      [INT]        (int)
    × name          [TEXT]       (QString)
    × description   [TEXT]       (QString)
    × is_retour     [INT]        (bool)
    × amount        [NUMERIC]    (double)
    × img           [BLOB]       (QImage -or- QPixmap)   -or-   [TEXT] relative path to file
                                 at the moment i am not sure what whould be better
    
    The 'description' and 'img' can be empty, the other table columns are 'NOT NULL' !!
