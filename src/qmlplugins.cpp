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
#include "qmlplugins.h"

#include <QtDeclarative>

void QmlPlugins::registerTypes(const char* uri)
{
    // @uri org.kde.private.akonaditasks.Model
    qmlRegisterType<Model>(uri, 0, 1, "Model");
    // @uri org.kde.private.akonaditasks.SortFilterModel
    qmlRegisterType<SortFilterModel>(uri, 0, 1, "SortFilterModel");
}

Q_EXPORT_PLUGIN2(plasmaakonaditasks, QmlPlugins)
