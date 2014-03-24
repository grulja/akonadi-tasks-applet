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

#ifndef MODEL_ITEM_H
#define MODEL_ITEM_H

#include <Akonadi/Item>
#include <Akonadi/Collection>
#include <KCalCore/Todo>

class ModelItem : public QObject
{
Q_OBJECT
public:
    ModelItem(Akonadi::Entity::Id id, Akonadi::Collection::Id collectionId, QObject* parent = 0);
    virtual ~ModelItem();

    // TODO categories

    Akonadi::Collection::Id collectionId() const;

    bool completed() const;
    void setCompleted(bool completed);

    QString description() const;
    void setDescription(const QString& description);

    KDateTime dueDate() const;
    void setDueDate(const KDateTime& date);

    Akonadi::Entity::Id id() const;

    QString parentUid() const;
    void setParentUid(const QString& parentUid);

    int priority() const;
    void setPriority(int priority);

    void setStartDate(const KDateTime& date);
    KDateTime startDate() const;

    QString summary() const;
    void setSummary(const QString& summary);

    QString uid() const;
    void setUid(const QString& uid);

    bool operator=(ModelItem * item);

private:
    Akonadi::Collection::Id m_collectionId;
    bool m_completed;
    QString m_description;
    KDateTime m_dueDate;
    Akonadi::Entity::Id m_id;
    QString m_parentUid;
    int m_priority;
    KDateTime m_startDate;
    QString m_summary;
    QString m_uid;
};

#endif
