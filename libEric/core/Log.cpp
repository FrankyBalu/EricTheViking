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


#include <libEric/Core/Log.hpp>

LibEric::Log *LibEric::Log::_Instance = nullptr;

LibEric::Log::Log() {
    _LogLevel = LOG_WARNING;
}

LibEric::Log *LibEric::Log::Instance() {
    if (_Instance == nullptr) {
        _Instance = new Log();
    }
    return _Instance;
}

void LibEric::Log::SetLogLevel(int logLevel) {
    _LogLevel = logLevel;
}