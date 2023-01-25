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


#ifndef __TEXTUREMANAGER
#define __TEXTUREMANAGER

#include <string>
#include <map>
#include <raylib.h>

namespace LibEric{

class TextureManager {
public:

    static TextureManager* Instance();

    //Lad alle Texturen, die in der XML-Datei stehen
    bool LoadFromLua (std::string fileName);

    //Ladet eine einzelne Texture aus der angegebenen Datei, mit der ID id
    bool Load (std::string fileName, std::string id);
    void Draw (std::string id, int x, int y);
    void DrawFrame (std::string id, float x, float y, float width, float height, int currentFrame, int currentRow);

    //FIXME wird die Texture dadurch in der größe geändert?
    //FIXME kann currentFrame und currentRow weg?
    void DrawFrameEx (std::string id, float srcX, float srcY, float srcWidth, float srcHeight, float destX, float destY, float destWidth, float destHeight, int currentFrame, int currentRow);
    void DrawFrameEx (std::string id, Rectangle src, Rectangle dest, float rotation = 0.0);
    void DrawTile (std::string id, int x, int y, int width, int height, int currentRow, int currentFrame); //durch DrawFrame ersetzt

    void ClearFromTextureMap (std::string id);

    //FIXME Resize Texture?

    bool Exist (std::string id);

private:

    std::map<std::string,Texture> _TextureMap;


    static TextureManager *_Instance;

    TextureManager();
    ~TextureManager();
};

}; //namespace LibEric
#endif //__TEXTUREMANAGER
