/****************************************************************************
 * This file is part of Vibe.
 *
 * Copyright (C) 2016 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * Author(s):
 *    Pier Luigi Fiorini
 *
 * $BEGIN_LICENSE:GPL2+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

#include <QtTest/QtTest>

#include <Vibe/Core/QObjectListModel>

class CustomObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString string MEMBER m_string CONSTANT)
    Q_PROPERTY(int integer MEMBER m_integer CONSTANT)
    Q_PROPERTY(bool boolean MEMBER m_boolean CONSTANT)
public:
    CustomObject(QObject *parent = nullptr)
        : QObject(parent)
    {
    }

    QString m_string;
    int m_integer;
    bool m_boolean;
};


class TestQObjectListModel : public QObject
{
    Q_OBJECT
public:
    TestQObjectListModel(QObject *parent = nullptr)
        : QObject(parent)
    {
    }

private Q_SLOTS:
    void initTestCase()
    {
        int i = 0;
        while (i < 5) {
            CustomObject *o = new CustomObject(this);
            o->m_string = QStringLiteral("item%1").arg(i + 1);
            o->m_integer = 42 + i;
            o->m_boolean = true;
            m_list.append(o);
            i++;
        }
    }

    void creation()
    {
        QObjectListModel *model = QObjectListModel::create(m_list, this);
        QVERIFY(model);

        QCOMPARE(model->rowCount(QModelIndex()), m_list.count());

        for (int i = 0; i < 5; i++) {
            QModelIndex index = model->index(i, 0, QModelIndex());
            auto object = model->data(index, Qt::DisplayRole).value<CustomObject *>();
            QCOMPARE(object->m_string, QStringLiteral("item%1").arg(i + 1));
            QCOMPARE(object->m_integer, 42 + i);
            QCOMPARE(object->m_boolean, true);
        }

        delete model;
    }

private:
    QList<CustomObject *> m_list;
};

QTEST_MAIN(TestQObjectListModel)

#include "tst_qobjectlistmodel.moc"
