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
import org.kde.plasma.components 0.1 as PlasmaComponents

PlasmaComponents.ListItem {
    id: taskItem;

    height: Math.max(taskName.height, taskDetails.height) + padding.margins.top + padding.margins.bottom;

    PlasmaCore.FrameSvgItem {
        id: padding
        imagePath: "widgets/viewitem"
        prefix: "hover"
        opacity: 0
        anchors.fill: parent
    }

    PlasmaComponents.CheckBox {
        id: taskCompleted;

        anchors {
            left: parent.left;
            leftMargin: ParentUid.length === 0 ? padding.margins.left : padding.margins.left + width;
            verticalCenter: parent.verticalCenter;
        }
        checked: Completed;
    }

    Column {
        id: taskDetails;

        anchors {
            left: taskCompleted.right;
            leftMargin: padding.margins.left;
            right: parent.right;
            rightMargin: padding.margins.right;
            verticalCenter: parent.verticalCenter;
        }
        spacing: 2;

        PlasmaComponents.Label {
            id: taskName;

            anchors {
                left: parent.left;
                right: parent.right;
            }
            elide: Text.ElideRight;
            height: paintedHeight;
            text: Summary;
            font.bold: ParentUid.length === 0;
        }

        PlasmaComponents.Label {
            id: taskDescription;

            anchors {
                left: parent.left;
                right: parent.right;
            }
            elide: Text.ElideRight;
            height: Description.length === 0 ? 0 : paintedHeight;
            maximumLineCount: 1;
            opacity: 0.6;
            text: Description;
            font.bold: ParentUid.length === 0;
        }
    }
}
