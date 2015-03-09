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

#include "config.h"


Language::Language()
{
}


QString Language::checkLanguage(const QString language)
{
    QStringList availableLanguages = getAvailableLanguages();
    if (availableLanguages.count() == 0) return QString("");
    for (int i=0; i<availableLanguages.count(); i++)
        if (language == availableLanguages[i])
            return availableLanguages[i];
    for (int i=0; i<availableLanguages.count(); i++)
        if (language.contains(availableLanguages[i] + QChar('_')))
            return availableLanguages[i];

    return availableLanguages[0];
}


QString Language::defineLanguage(const QString configPath, const QString options)
{
    QMap<QString, QString> optionsDict = parseOptions(options);
    if (optionsDict.contains(QString(LANGUAGE_KEY)))
        if (getAvailableLanguages().contains(optionsDict[QString(LANGUAGE_KEY)]))
            return optionsDict[QString(LANGUAGE_KEY)];

    QString language;
    language = defineLanguageFromFile(configPath);
    if (language.isEmpty())
        language = defineLanguageFromLocale();
    language = checkLanguage(language);

    return language;
}


QString Language::defineLanguageFromFile(const QString configPath)
{
    QSettings settings(configPath, QSettings::IniFormat);

    settings.beginGroup("Common");
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


QMap<QString, QString> Language::parseOptions(const QString options)
{
    QMap<QString, QString> optionsDict;
    for (int i=0; i<options.split(QChar(',')).count(); i++) {
        if (options.split(QChar(','))[i].split(QChar('=')).count() < 2) continue;
        optionsDict[options.split(QChar(','))[i].split(QChar('='))[0]] =
                options.split(QChar(','))[i].split(QChar('='))[1];
    }

    return optionsDict;
}
