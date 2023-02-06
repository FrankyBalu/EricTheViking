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

#include <libEric/Core/Linux.hpp>
#include <physfs.h>
#include <raylib-physfs.h>
#include <Config_LibEric.hpp>

const std::string datadir = "liberic";

LibEric::Filesystem *LibEric::Filesystem::pInstance = nullptr;

LibEric::Filesystem* LibEric::Filesystem::Instance(){
    if (pInstance == nullptr){
        pInstance = new Filesystem;
    }
    return pInstance;
}

LibEric::Filesystem::Filesystem(){
    InitPhysFSEx(LIBERIC_DATADIR.c_str(), datadir.c_str());
    MountPhysFS(GetPerfDirectory(" ", datadir.c_str()), "user");
}

bool LibEric::Filesystem::FileExists (std::string file){
    return FileExistsInPhysFS(file.c_str());
}

std::string LibEric::Filesystem::GetDataPath(){
    return datadir;
}
std::string LibEric::Filesystem::GetAssetPath(){
    return datadir + "/assets/";
}
std::string LibEric::Filesystem::GetMenuPath(){
    return datadir + "/menu/";
}
std::string LibEric::Filesystem::GetMapPath(){
    return datadir + "/maps/";
}
std::string LibEric::Filesystem::GetConfigPath(){
    return datadir;
}
std::string LibEric::Filesystem::GetUserPath(){
    return GetRealPath("user");
}
std::string LibEric::Filesystem::GetRealPath(std::string pasth){
    return PHYSFS_getRealDir(path.c_str());
}
char LibEric::Filesystem::GetDirSeparator(){
    return '/';
}
