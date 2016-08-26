/****************************************************************************
 * This file is part of Hawaii.
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

#pragma once

#include <QtCore/QLocale>
#include <QtCore/QObject>
#include <Hawaii/Core/KFormat>

/**
  * Formats is a wrapper around KFormat which provides support for formatting
  * numbers and datetimes in formats that are not supported by QLocale.
  *
  * @short Class for formatting numbers and datetimes.
  */
class Formatter : public QObject
{
    Q_OBJECT
public:
    /**
     * These binary units are used in KDE by the formatByteSize()
     * function.
     *
     * NOTE: There are several different units standards:
     * 1) SI  (i.e. metric), powers-of-10.
     * 2) IEC, powers-of-2, with specific units KiB, MiB, etc.
     * 3) JEDEC, powers-of-2, used for solid state memory sizing which
     *    is why you see flash cards labels as e.g. 4GB.  These (ab)use
     *    the metric units.  Although JEDEC only defines KB, MB, GB, if
     *    JEDEC is selected all units will be powers-of-2 with metric
     *    prefixes for clarity in the event of sizes larger than 1024 GB.
     *
     * Although 3 different dialects are possible this enum only uses
     * metric names since adding all 3 different names of essentially the same
     * unit would be pointless.  Use BinaryUnitDialect to control the exact
     * units returned.
     *
     * @see BinaryUnitDialect
     * @see formatByteSize
     */
    enum BinarySizeUnits {
        /// Auto-choose a unit such that the result is in the range [0, 1000 or 1024)
        DefaultBinaryUnits = -1,

        // The first real unit must be 0 for the current implementation!
        UnitByte,      ///<  B         1 byte
        UnitKiloByte,  ///<  KiB/KB/kB 1024/1000 bytes.
        UnitMegaByte,  ///<  MiB/MB/MB 2^20/10^06 bytes.
        UnitGigaByte,  ///<  GiB/GB/GB 2^30/10^09 bytes.
        UnitTeraByte,  ///<  TiB/TB/TB 2^40/10^12 bytes.
        UnitPetaByte,  ///<  PiB/PB/PB 2^50/10^15 bytes.
        UnitExaByte,   ///<  EiB/EB/EB 2^60/10^18 bytes.
        UnitZettaByte, ///<  ZiB/ZB/ZB 2^70/10^21 bytes.
        UnitYottaByte, ///<  YiB/YB/YB 2^80/10^24 bytes.
        UnitLastUnit = UnitYottaByte
    };
    Q_ENUM(BinarySizeUnits)

    /**
     * This enum chooses what dialect is used for binary units.
     *
     * Note: Although JEDEC abuses the metric prefixes and can therefore be
     * confusing, it has been used to describe *memory* sizes for quite some time
     * and programs should therefore use either Default, JEDEC, or IEC 60027-2
     * for memory sizes.
     *
     * On the other hand network transmission rates are typically in metric so
     * Default, Metric, or IEC (which is unambiguous) should be chosen.
     *
     * Normally choosing DefaultBinaryDialect is the best option as that uses
     * the user's selection for units.  If the user has not selected a preference,
     * IECBinaryDialect will typically be used.
     *
     * @see BinarySizeUnits
     * @see formatByteSize
     */
    enum BinaryUnitDialect {
        DefaultBinaryDialect = -1, ///< Used if no specific preference
        IECBinaryDialect,          ///< KiB, MiB, etc. 2^(10*n)
        JEDECBinaryDialect,        ///< KB, MB, etc. 2^(10*n)
        MetricBinaryDialect,       ///< SI Units, kB, MB, etc. 10^(3*n)
        LastBinaryDialect = MetricBinaryDialect
    };
    Q_ENUM(BinaryUnitDialect)

    /**
     * Format flags for formatDuration()
     */
    enum DurationFormatOption {
        DefaultDuration = 0x0,
        InitialDuration = 0x1,  ///< Default formatting in localized 1h23m45s format
        ShowMilliseconds = 0x2, ///< Include milliseconds in format, e.g. 1:23:45.678
        HideSeconds = 0x4,      ///< Hide the seconds, e.g. 1:23 or 1h23m, overrides
                                ///< ShowMilliseconds
        FoldHours = 0x8         ///< Fold the hours into the minutes, e.g. 83:45 or
                                ///< 83m45s, overrides HideSeconds
    };
    Q_DECLARE_FLAGS(DurationFormatOptions, DurationFormatOption)
    Q_FLAG(DurationFormatOptions)

    Formatter(QObject *parent = nullptr);

    /**
     * Converts @p size from bytes to the appropriate string representation
     * using the binary unit dialect @p dialect and the specific units @p specificUnit.
     *
     * Example:
     * formatByteSize(1000, unit, KFormat::UnitKiloByte) returns:
     *   for KFormat::MetricBinaryDialect, "1.0 kB",
     *   for KFormat::IECBinaryDialect,    "0.9 KiB",
     *   for KFormat::JEDECBinaryDialect,  "0.9 KB".
     *
     * @param size size in bytes
     * @param precision number of places after the decimal point to use.  KDE uses
     *        1 by default so when in doubt use 1.
     * @param dialect binary unit standard to use.  Use DefaultBinaryDialect to
     *        use the localized user selection unless you need to use a specific
     *        unit type (such as displaying a flash memory size in JEDEC).
     * @param specificUnit specific unit size to use in result.  Use
     *        DefaultBinaryUnits to automatically select a unit that will return
     *        a sanely-sized number.
     * @return converted size as a translated string including the units.
     *         E.g. "1.23 KiB", "2 GB" (JEDEC), "4.2 kB" (Metric).
     * @see BinarySizeUnits
     * @see BinaryUnitDialect
     */
    Q_INVOKABLE QString formatByteSize(double size, int precision = 1,
                                       BinaryUnitDialect dialect = DefaultBinaryDialect,
                                       BinarySizeUnits units = DefaultBinaryUnits) const;

    /**
     * Given a number of milliseconds, converts that to a string containing
     * the localized equivalent, e.g. 1:23:45
     *
     * @param msecs Time duration in milliseconds
     * @param options options to use in the duration format
     * @return converted duration as a string - e.g. "1:23:45" "1h23m"
     */
    Q_INVOKABLE QString formatDuration(quint64 msecs,
                                       DurationFormatOptions options = DefaultDuration) const;

    /**
     * Given a number of milliseconds, converts that to a string containing
     * the localized equivalent to the requested decimal places.
     *
     * e.g. given formatDuration(60000), returns "1.0 minutes"
     *
     * @param msecs Time duration in milliseconds
     * @param decimalPlaces Deciaml places to round off to, defaults to 2
     * @return converted duration as a string - e.g. "5.5 seconds" "23.0 minutes"
     */
    Q_INVOKABLE QString formatDecimalDuration(quint64 msecs, int decimalPlaces = 2) const;

    /**
     * Given a number of milliseconds, converts that to a spell-out string containing
     * the localized equivalent.
     *
     * e.g. given formatSpelloutDuration(60001) returns "1 minute"
     *      given formatSpelloutDuration(62005) returns "1 minute and 2 seconds"
     *      given formatSpelloutDuration(90060000) returns "1 day and 1 hour"
     *
     * @param msecs Time duration in milliseconds
     * @return converted duration as a string.
     *         Units not interesting to the user, for example seconds or minutes when the first
     *         unit is day, are not returned because they are irrelevant. The same applies for
     *         seconds when the first unit is hour.
     */
    Q_INVOKABLE QString formatSpelloutDuration(quint64 msecs) const;

    /**
     * Returns a string formatted to a relative date style.
     *
     * If the @p date falls within one week before or after the current date
     * then a relative date string will be returned, such as:
     * * Yesterday
     * * Today
     * * Tomorrow
     * * Last Tuesday
     * * Next Wednesday
     *
     * If the @p date falls outside this period then the @p format is used.
     *
     * @param date the date to be formatted
     * @param format the date format to use
     *
     * @return the date as a string
     */
    Q_INVOKABLE QString formatRelativeDate(const QDate &date, QLocale::FormatType format) const;

    /**
     * Returns a string formatted to a relative datetime style.
     *
     * If the @p dateTime falls within one week before or after the current date
     * then a relative date string will be returned, such as:
     * * Yesterday, 3:00pm
     * * Today, 3:00pm
     * * Tomorrow, 3:00pm
     * * Last Tuesday, 3:00pm
     * * Next Wednesday, 3:00pm
     *
     * If the @p dateTime falls outside this period then the @p format is used.
     *
     * @param dateTime the date to be formatted
     * @param format the date format to use
     *
     * @return the date as a string
     */
    Q_INVOKABLE QString formatRelativeDateTime(const QDateTime &dateTime,
                                               QLocale::FormatType format) const;

private:
    KFormat formatter;
};
