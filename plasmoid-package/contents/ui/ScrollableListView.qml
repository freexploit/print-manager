/*
 *   Copyright 2012 Daniel Nicoletti <dantti12@gmail.com>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License as
 *   published by the Free Software Foundation; either version 2 or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

import Qt 4.7
import org.kde.plasma.core 0.1 as PlasmaCore
import org.kde.plasma.components 0.1 as PlasmaComponents
import org.kde.qtextracomponents 0.1

Item {
    property alias delegate: list.delegate
    property alias model: list.model
    property alias interactive: list.interactive
    property alias currentIndex: list.currentIndex
    signal countChanged()
    
    Component.onCompleted: {
        list.countChanged.connect(countChanged)
    }

    ListView {
        id: list
        clip: true
        anchors {
            left:   parent.left
            right:  scrollBar.visible ? scrollBar.left : parent.right
            top :   parent.top
            bottom: parent.bottom
        }
        highlight: highlighter
    }
    Component {
        id: highlighter
        PlasmaCore.FrameSvgItem {
            width: list.width
            imagePath: "widgets/viewitem"
            prefix: "hover"
            opacity: 0.9
            Behavior on opacity {
                NumberAnimation {
                    duration: 250
                    easing.type: Easing.OutQuad
                }
            }
        }
    }
    PlasmaComponents.ScrollBar {
        id: scrollBar
        flickableItem: list
        anchors {
            right: parent.right
            top: list.top
            bottom: list.bottom
        }
    }
}

