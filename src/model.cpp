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

#include "model.h"

#include <Akonadi/CollectionFetchJob>
#include <Akonadi/CollectionFetchScope>
#include <Akonadi/ItemFetchJob>
#include <Akonadi/ItemFetchScope>

#include <KCalCore/Todo>

Model::Model(QObject* parent)
    : QAbstractListModel(parent)
    , m_monitor(new Akonadi::Monitor(this))
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[CollectionIdRole] = "CollectionId";
    roles[CompletedRole] = "Completed";
    roles[DescriptionRole] = "Description";
    roles[IdRole] = "Id";
    roles[EndDateRole] = "EndDate";
    roles[ParentUidRole] = "ParentUid";
    roles[PriorityRole] = "Priority";
    roles[StartDateRole] = "StartDate";
    roles[SummaryRole] = "Summary";
    roles[UidRole] = "Uid";

    setRoleNames(roles);

    QStringList mimeTypes;
    mimeTypes << KCalCore::Todo::todoMimeType();

    m_monitor->setAllMonitored(true);
    m_monitor->fetchCollection(true);
    m_monitor->collectionFetchScope().setAncestorRetrieval(Akonadi::CollectionFetchScope::All);
    m_monitor->collectionFetchScope().setContentMimeTypes(mimeTypes);
    m_monitor->itemFetchScope().fetchFullPayload(true);
    m_monitor->itemFetchScope().fetchAllAttributes(true);
    m_monitor->itemFetchScope().setAncestorRetrieval(Akonadi::ItemFetchScope::All);

    Akonadi::CollectionFetchJob * job = new Akonadi::CollectionFetchJob(Akonadi::Collection::root(), Akonadi::CollectionFetchJob::Recursive, this);

    connect(job, SIGNAL(result(KJob*)), SLOT(fetchCollectionsFinished(KJob*)));
    connect(m_monitor, SIGNAL(collectionAdded(Akonadi::Collection,Akonadi::Collection)),
            SLOT(onCollectionAdded(Akonadi::Collection,Akonadi::Collection)));
    connect(m_monitor, SIGNAL(collectionChanged(Akonadi::Collection)),
            SLOT(onCollectionChanged(Akonadi::Collection)));
    connect(m_monitor, SIGNAL(collectionRemoved(Akonadi::Collection)),
            SLOT(onCollectionRemoved(Akonadi::Collection)));
    connect(m_monitor, SIGNAL(itemAdded(Akonadi::Item,Akonadi::Collection)),
            SLOT(onItemAdded(Akonadi::Item,Akonadi::Collection)));
    connect(m_monitor, SIGNAL(itemChanged(Akonadi::Item,QSet<QByteArray>)),
            SLOT(onItemChanged(Akonadi::Item)));
    connect(m_monitor, SIGNAL(itemRemoved(Akonadi::Item)),
            SLOT(onItemRemoved(Akonadi::Item)));
}

Model::~Model()
{
    delete m_monitor;
}

QVariant Model::data(const QModelIndex& index, int role) const
{
   const int row = index.row();

    if (row >= 0 && row < m_items.count()) {
        ModelItem * item = m_items.at(row);

        switch (role) {
            case CollectionIdRole:
                return item->collectionId();
            case CompletedRole:
                return item->completed();
            case DescriptionRole:
                return item->description();
            case IdRole:
                return item->id();
            case EndDateRole:
                // TODO convert to variant
//                 return item->dueDate();
            case ParentUidRole:
                return item->parentUid();
            case PriorityRole:
                return item->priority();
            case StartDateRole:
                // TODO convert to variant
//                 return item->startDate();
            case SummaryRole:
                return item->summary();
            case UidRole:
                return item->uid();
            default:
                break;
        }
    }

    return QVariant();
}

int Model::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return m_items.count();
}

void Model::fetchCollectionsFinished(KJob* job)
{
    if (job->error()) {
        qDebug() << "Failed to fetch collections";
    }

    Akonadi::CollectionFetchJob * fetchJob = qobject_cast<Akonadi::CollectionFetchJob*>(job);
    Akonadi::Collection::List collections = fetchJob->collections();

    Q_FOREACH (const Akonadi::Collection & collection, collections) {
        if (collection.contentMimeTypes().contains(KCalCore::Todo::todoMimeType())) {
            m_monitor->setCollectionMonitored(collection, true);
            fetchItems(collection);
        }
    }
}

void Model::fetchItemsFinished(KJob* job)
{
    if (job->error()) {
        qDebug() << "Failed to fetch items";
        return;
    }

    Akonadi::ItemFetchJob * fetchJob = qobject_cast<Akonadi::ItemFetchJob *>(job);
    const Akonadi::Item::List items = fetchJob->items();

    Q_FOREACH (const Akonadi::Item & item, items) {
        if (item.hasPayload<KCalCore::Todo::Ptr>()) {
            onItemAdded(item, item.parentCollection());
        }
    }
}

void Model::onCollectionAdded(const Akonadi::Collection& collection, const Akonadi::Collection& parent)
{
    Q_UNUSED(parent);
    m_monitor->setCollectionMonitored(collection, true);
    fetchItems(collection);
}

void Model::onCollectionChanged(const Akonadi::Collection& collection)
{
    // TODO
    Q_UNUSED(collection)
}

void Model::onCollectionRemoved(const Akonadi::Collection& collection)
{
    m_monitor->setCollectionMonitored(collection, false);

    Q_FOREACH (const ModelItem * item, m_items) {
        if (item->collectionId() == collection.id()) {
            // TODO remove
        }
    }
}

void Model::onItemAdded(const Akonadi::Item& item, const Akonadi::Collection& collection)
{
    if (item.hasPayload<KCalCore::Todo::Ptr>()) {
        KCalCore::Todo::Ptr todo = item.payload<KCalCore::Todo::Ptr>();

        ModelItem * modelItem = new ModelItem(item.id(), collection.id(), this);
        modelItem->setCompleted(todo->isCompleted());
        modelItem->setDescription(todo->description());
        modelItem->setDueDate(todo->dtDue());
        modelItem->setParentUid(todo->relatedTo(KCalCore::Incidence::RelTypeParent));
        modelItem->setPriority(todo->priority());
        modelItem->setStartDate(todo->dtStart());
        modelItem->setSummary(todo->summary());
        modelItem->setUid(todo->uid());

        int index = m_items.count();
        beginInsertRows(QModelIndex(), index, index);
        m_items << modelItem;
        endInsertRows();
    }
}

void Model::onItemChanged(const Akonadi::Item& item)
{
    // TODO
    Q_UNUSED(item);
}

void Model::onItemRemoved(const Akonadi::Item& item)
{
    // TODO
    Q_UNUSED(item);
}

void Model::fetchItems(const Akonadi::Collection& collection)
{
    Akonadi::ItemFetchJob * job = new Akonadi::ItemFetchJob(collection);
    job->fetchScope().fetchFullPayload(true);
    job->fetchScope().fetchAllAttributes(true);
    job->fetchScope().setAncestorRetrieval(Akonadi::ItemFetchScope::All);

    connect(job, SIGNAL(result(KJob *)), SLOT(fetchItemsFinished(KJob *)));
}
