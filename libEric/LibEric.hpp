/*
 * libEric
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

#ifndef ERIC_LIBERIC_HPP
#define ERIC_LIBERIC_HPP

/**
 * @brief Diese Header sind nötig um ein Spiel mit libEric zu erstellen und sollten immer includiert werden.
 * Wichtig ist nur ERIC_APP zu definieren
 */
#ifdef ERIC_APP
#include "Dialog.hpp"
#include "Game.hpp"
#include "GameObjectFactory.hpp"
#include "GraphicGameObject.hpp"
#include "GameStateFactory.hpp"
#include "GameStateMaschine.hpp"
#include "UserSettings.hpp"
#endif //ERIC_APP

/**
 * @brief Header die zum, erweitern von libEric benötigt werden, diese sollen am besten einzeln includiert werden.
 * Für den fall der fälle gibt es hier alle auf einmal
 */
#ifdef ERIC_MODULE_ALL

#include "GameObject.hpp"
#include "GameState.hpp"
#include "Layer.hpp"
#include "Log.hpp"
#include "Map.hpp"
#include "MapManager.hpp"
#include "MapParser.hpp"
#include "ObjectLayer.hpp"
#include "PrivateSettings.hpp"
#include "StoryNode.hpp"
#include "TextureManager.hpp"
#include "TileLayer.hpp"

#endif //ERIC_MODULE_ALL

#endif //ERIC_LIBERIC_HPP
