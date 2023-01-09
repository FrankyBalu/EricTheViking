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

#ifndef __STORYNODE
#define __STORYNODE

#include <string>
#include <map>

namespace LibEric {

class StoryNode
{
public:
    static StoryNode* Instance();

    bool NodeFinished (std::string node);

    void NewNode (std::string node, bool value);

private:
    std::map<std::string,bool> _NodeMap;


    static StoryNode *_Instance;

    StoryNode();
    ~StoryNode();
};
}; //namespace LibEric
#endif // __STORYNODE
