/*
 * LibEric
 * Copyright (C) 2022  Frank Kartheuser <frank.kartheuser1988@gmail.com>
 * Copyright (C) 2023  Frank Kartheuser <frank.kartheuser1988@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "StoryNode.hpp"

LibEric::StoryNode *LibEric::StoryNode::pInstance = nullptr;


LibEric::StoryNode *LibEric::StoryNode::Instance() {
    if (pInstance == nullptr) {
        pInstance = new StoryNode();
    }
    return pInstance;
}

void LibEric::StoryNode::NewNode(std::string node, bool value) {
    if (pNodeMap.count(node) != 0) {
        pNodeMap[node] = value;
    }
    pNodeMap[node] = value;
}

bool LibEric::StoryNode::NodeFinished(std::string node) {
    if (pNodeMap.count(node) != 0) {
        return pNodeMap[node];
    }
    return false;
}

LibEric::StoryNode::StoryNode() {
}

LibEric::StoryNode::~StoryNode() {
}
