/*
 * LibEric
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

#ifndef ERIC_WINDOWS_HPP
#define ERIC_WINDOWS_HPP

#ifdef _WIN64

#include <string>
#include <algorithm>

namespace LibEric {
    class Filesystem {
    public:
        static Filesystem* Instance();

        bool FileExists (std::string file);
        std::string GetDataPath();
        std::string GetAssetPath();
        std::string GetMenuPath();
        std::string GetMapPath();
        std::string GetConfigPath();
        std::string GetUserPath();
        std::string GetRealPath(std::string pasth);
        char GetDirSeparator();

        std::string PathToUnix(std::string path);

    private:
        Filesystem();
        std::string pDatapath;
        std::string pOSstring;
        static Filesystem *pInstance;
    };
}//namespace

#endif

#endif //ERIC_WINDOWS_HPP
