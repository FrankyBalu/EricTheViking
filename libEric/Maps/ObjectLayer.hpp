/*
 * libEric
 * Copyright (C) 2022   Frank Kartheuser <frank.kartheuser1988@gmail.com>
 * Copyright (C) 2023   Frank Kartheuser <frank.kartheuser1988@gmail.com>
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

#ifndef OBJECTLAYER
#define OBJECTLAYER

#include <vector>
#include <libEric/Maps/Layer.hpp>
#include <libEric/Core/GameObject_Interface.hpp>

namespace LibEric {

    class ObjectLayer : public Layer {
    public:
        ObjectLayer();

        void Render() override;

        void Update() override;

        std::vector<GameObject_Interface *> *GetGameObjectList();

    private:
        std::vector<GameObject_Interface *> pGameObjectList;
    };

}; //namespace LibEric
#endif //__OBJECTLAYER
