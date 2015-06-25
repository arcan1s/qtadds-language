/***************************************************************************
 *  Copyright (C) 2014  Evgeniy Alekseev                                      *
 *                                                                         *
 *  This library is free software; you can redistribute it and/or          *
 *  modify it under the terms of the GNU Lesser General Public             *
 *  License as published by the Free Software Foundation; either           *
 *  version 3.0 of the License, or (at your option) any later version.     *
 *                                                                         *
 *  This library is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU       *
 *  Lesser General Public License for more details.                        *
 *                                                                         *
 *  You should have received a copy of the GNU Lesser General Public       *
 *  License along with this library.                                       *
 ***************************************************************************/


#include "language.h"

#include <QFile>
#include <QLocale>
#include <QSettings>
#include <QRegExp>

#include "config.h"


Language::Language(QObject *parent)
    : QObject(parent)
{
}


Language::~Language()
{
}


QString Language::checkLanguage(const QString language)
{
    QStringList availableLanguages = getAvailableLanguages();
    if (availableLanguages.isEmpty()) return QString();

    QStringList filtered = availableLanguages.filter(language);
    filtered.append(availableLanguages.filter(QRegExp(QString("^%1").arg(language.split(QChar('_'))[0]))));

    if (filtered.isEmpty())
        return availableLanguages[0];
    else
        return filtered[0];
}


QString Language::defineLanguage(const QString configPath, const QString options)
{
    // create instance
    Language *langObject = new Language(nullptr);

    // define language
    QString language = langObject->parseOptions(options);
    if (language.isEmpty())
        language = langObject->defineLanguageFromFile(configPath);
    if (language.isEmpty())
        language = langObject->defineLanguageFromLocale();
    language = langObject->checkLanguage(language);

    // clear
    delete langObject;

    return language;
}


QString Language::defineLanguageFromFile(const QString configPath)
{
    QSettings settings(configPath, QSettings::IniFormat);

    settings.beginGroup(QString(LANGUAGE_SECTION));
    QString language = settings.value(QString(LANGUAGE_KEY), QString()).toString();
    settings.endGroup();

    return language;
}


QString Language::defineLanguageFromLocale()
{
    return QLocale::system().name();
}


QStringList Language::getAvailableLanguages()
{
    return QString(LANGUAGES).split(QChar(','));
}


QString Language::parseOptions(const QString options)
{
    QString language;
    for (int i=0; i<options.split(QChar(',')).count(); i++) {
        if (options.split(QChar(','))[i].split(QChar('=')).count() < 2) continue;
        if (options.split(QChar(','))[i].split(QChar('='))[0] != QString(LANGUAGE_KEY)) continue;
        language = options.split(QChar(','))[i].split(QChar('='))[1];
    }

    return language;
}
