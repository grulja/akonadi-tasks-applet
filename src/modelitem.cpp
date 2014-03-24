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

#include "modelitem.h"

ModelItem::ModelItem(Akonadi::Entity::Id id, Akonadi::Collection::Id collectionId, QObject* parent)
    : QObject(parent)
    , m_collectionId(collectionId)
    , m_completed(false)
    , m_id(id)
    , m_priority(0)
{
}

ModelItem::~ModelItem()
{
}

Akonadi::Entity::Id ModelItem::collectionId() const
{
    return m_collectionId;
}

bool ModelItem::completed() const
{
    return m_completed;
}

void ModelItem::setCompleted(bool completed)
{
    m_completed = completed;
}

QString ModelItem::description() const
{
    return m_description;
}

void ModelItem::setDescription(const QString& description)
{
    m_description = description;
}

KDateTime ModelItem::dueDate() const
{
    return m_dueDate;
}

void ModelItem::setDueDate(const KDateTime& date)
{
    m_dueDate = date;
}

Akonadi::Entity::Id ModelItem::id() const
{
    return m_id;
}

QString ModelItem::parentUid() const
{
    return m_parentUid;
}

void ModelItem::setParentUid(const QString& parentUid)
{
    m_parentUid = parentUid;
}

int ModelItem::priority() const
{
    return m_priority;
}

void ModelItem::setPriority(int priority)
{
    m_priority = priority;
}

KDateTime ModelItem::startDate() const
{
    return m_startDate;
}

void ModelItem::setStartDate(const KDateTime& date)
{
    m_startDate = date;
}

QString ModelItem::summary() const
{
    return m_summary;
}

void ModelItem::setSummary(const QString& summary)
{
    m_summary = summary;
}

QString ModelItem::uid() const
{
    return m_uid;
}

void ModelItem::setUid(const QString& uid)
{
    m_uid = uid;
}

bool ModelItem::operator=(ModelItem* item)
{
    return id() == item->id();
}
