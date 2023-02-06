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

#include <libEric/Core/Windows.hpp>
#include <filesystem>
#include <Config_LibEric.hpp>

const std::string datadir = "data\\";

LibEric::Filesystem *LibEric::Filesystem::pInstance = nullptr;

LibEric::Filesystem* LibEric::Filesystem::Instance(){
    if (pInstance == nullptr){
        pInstance = new Filesystem;
    }
    return pInstance;
}

LibEric::Filesystem::Filesystem(){

}

bool LibEric::Filesystem::FileExists (std::string file){
    return std::filesystem::exists(file.c_str());
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
    return datadir;
}
std::string LibEric::Filesystem::GetRealPath(std::string path){

    return  path;
}
char LibEric::Filesystem::GetDirSeparator(){
    return '\\';
}

std::string LibEric::Filesystem::PathToUnix(std::string path) {
    std::string tmpPath;
    std::replace( tmpPath.begin(), tmpPath.end(), '\\', '/');
    return tmpPath;
}