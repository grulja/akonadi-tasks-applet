/*
 * Copyright (C) 2014 Jan Grulich <jgrulich@redhat.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#ifndef MODEL_H
#define MODEL_H

#include <QtCore/QAbstractListModel>

#include <Akonadi/Collection>
#include <Akonadi/Monitor>

#include <KJob>

#include "modelitem.h"

class Model : public QAbstractListModel
{
Q_OBJECT
public:
    enum ItemRole {
        // TODO categories
        CollectionIdRole = Qt::UserRole + 1,
        CompletedRole,
        DescriptionRole,
        IdRole,
        EndDateRole,
        ParentUidRole,
        PriorityRole,
        StartDateRole,
        SummaryRole,
        UidRole,

    };

    Model(QObject* parent = 0);
    virtual ~Model();

    QVariant data(const QModelIndex& index, int role) const;
    int rowCount(const QModelIndex& parent) const;

private Q_SLOTS:
    void fetchCollectionsFinished(KJob* job);
    void fetchItemsFinished(KJob * job);
    void onCollectionAdded(const Akonadi::Collection& collection, const Akonadi::Collection& parent);
    void onCollectionChanged(const Akonadi::Collection& collection);
    void onCollectionRemoved(const Akonadi::Collection& collection);
    void onItemAdded(const Akonadi::Item & item,const Akonadi::Collection & collection);
    void onItemChanged(const Akonadi::Item & item);
    void onItemRemoved(const Akonadi::Item & item);

private:
    Akonadi::Monitor * m_monitor;
    QList<ModelItem*> m_items;

    void fetchItems(const Akonadi::Collection & collection);
};

#endif
