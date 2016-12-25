/****************************************************************************
 * This file is part of Vibe.
 *
 * Copyright (C) 2016 Michael Spencer <sonrisesoftware@gmail.com>
 *
 * $BEGIN_LICENSE:LGPL2.1+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

#include "formatter.h"

Formatter::Formatter(QObject *parent)
    : QObject(parent)
{
}

QString Formatter::formatByteSize(double size, int precision, BinaryUnitDialect dialect,
                                  BinarySizeUnits units) const
{
    return formatter.formatByteSize(size, precision,
                                    static_cast<KFormat::BinaryUnitDialect>(dialect),
                                    static_cast<KFormat::BinarySizeUnits>(units));
}

QString Formatter::formatDuration(quint64 msecs, DurationFormatOptions options) const
{
    int tempOptions = int(options);
    return formatter.formatDuration(msecs, QFlags<KFormat::DurationFormatOption>(tempOptions));
}

QString Formatter::formatDecimalDuration(quint64 msecs, int decimalPlaces) const
{
    return formatter.formatDecimalDuration(msecs, decimalPlaces);
}

QString Formatter::formatSpelloutDuration(quint64 msecs) const
{
    return formatter.formatSpelloutDuration(msecs);
}

QString Formatter::formatRelativeDate(const QDate &date, QLocale::FormatType format) const
{
    return formatter.formatRelativeDate(date, format);
}

QString Formatter::formatRelativeDateTime(const QDateTime &dateTime,
                                          QLocale::FormatType format) const
{
    return formatter.formatRelativeDateTime(dateTime, format);
}
