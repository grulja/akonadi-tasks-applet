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

import QtQuick 1.1
import org.kde.plasma.core 0.1 as PlasmaCore
import org.kde.akonaditasks 0.1 as AkonadiTasks

Item {
    id: mainWindow;

    property int minimumWidth: 300;
    property int minimumHeight: 300;

    property Component compactRepresentation: CompactRepresentation { }

    AkonadiTasks.Model {
        id: tasksModel;
    }

    AkonadiTasks.SortFilterModel {
        id: sortFilterModel;

        sourceModel: tasksModel;
    }

    ListView {
        id: connectionView;

        anchors {
            fill: parent
        }
        clip: true
        model: sortFilterModel;
        currentIndex: -1;
        interactive: true;
        boundsBehavior: Flickable.StopAtBounds;
        delegate: TaskItem { }
    }
}
