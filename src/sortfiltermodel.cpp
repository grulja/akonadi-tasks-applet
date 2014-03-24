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
#include "sortfiltermodel.h"

SortFilterModel::SortFilterModel(QObject* parent)
    : QSortFilterProxyModel(parent)
{
    setDynamicSortFilter(true);
    sort(0, Qt::DescendingOrder);
}

SortFilterModel::~SortFilterModel()
{
}

bool SortFilterModel::filterAcceptsRow(int source_row, const QModelIndex& source_parent) const
{
    // TODO add some filters, i.e completed tasks
    return true;
}

bool SortFilterModel::lessThan(const QModelIndex& left, const QModelIndex& right) const
{
    const QString leftUid = sourceModel()->data(left, Model::UidRole).toString();
    const QString rightUid = sourceModel()->data(right, Model::UidRole).toString();

    const QString leftParentUid = sourceModel()->data(left, Model::ParentUidRole).toString();
    const QString rightParentUid = sourceModel()->data(right, Model::ParentUidRole).toString();

    const int leftPriority = sourceModel()->data(left, Model::PriorityRole).toInt();
    const int rightPriority = sourceModel()->data(right, Model::PriorityRole).toInt();

    if (leftParentUid == rightParentUid) {
        // TODO add more sorting options
        return leftPriority > rightPriority;
    }

    // TODO - level 2+?
    if (leftParentUid.isEmpty() && !rightParentUid.isEmpty()) {
        return leftUid == rightParentUid;
    } else if (!leftParentUid.isEmpty() && rightParentUid.isEmpty()) {
        return leftParentUid == rightUid;
    }

    return false;
}

