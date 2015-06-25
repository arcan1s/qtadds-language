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

#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <QStringList>
#include <QObject>


class Language : public QObject
{
    Q_OBJECT

public:
    explicit Language(QObject *parent);
    virtual ~Language();
    static QString defineLanguage(const QString configPath,
                                  const QString options = QString("OPTIONS"));
    static QStringList getAvailableLanguages();

private:
    QString checkLanguage(const QString language);
    QString defineLanguageFromFile(const QString configPath);
    QString defineLanguageFromLocale();
    QString parseOptions(const QString options);
};


#endif /* LANGUAGE_H */
